#include "pch.h"
#include <stdlib.h>
#include "hooks.h"
#include "pattern.h"
#include "script.h"
#include "logger.h"
#include "natives.h"
#include "globals.h"
#include "enums.h"

bool enableProtections = false;
_scriptEvents g_scriptEvents[9] = {
	{ CEO_BAN, "CEO Ban", &enableProtections },
	{ CEO_KICK, "CEO Kick", &enableProtections },
	{ CEO_MONEY, "CEO Money", &enableProtections },
	{ SET_BOUNTY, "Set Bounty", &enableProtections },
	{ CLEAR_WANTED, "Clear Wanted", &enableProtections },
	{ FAKE_DEOPOSIT, "Fake Deposit", &enableProtections },
	{ FORCE_MISSION, "Force Mission", &enableProtections },
	{ GTA_BANNER, "GTA Banner", &enableProtections },
	{ ROTATE_CAM, "Rotate Cam", &enableProtections }
};

lbls m_gameLabels[100];
int g_labelNum = 0;

GtaThread *getCurScrThr() { return *(GtaThread**)(*(char**)__readgsqword(0x58) + 0x830); }
void setCurScrThr(char* tls, GtaThread* thr) {
	*(GtaThread**)(tls + 0x828) = thr;
	*(bool*)(tls + 0x830) = thr != NULL;
}
GtaThread* getGtaThreadByHash(uint hash) {
	GtaThread** thrTable = (*g_pointers.m_gtaThreads).m_data;
	for (int i = 0; i < (*g_pointers.m_gtaThreads).m_size; i++)
		if (thrTable[i]->script_hash == 0x5700179C)
			return thrTable[i];
	return NULL;
}

//0x5700179C: main_persistent
int (*ogScrThreadRun)(uint32_t ops_to_execute);
int scrThreadRunHk(uint32_t ops_to_execute) {
	GtaThread* main_persistent = getGtaThreadByHash(0x5700179C);
	if (g_running) {
		if (main_persistent != NULL) {
			char* tls = *(char**)__readgsqword(0x58);
			GtaThread* ogThr = getCurScrThr();
			setCurScrThr(tls, main_persistent);
			fbrTick(&g_mainFbr);
			setCurScrThr(tls, ogThr);
		}
		//Disables screenblur, non thread specific
		if (NETWORK_NETWORK_IS_SESSION_ACTIVE()) {
			//We need to not do this in story mode, it breaks the hospital teleport and creates a indefinite suicide scneen
			GRAPHICS_DISABLE_SCREENBLUR_FADE();
			if (CAM_IS_SCREEN_FADED_OUT())
				CAM_DO_SCREEN_FADE_OUT(0);
			else if (CAM_IS_SCREEN_FADED_IN())
				CAM_DO_SCREEN_FADE_IN(0);
		}
	}
	return ogScrThreadRun(ops_to_execute);
}

const char*(*ogGetLabelText)(void* unk, const char* lbl);
const char* getLabelTextHk(void* unk, const char* lbl) {
	for (int i = 0; i < g_labelNum; i++) {
		if (!strcmp(m_gameLabels[i].label, lbl))
			return m_gameLabels[i].contents;
	}
	return ogGetLabelText(unk, lbl);
}

bool scriptedGameEvent(struct CScriptedGameEvent* sge, struct CNetGamePlayer* sender) {
	int64_t* args = sge->m_args;
	for (int i = 0; i < 8; i++) {
		if (args[0] == g_scriptEvents[i].evnt && *g_scriptEvents[i].toggle) {
			sendLog(consoleWhiteOnBlack, "Event Protections", "%s Event from %s", g_scriptEvents[i].name, sender->m_player_info->m_net_player_data.m_name);
			return true;
		}
	}
	return false;
}
void (*ogReceivedEvent)(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, uint16_t id, int idx, int handledBitset, int bufferSize, struct datBitBuffer* buffer);
void receivedEventHk(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, uint16_t id, int idx, int handledBitset, int bufferSize, struct datBitBuffer* buffer) {
	char const* eventName = *(char const**)(eventMgr + 8ui64 * id + 0x3B6B0);
	if (eventName == NULL || source == NULL || source->m_player_id < 0 || source->m_player_id >= 32 || !NETWORK_NETWORK_IS_SESSION_ACTIVE()) {
		g_pointers.m_sendEventAck(eventMgr, source, target, id, handledBitset);
		return;
	}
	switch (id) {
	case _CScriptedGameEvent: {
		struct CScriptedGameEvent* sge = malloc(sizeof(struct CScriptedGameEvent));
		buffer_ReadDword(buffer, &sge->m_args_size, 0x20);
		if (sge->m_args_size - 1 <= 0x1AF)
			buffer_ReadArray(buffer, &sge->m_args, 8 * sge->m_args_size);
		bool res = scriptedGameEvent(sge, source);
		free((void*)sge);
		if (res) {
			g_pointers.m_sendEventAck(eventMgr, source, target, id, handledBitset);
			return;
		}
		buffer_Seek(buffer, 0);
	} break;
	}
	return ogReceivedEvent(eventMgr, source, target, id, idx, handledBitset, bufferSize, buffer);
}

