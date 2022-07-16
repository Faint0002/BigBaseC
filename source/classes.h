#pragma once
#include "pointers.h"

typedef struct r_vector2 { float x; float y; } r_vector2;
typedef struct r_vector3 { float x; float y; float z; } r_vector3;
typedef struct r_vector4 { float x; float y; float z; float w; } r_vector4;

typedef struct GtaThread GtaThread;
typedef struct GtaThreadVtbl {
	void* (*__vecDelDtor)(unsigned int);
	int(*Reset)(uint32_t scriptHash, void* args, uint32_t arg_count);
	int(*Run)();
	int(*Tick)(uint32_t ops_to_execute);
	void(*Kill)();
} GtaThreadVtbl;
struct GtaThread {
	struct GtaThreadVtbl* vfptr;
	uint32_t thread_id;
	uint32_t script_hash;
};
typedef struct atArray {
	uintptr_t* m_data;
	uint16_t m_size;
	uint16_t m_capacity;
} atArray;

typedef struct CPedFactory {
	char pad_0000[8]; //0x0000
	struct CPed* m_local_ped; //0x0008
} CPedFactory;

typedef struct CPedModelInfo {
	char pad_0000[24]; //0x0000
	uint32_t m_model_hash; //0x0018
} CPedModelInfo; //Size: 0x001C

typedef struct posBase {
	char pad_0000[80]; //0x0000
	struct r_vector3 m_pos; //0x0050
} posBase; //Size: 0x005C

#pragma pack(push, 1)
typedef struct CPed {
	char pad_0000[32]; //0x0000
	struct CPedModelInfo* m_ped_model_info; //0x0020
	uint8_t m_entity_type; //0x0028
	char pad_0029[3]; //0x0029
	uint8_t m_invisible; //0x002C
	char pad_002D[1]; //0x002D
	uint8_t m_freeze_momentum; //0x002E
	char pad_002F[1]; //0x002F
	posBase* m_posbase; //0x0030
	char pad_0038[88]; //0x0038
	struct r_vector3 m_camera; //0x0090
	char pad_009C[237]; //0x009C
	uint8_t m_godmode; //0x0189
	char pad_018A[2]; //0x018A
	uint8_t m_hostility; //0x018C
	char pad_018D[243]; //0x018D
	float m_health; //0x0280
	char pad_0284[28]; //0x0284
	float m_maxhealth; //0x02A0
	char pad_02A4[124]; //0x02A4
	struct r_vector3 m_velocity; //0x0320
	char pad_032C[2564]; //0x032C
	struct CAutomobile* m_vehicle; //0x0D30
	char pad_0D38[912]; //0x0D38
	struct CPlayerInfo* m_player_info; //0x10C8
	char pad_10D0[8]; //0x10D0
	uintptr_t m_weapon_manager; //0x10D8
	char pad_10E0[907]; //0x10E0
	uint8_t m_ped_task_flag; //0x146B
	char pad_146C[196]; //0x146C
	float m_armor; //0x1530
} CPed; //Size: 0x1534
#pragma pack(pop)

typedef struct CNavigation {
	char pad_0000[32]; //0x0000
	float m_heading; //0x0020
	float m_heading2; //0x0024
	char pad_0028[8]; //0x0028
	struct r_vector3 m_rotation; //0x0030
	char pad_003C[20]; //0x003C
	struct r_vector3 m_position; //0x0050
} CNavigation; //Size: 0x005C

typedef struct CBaseModelInfo {
	char pad_0000[0x18]; //0x0000
	uint32_t m_model; //0x0018
	char pad_001C[0x81]; //0x001C
	BYTE m_model_type; //0x009D
	char pad_009D[0x2A2]; //0x009E
	int32_t m_handling_type; //0x0340
} CBaseModelInfo; //Size: 0x0344

