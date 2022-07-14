#include "gui.h"
#include "fiber.h"
#include "script.h"
#include "natives.h"

bool g_opened = true;
//Positoning
float g_posX = 0.15f;
float g_posY = 0.01f;
float g_width = 0.22f;
//Colors
RGBA g_fontColor = { 255, 255, 255, 255 };
RGBA g_rectColor = { 255, 190, 255, 255 };
RGBA g_subtitleColor = { 0, 0, 0, 220 };
RGBA g_subtitleTextColor = { 255, 255, 255, 255 };
RGBA g_submenuarrowColor = { 255, 255, 255, 255 };
RGBA g_submenuarrowSelectedColor = { 0, 0, 0, 255 };
RGBA g_optionText = { 255, 255, 255, 255 };
RGBA g_selectedOptionText = { 0, 0, 0, 255 };
RGBA g_optionColor = { 0, 0, 0, 150 };
RGBA g_scrollerColor = { 255, 255, 255, 255 };
RGBA g_footerColor = { 10, 10, 10, 200 };
RGBA g_descriptionColor = { 10, 10, 10, 255 };
//Keypresses
bool g_selectPressed = FALSE;
bool g_leftPressed = FALSE;
bool g_rightPressed = FALSE;
int m_delay = 150;
int g_previousTick = 0;
//Smooth scroll handling
float g_target = 0.f, g_current = 0.f, g_speed = 0.1281f;
//Option handling
int g_maxVisOptions = 16;
int g_optionCount = 0;
int g_currentOption = 0;
int g_menuLevel = 0;
void(*g_currentMenu)();
void(*g_menuArray[1000])();
int g_optionArray[1000];
char const* g_currentSubmenu = "";
char const* g_submenuArray[1000];
char const* g_currentDescription = "";