bool getMsgType(enum eNetMessage* msgType, datBitBuffer* buffer) {
	auto pos = 0;
	uint32_t magic, length, extended;
	if ((buffer->m_flagBits & 2) != 0 || (buffer->m_flagBits & 1) == 0 ? (pos = buffer->m_curBit) : (pos = buffer->m_maxBit), buffer->m_bitsRead + 15 > pos || !buffer_ReadDword(buffer, &magic, 14) || magic != 0x3246 || !buffer_ReadDword(buffer, &extended, 1)) {
		*msgType = CMsgInvalid;
		return false;
	}
	length = extended ? 16 : 8;
	uint32_t msgT;
	if ((buffer->m_flagBits & 1) == 0 ? (pos = buffer->m_curBit) : (pos = buffer->m_maxBit), length + buffer->m_bitsRead <= pos && buffer_ReadDword(buffer, &msgT, length)) {
		*msgType = msgT;
		return true;
	}
	else
		return false;
}
CNetGamePlayer* getPlayerFromHostToken(uint64_t val) {
	CNetworkPlayerMgr* npm = *g_pointers.m_networkPlayerMgr;
	if (npm != 0 && npm->m_player_count != 0) {
		for (int i = 0; i < npm->m_player_count; i++) {
			if (npm->m_player_list[i]) {
				if (npm->m_player_list[i]->m_netPlayer && npm->m_player_list[i]->m_netPlayer->is_valid()) {
					if (npm->m_player_list[i]->m_player_info->m_net_player_data.m_host_token == val)
						return npm->m_player_list[i];
				}
			}
		}
	}
	return NULL;
}
CNetGamePlayer* getPlayerFromMsgID(uint32_t val) {
	CNetworkPlayerMgr* npm = *g_pointers.m_networkPlayerMgr;
	if (npm != 0 && npm->m_player_count != 0) {
		for (int i = 0; i < npm->m_player_count; i++) {
			if (npm->m_player_list[i]) {
				if (npm->m_player_list[i]->m_netPlayer && npm->m_player_list[i]->m_netPlayer->is_valid()) {
					if (npm->m_player_list[i]->m_msg_id == val)
						return npm->m_player_list[i];
				}
			}
		}
	}
	return NULL;
}
bool(*ogReceivedNetMessage)(void* netConnectionMgr, void* unk, InFrame* frame);
bool receivedNetMessageHk(void* netConnectionMgr, void* unk, InFrame* frame) {
	if (frame->m_vtbl->get_type() == 4) {
		struct datBitBuffer* buffer = malloc(sizeof(struct datBitBuffer));
		init_datBitBuffer(buffer, (uint8_t*)frame->m_data, frame->m_length);
		enum eNetMessage msgType;
		buffer->m_flagBits = 1;
		CNetGamePlayer* sender = getPlayerFromMsgID(frame->m_msg_id);
		if (sender && getMsgType(&msgType, buffer)) {
			switch (msgType) {
			case CMsgNetComplaint: {
				uint64_t hostToken = NULL;
				buffer_ReadQWord(buffer, &hostToken, 0x40);
				uint32_t numberOfHostTokens = NULL;
				buffer_ReadDword(buffer, &numberOfHostTokens, 0x20);
				if (numberOfHostTokens <= 64) {
					//We only need the first element, so we only need to grab one
					uint64_t arrayElement = NULL;
					buffer_ReadQWord(buffer, &arrayElement, 0x40);
					if (arrayElement != NULL)
						getPlayerFromHostToken(arrayElement)->m_complaints = USHRT_MAX;
				}
				buffer_Seek(buffer, 0);
				sendLog(consoleWhiteOnBlack, "Event Protections", "Desync Kick from %s", getPlayerFromHostToken(hostToken)->m_player_info->m_net_player_data.m_name);
				free((void*)buffer);
				return false;
			} break;
			case CMsgTextMessage: {
				char const* ss; //I really don't feel like creating another signature for strings, so we can just do this instead :)
				int const textLen = buffer_ReadBits(buffer, buffer_ReadBits(buffer, 1) ? 15 : 7);
				for (int i = 0; i < textLen; i++)
					ss += (char)buffer_ReadBits(buffer, 8);
				uint64_t senderPeerId;
				buffer_ReadQWord(buffer, &senderPeerId, 0x20);
				bool unk = buffer_ReadBits(buffer, 1);
				sendLog(consoleWhiteOnBlack, "Event Protections", "%s: %s", sender->m_player_info->m_net_player_data.m_name, unk, ss);
				free((void*)buffer);
			} break;
			}
		}
		else {
			//Ensure buffer is freed, otherwise we create a memory leak.
			if (buffer)
				free((void*)buffer);
		}
	}
	return ogReceivedNetMessage(netConnectionMgr, unk, frame);
}

void initHooks() {
	lbls_addText("HUD_JOINING", "Isn't BigBaseC the fucking best?");
	lbls_addText("HUD_TRANSP", "Isn't BigBaseC the fucking best?");
	if (MH_CreateHook((LPVOID)g_pointers.m_scrThreadRun, (LPVOID)&scrThreadRunHk, (LPVOID)&ogScrThreadRun) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook STR");
	if (MH_CreateHook((LPVOID)g_pointers.m_getLabelText, (LPVOID)&getLabelTextHk, (LPVOID)&ogGetLabelText) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook GLT");
	if (MH_CreateHook((LPVOID)g_pointers.m_receivedEvent, (LPVOID)&receivedEventHk, (LPVOID)&ogReceivedEvent) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook RE");
	if (MH_CreateHook((LPVOID)g_pointers.m_receivedNetMessage, (LPVOID)&receivedNetMessageHk, (LPVOID)&ogReceivedNetMessage) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook RNM");
	MH_EnableHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Enabled all hooks");
}
void uninitHooks() {
	MH_DisableHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Disabled all hooks");
	MH_RemoveHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Removed all hooks");
}