#pragma pack(push, 4)
typedef struct fwEntity {
	char pad_0000[32]; //0x0000
	struct CBaseModelInfo* m_model_info; //0x0020
	char pad_0028[1]; //0x0028
	int8_t m_entity_type; //0x0029
	char pad_002A[2]; //0x002A
	uint8_t m_invisible; //0x002C
	char pad_002D[3]; //0x002D
	struct CNavigation* m_navigation; //0x0030
	char pad_0038[16]; //0x0038
	uintptr_t m_draw_data; //0x0048
	char pad_0050[128]; //0x0050
	uintptr_t m_net_object; //0x00D0
	char pad_00D8[176]; //0x00D8
	uint32_t m_damage_bits; //0x0188
} fwEntity; //Size: 0x018C
#pragma pack(pop)

typedef struct CAutomobile {
	char pad_018C[244]; //0x018C
	float m_health; //0x0280
	char pad_0284[28]; //0x0284
	float m_health_max; //0x02A0
	char pad_02A4[116]; //0x02A4
	uint8_t m_boost_state; //0x0318
	char pad_0319[2]; //0x0319
	uint8_t m_boost_allow_recharge; //0x031B
	char pad_031C[4]; //0x031C
	float m_boost; //0x0320
	float m_rocket_recharge_speed; //0x0324
	char pad_0328[136]; //0x0328
	float m_jump_boost_charge; //0x03B0
	char pad_03B4[1164]; //0x03B4
	float m_body_health; //0x0840
	float m_petrol_tank_health; //0x0844
	char pad_0848[192]; //0x0848
	float m_engine_health; //0x0908
	char pad_090C[44]; //0x090C
	uintptr_t m_handling; //0x0938
	char pad_0940[2]; //0x0940
	uint8_t m_is_drivable; //0x0942
	uint8_t m_tyres_can_burst; //0x0943
	uint8_t m_deform_god; //0x0944
	char pad_0945[179]; //0x0945
	float m_dirt_level; //0x09F8
	char pad_09FC[194]; //0x09FC
	uint8_t m_is_targetable; //0x0ABE
	char pad_0ABF[413]; //0x0ABF
	float m_gravity; //0x0C5C
	char pad_0C60[8]; //0x0C60
	struct CPed* m_driver; //0x0C68
	struct CPed* m_passengers[15]; //0x0C70
	struct CPed* m_last_driver; //0x0CE8
} CAutomobile; //Size: 0x0CF0

enum eFrameFlags {
	eFrameFlagExplosiveAmmo = 1 << 11,
	eFrameFlagFireAmmo = 1 << 12,
	eFrameFlagExplosiveMelee = 1 << 13,
	eFrameFlagSuperJump = 1 << 14,
};
typedef struct netAddress {
	uint8_t m_field1;
	uint8_t m_field2;
	uint8_t m_field3;
	uint8_t m_field4;
} netAddress;
typedef struct netPlayerData {
	char pad_0000[8]; //0x0000
	int64_t m_rockstar_id; //0x0008
	char pad_0010[52]; //0x0010
	struct netAddress m_relay_ip; //0x0044
	uint16_t m_relay_port; //0x0048
	char pad_004A[2]; //0x004A
	struct netAddress m_external_ip; //0x004C
	uint16_t m_external_port; //0x0050
	char pad_0052[2]; //0x0052
	struct netAddress m_internal_ip; //0x0054
	uint16_t m_internal_port; //0x0058
	char pad_005A[6]; //0x005A
	uint64_t m_host_token; //0x0060
	uint64_t m_peer_id; //0x0068
	int64_t m_rockstar_id2; //0x0070
	char pad_0078[12]; //0x0078
	char m_name[20]; //0x0084
} rlGamerInfo; //Size: 0x0098

