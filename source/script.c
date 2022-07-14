#include "script.h"
#include "classes.h"
#include "invoker.h"
#include "natives.h"
#include "logger.h"
#include "gui.h"
#include "pointers.h"
#include "globals.h"
int g_selectedPlayer = 0;
fbr g_mainFbr;

void notifyleft(const char* message, int timeout) {
	UI__SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI_ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(message);
	UI__DRAW_NOTIFICATION(timeout * 100, true);
}
void initializeMenu() {
	forwardMenu(mainmenu, "Home");
	g_current = g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * 1);
	notifyleft("Welcome to BigBaseC. Open with INS or LB + RB", 17);
}

void selectedplayermenu() {
	if (drawOption("Placeholder", ""))
		g_running = false;
}
void playersmenu() {
	CNetworkPlayerMgr* npm = *g_pointers.m_networkPlayerMgr;
	if (npm != 0 && npm->m_player_count != 0) {
		for (int i = 0; i < npm->m_player_count; i++) {
			if (npm->m_player_list[i]) {
				if (npm->m_player_list[i]->m_netPlayer && npm->m_player_list[i]->m_netPlayer->is_valid()) {
					if (drawSub(npm->m_player_list[i]->m_player_info->m_net_player_data.m_name, "", selectedplayermenu))
						g_selectedPlayer = i;
				}
			}
		}
	}
	else {
		if (drawSub(PLAYER_GET_PLAYER_NAME(0), "", selectedplayermenu))
			g_selectedPlayer = 0;
	}
}
void settingsmenu() {
	drawFloat("X Pos", "", &g_posX, 0.f, 0.88f, 0.01f);
	drawFloat("Y Pos", "", &g_posY, 0.f, 1.f, 0.01f);
	if (drawOption("Unload", "Unloads the menu"))
		g_running = false;
}
void mainmenu() {
	drawSub("Players", "", playersmenu);
	drawSub("Settings", "", settingsmenu);
	if (drawOption("Suicide", "")) {
		struct CPed* cPed = (*g_pointers.m_pedFactory)->m_local_ped;
		cPed->m_health = 0.f;
	}
}

void scrMain() {
	initializeMenu();
	while (true) {
		inputHandler();
		if (g_menuLevel != 0 && g_opened) {
			HUD_DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME();
			GRAPHICS_SET_SCRIPT_GFX_DRAW_ORDER(8);
			GRAPHICS_FORCE_RENDER_IN_GAME_UI(true);
			GRAPHICS_SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(true);
			drawTitle("BigBase");
			g_currentMenu();
			drawSubtitle(g_currentSubmenu);
			drawEnd();
			drawDescription();
		}
		fbrYield(&g_mainFbr, 0);
	}
}

void initScr() {
	fbrInit(&g_mainFbr, &scrMain);
}
void uninitScr() {
	fbrUninit(&g_mainFbr);
}