char const* charKeyboard(char const* windowName, int maxInput, char const* defaultText) {
	GAMEPLAY_DISPLAY_ONSCREEN_KEYBOARD(0, windowName, "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY_UPDATE_ONSCREEN_KEYBOARD() == 0)
		WAIT(0);
	if (!GAMEPLAY_GET_ONSCREEN_KEYBOARD_RESULT())
		return "";
	return GAMEPLAY_GET_ONSCREEN_KEYBOARD_RESULT();
}
char const* toString(int value) {
	static char strData[16];
	snprintf(strData, 16, "%i", value);
	return strData;
}
char const* toStringFloat(float value) {
	static char strData[16];
	snprintf(strData, 16, "%.2f", value);
	return strData;
}
char const* getText(int currentValue, int max) {
	static char opText[12];
	snprintf(opText, sizeof(opText), "%i/%i", currentValue, max);
	return opText;
}
char const* getTextFloat(float currentValue, float max) {
	static char opText[12];
	snprintf(opText, sizeof(opText), "%.2f/%.2f", currentValue, max);
	return opText;
}
char const* toUpper(char const* text) {
	static char newText[256];
	memset(newText, NULL, 256);
	for (int i = 0; i < strlen(text); i++)
		newText[i] = (char)toupper(text[i]);
	return newText;
}
float getTextWidth(char const* text, int32_t font, float scaleOverride) {
	UI__BEGIN_TEXT_COMMAND_WIDTH("STRING");
	UI_ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(text);
	float scale = 0.35f;
	UI_SET_TEXT_FONT(0);
	if (font != -1) {
		scale = scaleOverride;
		UI_SET_TEXT_FONT(font);
	}
	UI_SET_TEXT_SCALE(0.0f, scale);
	return UI__END_TEXT_COMMAND_GET_WIDTH(true);
}
void drawText(char const* text, RGBA color, Vector2 position, Vector2 size, int font) {
	UI_SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
	UI_SET_TEXT_SCALE(size.x, size.y);
	UI_SET_TEXT_FONT(font);
	UI_SET_TEXT_EDGE(true, 0, 0, 0, 0);
	UI_BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI_ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI_END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
void drawSprite(char const* dict, char const* texture, Vector2 pos, Vector2 size, float rotation, RGBA color) {
	int screenRes[2];
	GRAPHICS__GET_ACTIVE_SCREEN_RESOLUTION(&screenRes[0], &screenRes[1]);
	float aspect = GRAPHICS__GET_ASPECT_RATIO(0);
	float factor = SYSTEM_TO_FLOAT(screenRes[0]) / SYSTEM_TO_FLOAT(screenRes[1]);
	float scale = factor / aspect;
	Vector3 textureRes = GRAPHICS_GET_TEXTURE_RESOLUTION(dict, texture);
	textureRes.x = (textureRes.x * (0.5f / scale)), textureRes.y = (textureRes.y * (0.5f / scale));
	if (!GRAPHICS_HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		GRAPHICS_REQUEST_STREAMED_TEXTURE_DICT(dict, false);
	else
		GRAPHICS_DRAW_SPRITE(dict, texture, pos.x, pos.y, ((textureRes.x / 1280.0f) * scale) * size.x, ((textureRes.y / 720.0f) * scale) * size.y, rotation, color.r, color.g, color.b, color.a);
}
void drawRect(RGBA color, Vector2 position, Vector2 size) {
	GRAPHICS_DRAW_RECT(position.x, position.y, size.x, size.y, color.r, color.g, color.b, color.a);
}
void updateScroller() {
	if (g_current != g_target)
		g_current = g_current * (1 - g_speed) + g_target * g_speed;
	if ((g_current > g_target - 0.0005) && (g_current < g_target + 0.0005))
		g_current = g_target;
}
void forwardMenu(void(*menu)(), char const* submenu) {
	g_menuArray[g_menuLevel] = g_currentMenu;
	g_submenuArray[g_menuLevel] = g_currentSubmenu;
	g_optionArray[g_menuLevel] = g_currentOption;
	g_menuLevel++;
	g_currentMenu = menu;
	g_currentSubmenu = submenu;
	g_currentOption = 1;
}
void backMenu() {
	g_menuLevel--;
	g_currentMenu = g_menuArray[g_menuLevel];
	g_currentSubmenu = g_submenuArray[g_menuLevel];
	g_currentOption = g_optionArray[g_menuLevel];
}
void drawTitle(char const* title) {
	drawRect(g_rectColor, Vector2(g_posX, g_posY + 0.07f), Vector2(g_width, 0.1f));
	drawText(title, g_fontColor, Vector2((g_posX - 0.001f) - getTextWidth(title, -1, 0.f), g_posY + 0.04f), Vector2(1.f, 1.f), 1);
	CONTROLS_DISABLE_CONTROL_ACTION(2, 27, true);
}
void drawSubtitle(char const* title) {
	char const* upperTitle = toUpper(title);
	drawRect(g_subtitleColor, Vector2(g_posX, g_posY + 0.1f + 0.04f), Vector2(g_width, 0.04f));
	drawText(upperTitle, g_subtitleTextColor, Vector2(g_posX - 0.1045f, g_posY + 0.1f + 0.04f - 0.015f), Vector2(0.4f, 0.4f), 0);
	char const* text = getText(g_currentOption, g_optionCount);
	drawText(text, g_subtitleTextColor, Vector2(g_posX + (g_width - 0.115f) - getTextWidth(text, -1, 0.f), g_posY + 0.1f + 0.04f - 0.015f), Vector2(0.4f, 0.4f), 0);
}
bool drawOption(char const* option, char const* description) {
	g_optionCount++;
	bool onThis = g_currentOption == g_optionCount ? true : false;
	int opCountChecks = g_currentOption > g_maxVisOptions ? g_maxVisOptions : g_optionCount;
	GRAPHICS_SET_SCRIPT_GFX_DRAW_ORDER(7);
	drawRect(g_optionColor, Vector2(g_posX, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * opCountChecks)), Vector2(g_width, 0.035f));
	GRAPHICS_SET_SCRIPT_GFX_DRAW_ORDER(8);
	if (onThis) {
		g_target = g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * opCountChecks);
		updateScroller();
		drawRect(g_scrollerColor, Vector2(g_posX, g_current), Vector2(g_width, 0.035f));
	}
	drawText(option, onThis ? g_selectedOptionText : g_optionText, Vector2(g_posX - 0.105f, g_posY + 0.1f + 0.04f + (0.035f * opCountChecks) - 0.01f), Vector2(0.35f, 0.35f), 0);
	if (g_currentOption == g_optionCount) {
		g_currentDescription = description;
		if (g_selectPressed)
			return true;
	}
	return false;
}
bool drawSub(char const* option, char const* description, void(*sub)()) {
	drawOption(option, description);
	bool onThis = g_currentOption == g_optionCount ? true : false;
	int opCountChecks = g_currentOption > g_maxVisOptions ? g_maxVisOptions : g_optionCount;
	drawText(">", onThis ? g_submenuarrowSelectedColor : g_submenuarrowColor, Vector2(g_posX + (g_width - 0.113f) - getTextWidth(">", -1, 0.f), g_posY + 0.1f + 0.04f - 0.015f + (0.035f * opCountChecks)), Vector2(0.5f, 0.5f), 4);
	if (g_currentOption == g_optionCount)
		if (g_selectPressed) {
			forwardMenu(sub, option);
			return true;
		}
	return false;
}
bool drawToggle(char const* option, char const* description, bool* toggle) {
	drawOption(option, description);
	bool onThis = g_currentOption == g_optionCount ? true : false;
	int opCountChecks = g_currentOption > g_maxVisOptions ? g_maxVisOptions : g_optionCount;
	char const* text = *toggle ? "~g~ON" : "~r~OFF";
	drawText(text, g_optionText, Vector2(g_posX + (g_width - 0.112f) - getTextWidth(text, -1, 0.f), g_posY + 0.1f + 0.04f - 0.0115f + (0.035f * opCountChecks)), Vector2(0.35f, 0.35f), 0);
	if (g_currentOption == g_optionCount)
		if (g_selectPressed) {
			*toggle = !*toggle;
			return true;
		}
	return false;
}
bool drawInt(char const* option, char const* description, int* inttochange, int min, int max, int step) {
	drawOption(option, description);
	if (*inttochange < min)
		*inttochange = max;
	bool onThis = g_currentOption == g_optionCount ? true : false;
	int opCountChecks = g_currentOption > g_maxVisOptions ? g_maxVisOptions : g_optionCount;
	char const* text = toString(*inttochange);
	drawText(text, onThis ? g_selectedOptionText : g_optionText, Vector2(g_posX + (g_width - 0.112f) - getTextWidth(text, -1, 0.f), g_posY + 0.1f + 0.04f - 0.0115f + (0.035f * opCountChecks)), Vector2(0.35f, 0.35f), 0);
	if (g_currentOption == g_optionCount) {
		if (g_leftPressed) {
			if (*inttochange >= min)
				*inttochange -= step;
			else
				*inttochange = max;
		}
		if (g_rightPressed) {
			if (*inttochange < max)
				*inttochange += step;
			else
				*inttochange = min;
		}
	}
	return true;
}
bool drawFloat(char const* option, char const* description, float* floattochange, float min, float max, float step) {
	drawOption(option, description);
	if (*floattochange < min)
		*floattochange = max;
	bool onThis = g_currentOption == g_optionCount ? true : false;
	int opCountChecks = g_currentOption > g_maxVisOptions ? g_maxVisOptions : g_optionCount;
	char const* text = toStringFloat(*floattochange);
	drawText(text, onThis ? g_selectedOptionText : g_optionText, Vector2(g_posX + (g_width - 0.112f) - getTextWidth(text, -1, 0.f), g_posY + 0.1f + 0.04f - 0.0115f + (0.035f * opCountChecks)), Vector2(0.35f, 0.35f), 0);
	if (g_currentOption == g_optionCount) {
		if (g_leftPressed) {
			if (*floattochange >= min)
				*floattochange -= step;
			else
				*floattochange = max;
		}
		if (g_rightPressed) {
			if (*floattochange < max)
				*floattochange += step;
			else
				*floattochange = min;
		}
	}
	return false;
}
void drawEnd() {
	char const* texture = "shop_arrows_upanddown";
	float rotation = 0.f;
	float size = 1.f;
	if (g_currentOption == 1)
		rotation = 90.f, texture = "arrowright", size *= 1.3f;
	else if (g_currentOption == g_optionCount)
		rotation = 270.f, texture = "arrowright", size *= 1.3f;
	if (g_optionCount >= g_maxVisOptions) {
		drawRect(g_footerColor, Vector2(g_posX, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_maxVisOptions) + 0.035f), Vector2(g_width, 0.035f));
		drawSprite("commonmenu", texture, Vector2(g_posX + 0.0015f, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_maxVisOptions) + 0.035f), Vector2(size, size), rotation, RGBA(255, 255, 255, 255));
	}
	else if (g_optionCount > 0) {
		drawRect(g_footerColor, Vector2(g_posX, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_optionCount) + 0.035f), Vector2(g_width, 0.035f));
		drawSprite("commonmenu", texture, Vector2(g_posX + 0.0015f, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_optionCount) + 0.035f), Vector2(size, size), rotation, RGBA(255, 255, 255, 255));
	}
}
void drawDescription() {
	if (strcmp(g_currentDescription, "")) {
		if (g_optionCount >= g_maxVisOptions) {
			drawRect(g_descriptionColor, Vector2(g_posX, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_maxVisOptions) + 0.035f + 0.035f + 0.005f), Vector2(g_width, 0.035f));
			drawSprite("shared", "info_icon_32", Vector2(g_posX - (g_width / 2.f) + 0.01f, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_maxVisOptions) + 0.035f + 0.035f + 0.005f), Vector2(1.f, 1.f), 0.f, RGBA(255, 255, 255, 255));
			drawText(g_currentDescription, g_optionText, Vector2((g_posX + 0.003f) - (g_width / 2.1f) + getTextWidth(g_currentDescription, -1, 0.f), g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_maxVisOptions) + 0.035f + 0.035f - 0.0045f), Vector2(0.25f, 0.25f), 0);
		}
		else if (g_optionCount > 0) {
			drawRect(g_descriptionColor, Vector2(g_posX, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_optionCount) + 0.035f + 0.035f + 0.005f), Vector2(g_width, 0.035f));
			drawSprite("shared", "info_icon_32", Vector2(g_posX - (g_width / 2.f) + 0.01f, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_optionCount) + 0.035f + 0.035f + 0.005f), Vector2(1.f, 1.f), 0.f, RGBA(255, 255, 255, 255));
			drawText(g_currentDescription, g_optionText, Vector2((g_posX + 0.003f) - (g_width / 2.f) + 0.0135f, g_posY + 0.1f + (0.041f + 0.00122f) + (0.035f * g_optionCount) + 0.035f + 0.035f - 0.0045f), Vector2(0.25f, 0.25f), 0);
		}
	}
}
void playFrontendSound(char const* soundName) {
	AUDIO_PLAY_SOUND_FRONTEND(-1, soundName, "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
}
void inputHandler() {
	g_selectPressed = false;
	g_leftPressed = false;
	g_rightPressed = false;
	if (GetTickCount() - g_previousTick > m_delay) {
		if (GetAsyncKeyState(VK_INSERT) || CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 21) && CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 20)) {
			if (g_menuLevel == 0)
				forwardMenu(mainmenu, "Home");
			playFrontendSound(g_opened ? "SELECT" : "BACK");
			g_opened = !g_opened;
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 194)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("BACK");
				if (g_menuLevel == 1)
					g_opened = false;
				else if (g_menuLevel != 1)
					backMenu();
			}
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 172)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("NAV_UP_DOWN");
				if (g_currentOption > 1)
					g_currentOption--;
				else
					g_currentOption = g_optionCount;
			}
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 173)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("NAV_UP_DOWN");
				if (g_currentOption < g_optionCount)
					g_currentOption++;
				else
					g_currentOption = 1;
			}
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 174)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("NAV_LEFT_RIGHT");
				g_leftPressed = true;
			}
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 175)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("NAV_LEFT_RIGHT");
				g_rightPressed = true;
			}
			g_previousTick = GetTickCount64();
		}
		else if (CONTROLS_IS_DISABLED_CONTROL_PRESSED(2, 191)) {
			if (g_opened && g_menuLevel != 0) {
				playFrontendSound("SELECT");
				g_selectPressed = true;
			}
			g_previousTick = GetTickCount64();
		}
	}
	g_optionCount = 0;
}