#pragma pack(push, 1)
typedef struct CPlayerInfo {
	char pad_0000[32]; //0x0000
	struct netPlayerData m_net_player_data; //0x0020
	char pad_00B8[184]; //0x00B8
	float m_swim_speed; //0x0170
	char pad_0174[20]; //0x0174
	uint32_t m_water_proof; //0x0188
	char pad_018C[92]; //0x018C
	struct CPed* m_ped; //0x01E8
	char pad_01F0[40]; //0x01F0
	enum eFrameFlags m_frame_flags; //0x0218
	char pad_021C[52]; //0x021C
	uint32_t m_player_controls; //0x0250
	char pad_0254[1256]; //0x0254
	float m_wanted_can_change; //0x073C
	char pad_0740[304]; //0x0740
	uint32_t m_npc_ignore; //0x0870
	char pad_0874[12]; //0x0874
	bool m_is_wanted; //0x0880
	char pad_0881[7]; //0x0881
	uint32_t m_wanted_level; //0x0888
	uint32_t m_wanted_level_display; //0x088C
	char pad_0890[1120]; //0x0890
	float m_run_speed; //0x0CF0
	float m_stamina; //0x0CF4
	float m_stamina_regen; //0x0CF8
	char pad_0CFC[16]; //0x0CFC
	float m_weapon_damage_mult; //0x0D0C
	float m_weapon_defence_mult; //0x0D10
	char pad_0D14[4]; //0x0D14
	float m_melee_weapon_damage_mult; //0x0D18
	float m_melee_damage_mult; //0x0D1C
	float m_melee_defence_mult; //0x0D20
	char pad_0D24[8]; //0x0D24
	float m_melee_weapon_defence_mult; //0x0D2C
} CPlayerInfo; //Size: 0x0D30
#pragma pack(pop)

typedef struct nonPhysicalPlayerDataBase nonPhysicalPlayerDataBase;
typedef struct netPlayer netPlayer;
typedef struct CNetGamePlayer CNetGamePlayer;
typedef struct netPlayerMgrBase netPlayerMgrBase;
typedef struct nonPhysicalPlayerDataBase {
	void*(*__vecDelDtor)(unsigned int);
	void(*_0x08)();
	void(*_0x10)();
	void(*_0x18)();
	void(*log)();
} nonPhysicalPlayerDataBase; //Size: 0x0008
typedef struct CNonPhysicalPlayerData {
	struct nonPhysicalPlayerDataBase* m_nonPhysicalPlayerDataBase; //0x0000
	int32_t m_bubble_id; //0x0008
	int32_t m_player_id; //0x000C
	struct r_vector3 m_position; //0x0010
} CNonPhysicalPlayerData; //Size: 0x001C
typedef struct netPlayer {
	void*(*__vecDelDtor)(unsigned int);
	void(*reset)();
	bool(*is_valid)();
	const char*(*get_name)();
	void(*_0x20)();
	bool(*is_host)();
	struct netPlayerData*(*get_net_data)();
	void(*_0x38)();
} netPlayer; //Size: 0x0008
typedef struct CNetGamePlayer {
	struct netPlayer* m_netPlayer; //0x0000
	char pad_0008[8]; //0x0008
	struct CNonPhysicalPlayerData* m_non_physical_player; //0x0010
	uint32_t m_msg_id; //0x0018
	char pad_001C[4]; //0x001C
	uint8_t m_active_id; //0x0020
	uint8_t m_player_id; //0x0021
	char pad_0022[124]; //0x0022
	uint16_t m_complaints; //0x0025
	struct CPlayerInfo* m_player_info; //0x00A0
} CNetGamePlayer; //Size: 0x00A8

typedef struct netPlayerMgrBase {
	void*(*__vecDelDtor)(netPlayerMgrBase* this, unsigned int);
	void(*Initialize)();
	void(*Shutdown)();
	void(*unk_0x18)();
	CNetGamePlayer*(*AddPlayer_raw)(void* a1, void* a2, void* a3, struct netPlayerData* net_player_data, struct CNonPhysicalPlayerData* non_physical_player_data);
	void(*RemovePlayer)(CNetGamePlayer* net_game_player);
	void(*UpdatePlayerListsForPlayer)(CNetGamePlayer* net_game_player);
	CNetGamePlayer*(*AddPlayer)(void* a1, void* a2, void* a3, struct netPlayerData* net_player_data, struct CNonPhysicalPlayerData* non_physical_player_data);
}netPlayerMgrBase; //Size: 0x0008
typedef struct CNetworkPlayerMgr {
	struct netPlayerMgrBase* m_netPlayerMgrBase; //0x0000
	char pad_0008[224]; //0x0008
	struct CNetGamePlayer* m_local_net_player; //0x00E8
	char pad_00F0[144]; //0x00F0
	struct CNetGamePlayer* m_player_list[32]; //0x0180
	uint16_t m_player_limit; //0x0280
	char pad_0282[10]; //0x0282
	uint16_t m_player_count; //0x028C
} CNetworkPlayerMgr; //Size: 0x028E

typedef struct netGameEvent {
	void*(*__vecDelDtor)(struct netGameEvent* this, unsigned int);
	const char*(*get_name)();
	bool(*is_in_scope)(netPlayer* player);
	bool(*time_to_resend)(uint32_t time);
	bool(*can_change_scope)();
	void(*prepare_data)(struct datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player);
	void(*handle_data)(struct datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player);
	bool(*decide)(netPlayer* source_player, netPlayer* target_player);
	void(*prepare_reply)(struct datBitBuffer* buffer, netPlayer* reply_player);
	void(*handle_reply)(struct datBitBuffer* buffer, netPlayer* souce_player);
	void(*prepare_extra_data)(struct datBitBuffer* buffer, bool is_reply, netPlayer* source_player, netPlayer* target_player);
	void(*handle_extra_data)(struct datBitBuffer* buffer, bool is_reply, netPlayer* source_player, netPlayer* target_player);
	void(*unk_0x60)();
	void(*unk_0x68)();
	void(*unk_0x70)();
	void(*unk_0x78)();
	void(*unk_0x80)();
	void(*unk_0x88)();
	bool(*must_persist)();
	bool(*must_persist_when_out_of_scope)();
	bool(*has_timed_out)();
	uint16_t m_id; //0x0008
	bool m_requires_reply; //0x000A
	char m_padding1[0x05]; //0x000B
	netPlayer* m_source_player; //0x0010
	netPlayer* m_target_player; //0x0018
	uint32_t m_resend_time; //0x0020
	uint16_t m_0x24; //0x0024
	uint8_t m_0x26; //0x0026
	uint8_t m_0x27; //0x0027
	uint32_t m_0x28; //0x0028
	char m_padding2[0x04];
} netGameEvent;
typedef struct CScriptedGameEvent {
	netGameEvent* m_netGameEvent; //0x0000
	char m_padding[0x40]; //0x0030
	int64_t m_args[54]; //0x0070
	uint32_t m_bitset; //0x0220
	uint32_t m_args_size; //0x0224
} CScriptedGameEvent;
typedef struct CNetworkIncrementStatEvent {
	netGameEvent* m_netGameEvent; //0x0000
	uint32_t m_stat; //0x0030
	uint32_t m_amount; //0x0034
} CNetworkIncrementStatEvent;
typedef struct datBitBuffer {
	uint8_t* m_data; //0x0000
	uint32_t m_bitOffset; //0x0008
	uint32_t m_maxBit; //0x000C
	uint32_t m_bitsRead; //0x0010
	uint32_t m_curBit; //0x0014
	uint32_t m_highestBitsRead; //0x0018
	uint8_t m_flagBits; //0x001C
} datBitBuffer;
inline void init_datBitBuffer(struct datBitBuffer* buffer, uint8_t* data, uint32_t size) {
	buffer->m_data = data;
	buffer->m_bitOffset = 0;
	buffer->m_maxBit = size * 8;
	buffer->m_bitsRead = 0;
	buffer->m_curBit = 0;
	buffer->m_highestBitsRead = 0;
	buffer->m_flagBits = 0;
}
inline uint32_t buffer_GetPosition(struct datBitBuffer* buffer) {
	return buffer->m_bitsRead;
}
inline bool buffer_Seek(struct datBitBuffer* buffer, uint32_t bits) {
	if (bits >= 0) {
		uint32_t length = (buffer->m_flagBits & 1) ? buffer->m_maxBit : buffer->m_curBit;
		if (bits <= length)
			buffer->m_bitsRead = bits;
	}
	return false;
}
inline uint64_t buffer_ReadBits(struct datBitBuffer* buffer, size_t numBits) {
	uint32_t const totalBits = (buffer->m_flagBits & 1) ? buffer->m_maxBit : buffer->m_curBit;
	if ((buffer->m_flagBits & 2) || buffer->m_bitsRead + numBits > totalBits)
		return 0;
	uint32_t const bufPos = buffer->m_bitsRead + buffer->m_bitOffset;
	uint32_t const initialBitOffset = bufPos & 0b111;
	uint8_t* const start = &buffer->m_data[bufPos / 8];
	uint8_t* const next = &start[1];
	int result = (start[0] << initialBitOffset) & 0xff;
	for (auto i = 0; i < (numBits - 1) / 8; i++) {
		result <<= 8;
		result |= next[i] << initialBitOffset;
	}
	if (initialBitOffset)
		result |= next[0] >> (8 - initialBitOffset);
	buffer->m_bitsRead += numBits;
	if (buffer->m_bitsRead > buffer->m_highestBitsRead)
		buffer->m_highestBitsRead = buffer->m_bitsRead;
	return result >> ((8 - numBits) % 8);
}
inline int buffer_GetDataLength(struct datBitBuffer* buffer) {
	int leftoverBit = (buffer->m_curBit % 8) ? 1 : 0;
	return (buffer->m_curBit / 8) + leftoverBit;
}
inline bool buffer_ReadByte(struct datBitBuffer* buffer, uint8_t* integer, int bits) {
	uint32_t read;
	if (g_pointers.m_readBitbufferDword(buffer, &read, bits)) {
		*integer = read;
		return true;
	}
	return false;
}
inline bool buffer_ReadWord(struct datBitBuffer* buffer, uint16_t* integer, int bits) {
	uint32_t read;
	if (g_pointers.m_readBitbufferDword(buffer, &read, bits)) {
		*integer = read;
		return true;
	}
	return false;
}
inline bool buffer_ReadDword(struct datBitBuffer* buffer, uint32_t* integer, int bits) {
	return g_pointers.m_readBitbufferDword(buffer, integer, bits);
}
inline bool ReadInt32(struct datBitBuffer* buffer, int32_t* integer, int bits) {
	int32_t v8;
	int32_t v9;
	if (buffer_ReadDword(buffer, (uint32_t*)&v8, 1u) && buffer_ReadDword(buffer, (uint32_t*)&v9, bits - 1)) {
		*integer = v8 + (v9 ^ -v8);
		return true;
	}
	return false;
}
inline bool buffer_ReadQWord(struct datBitBuffer* buffer, uint64_t* integer, int bits) {
	if (bits <= 32) {
		uint32_t v10;
		if (buffer_ReadDword(buffer, &v10, bits)) {
			*integer = v10;
			return true;
		}
	}
	else {
		uint32_t v10, v11;
		if (buffer_ReadDword(buffer, &v11, 32u) && buffer_ReadDword(buffer, &v10, bits - 32u)) {
			*integer = v11 | ((uint64_t)v10 << 32);
			return true;
		}
	}
	return false;
}
inline bool buffer_ReadInt64(struct datBitBuffer* buffer, int64_t* integer, int bits) {
	uint32_t v8;
	uint64_t v9;
	if (buffer_ReadDword(buffer, &v8, 1u) && buffer_ReadQWord(buffer, &v9, bits - 1)) {
		*integer = v8 + (v9 ^ -(int64_t)v8);
		return true;
	}
	return false;
}
inline bool buffer_ReadArray(struct datBitBuffer* buffer, PVOID array, int size) {
	return g_pointers.m_readBitbufferArray(buffer, array, size, 0);
}

typedef struct InFrame InFrame;
typedef struct InFrameVtbl InFrameVtbl;
struct InFrameVtbl {
	void* (*__vecDelDtor)(unsigned int);
	void(*destroy)();
	uint32_t(*get_type)();
	uint32_t(*_0x18)();
};
typedef struct InFrame {
	InFrameVtbl* m_vtbl; //0x0000
	char pad_0008[56]; //0x0008
	uint32_t m_msg_id; //0x0040
	char pad_0044[4]; //0x0044
	InFrame* m_this; //0x0048
	char pad_0050[40]; //0x0050
	uint32_t m_length; //0x0078
	char pad_007C[4]; //0x007C
	void* m_data; //0x0080
} InFrame;