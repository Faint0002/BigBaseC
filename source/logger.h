#pragma once

extern bool consoleEnabled;
enum ConsoleColors {
	consoleBlackOnBlack = 0x00,
	consoleBlackOnBlue = 0x10,
	consoleBlackOnGreen = 0x20,
	consoleBlackOnAqua = 0x30,
	consoleBlackOnRed = 0x40,
	consoleBlackOnPurple = 0x50,
	consoleBlackOnYellow = 0x60,
	consoleBlackOnWhite = 0x70,
	consoleBlackOnGray = 0x80,
	consoleBlackOnBrightBlue = 0x90,
	consoleBlackOnBrightGreen = 0xA0,
	consoleBlackOnBrightAqua = 0xB0,
	consoleBlackOnBrightRed = 0xC0,
	consoleBlackOnBrightPurple = 0xD0,
	consoleBlackOnBrightYellow = 0xE0,
	consoleBlackOnBrightWhite = 0xF0,
	consoleBlueOnBlack = 0x01,
	consoleBlueOnBlue = 0x11,
	consoleBlueOnGreen = 0x21,
	consoleBlueOnAqua = 0x31,
	consoleBlueOnRed = 0x41,
	consoleBlueOnPurple = 0x51,
	consoleBlueOnYellow = 0x61,
	consoleBlueOnWhite = 0x71,
	consoleBlueOnGray = 0x81,
	consoleBlueOnBrightBlue = 0x91,
	consoleBlueOnBrightGreen = 0xA1,
	consoleBlueOnBrightAqua = 0xB1,
	consoleBlueOnBrightRed = 0xC1,
	consoleBlueOnBrightPurple = 0xD1,
	consoleBlueOnBrightYellow = 0xE1,
	consoleBlueOnBrightWhite = 0xF1,
	consoleGreenOnBlack = 0x02,
	consoleGreenOnBlue = 0x12,
	consoleGreenOnGreen = 0x22,
	consoleGreenOnAqua = 0x32,
	consoleGreenOnRed = 0x42,
	consoleGreenOnPurple = 0x52,
	consoleGreenOnYellow = 0x62,
	consoleGreenOnWhite = 0x72,
	consoleGreenOnGray = 0x82,
	consoleGreenOnBrightBlue = 0x92,
	consoleGreenOnBrightGreen = 0xA2,
	consoleGreenOnBrightAqua = 0xB2,
	consoleGreenOnBrightRed = 0xC2,
	consoleGreenOnBrightPurple = 0xD2,
	consoleGreenOnBrightYellow = 0xE2,
	consoleGreenOnBrightWhite = 0xF2,
	consoleAquaOnBlack = 0x03,
	consoleAquaOnBlue = 0x13,
	consoleAquaOnGreen = 0x23,
	consoleAquaOnAqua = 0x33,
	consoleAquaOnRed = 0x43,
	consoleAquaOnPurple = 0x53,
	consoleAquaOnYellow = 0x63,
	consoleAquaOnWhite = 0x73,
	consoleAquaOnGray = 0x83,
	consoleAquaOnBrightBlue = 0x93,
	consoleAquaOnBrightGreen = 0xA3,
	consoleAquaOnBrightAqua = 0xB3,
	consoleAquaOnBrightRed = 0xC3,
	consoleAquaOnBrightPurple = 0xD3,
	consoleAquaOnBrightYellow = 0xE3,
	consoleAquaOnBrightWhite = 0xF3,
	consoleRedOnBlack = 0x04,
	consoleRedOnBlue = 0x14,
	consoleRedOnGreen = 0x24,
	consoleRedOnAqua = 0x34,
	consoleRedOnRed = 0x44,
	consoleRedOnPurple = 0x54,
	consoleRedOnYellow = 0x64,
	consoleRedOnWhite = 0x74,
	consoleRedOnGray = 0x84,
	consoleRedOnBrightBlue = 0x94,
	consoleRedOnBrightGreen = 0xA4,
	consoleRedOnBrightAqua = 0xB4,
	consoleRedOnBrightRed = 0xC4,
	consoleRedOnBrightPurple = 0xD4,
	consoleRedOnBrightYellow = 0xE4,
	consoleRedOnBrightWhite = 0xF4,
	consolePurpleOnBlack = 0x05,
	consolePurpleOnBlue = 0x15,
	consolePurpleOnGreen = 0x25,
	consolePurpleOnAqua = 0x35,
	consolePurpleOnRed = 0x45,
	consolePurpleOnPurple = 0x55,
	consolePurpleOnYellow = 0x65,
	consolePurpleOnWhite = 0x75,
	consolePurpleOnGray = 0x85,
	consolePurpleOnBrightBlue = 0x95,
	consolePurpleOnBrightGreen = 0xA5,
	consolePurpleOnBrightAqua = 0xB5,
	consolePurpleOnBrightRed = 0xC5,
	consolePurpleOnBrightPurple = 0xD5,
	consolePurpleOnBrightYellow = 0xE5,
	consolePurpleOnBrightWhite = 0xF5,
	consoleYellowOnBlack = 0x06,
	consoleYellowOnBlue = 0x16,
	consoleYellowOnGreen = 0x26,
	consoleYellowOnAqua = 0x36,
	consoleYellowOnRed = 0x46,
	consoleYellowOnPurple = 0x56,
	consoleYellowOnYellow = 0x66,
	consoleYellowOnWhite = 0x76,
	consoleYellowOnGray = 0x86,
	consoleYellowOnBrightBlue = 0x96,
	consoleYellowOnBrightGreen = 0xA6,
	consoleYellowOnBrightAqua = 0xB6,
	consoleYellowOnBrightRed = 0xC6,
	consoleYellowOnBrightPurple = 0xD6,
	consoleYellowOnBrightYellow = 0xE6,
	consoleYellowOnBrightWhite = 0xF6,
	consoleWhiteOnBlack = 0x07,
	consoleWhiteOnBlue = 0x17,
	consoleWhiteOnGreen = 0x27,
	consoleWhiteOnAqua = 0x37,
	consoleWhiteOnRed = 0x47,
	consoleWhiteOnPurple = 0x57,
	consoleWhiteOnYellow = 0x67,
	consoleWhiteOnWhite = 0x77,
	consoleWhiteOnGray = 0x87,
	consoleWhiteOnBrightBlue = 0x97,
	consoleWhiteOnBrightGreen = 0xA7,
	consoleWhiteOnBrightAqua = 0xB7,
	consoleWhiteOnBrightRed = 0xC7,
	consoleWhiteOnBrightPurple = 0xD7,
	consoleWhiteOnBrightYellow = 0xE7,
	consoleWhiteOnBrightWhite = 0xF7,
	consoleGrayOnBlack = 0x08,
	consoleGrayOnBlue = 0x18,
	consoleGrayOnGreen = 0x28,
	consoleGrayOnAqua = 0x38,
	consoleGrayOnRed = 0x48,
	consoleGrayOnPurple = 0x58,
	consoleGrayOnYellow = 0x68,
	consoleGrayOnWhite = 0x78,
	consoleGrayOnGray = 0x88,
	consoleGrayOnBrightBlue = 0x98,
	consoleGrayOnBrightGreen = 0xA8,
	consoleGrayOnBrightAqua = 0xB8,
	consoleGrayOnBrightRed = 0xC8,
	consoleGrayOnBrightPurple = 0xD8,
	consoleGrayOnBrightYellow = 0xE8,
	consoleGrayOnBrightWhite = 0xF8,
	consoleBrightBlueOnBlack = 0x09,
	consoleBrightBlueOnBlue = 0x19,
	consoleBrightBlueOnGreen = 0x29,
	consoleBrightBlueOnAqua = 0x39,
	consoleBrightBlueOnRed = 0x49,
	consoleBrightBlueOnPurple = 0x59,
	consoleBrightBlueOnYellow = 0x69,
	consoleBrightBlueOnWhite = 0x79,
	consoleBrightBlueOnGray = 0x89,
	consoleBrightBlueOnBrightBlue = 0x99,
	consoleBrightBlueOnBrightGreen = 0xA9,
	consoleBrightBlueOnBrightAqua = 0xB9,
	consoleBrightBlueOnBrightRed = 0xC9,
	consoleBrightBlueOnBrightPurple = 0xD9,
	consoleBrightBlueOnBrightYellow = 0xE9,
	consoleBrightBlueOnBrightWhite = 0xF9,
	consoleBrightGreenOnBlack = 0x0A,
	consoleBrightGreenOnBlue = 0x1A,
	consoleBrightGreenOnGreen = 0x2A,
	consoleBrightGreenOnAqua = 0x3A,
	consoleBrightGreenOnRed = 0x4A,
	consoleBrightGreenOnPurple = 0x5A,
	consoleBrightGreenOnYellow = 0x6A,
	consoleBrightGreenOnWhite = 0x7A,
	consoleBrightGreenOnGray = 0x8A,
	consoleBrightGreenOnBrightBlue = 0x9A,
	consoleBrightGreenOnBrightGreen = 0xAA,
	consoleBrightGreenOnBrightAqua = 0xBA,
	consoleBrightGreenOnBrightRed = 0xCA,
	consoleBrightGreenOnBrightPurple = 0xDA,
	consoleBrightGreenOnBrightYellow = 0xEA,
	consoleBrightGreenOnBrightWhite = 0xFA,
	consoleBrightAquaOnBlack = 0x0B,
	consoleBrightAquaOnBlue = 0x1B,
	consoleBrightAquaOnGreen = 0x2B,
	consoleBrightAquaOnAqua = 0x3B,
	consoleBrightAquaOnRed = 0x4B,
	consoleBrightAquaOnPurple = 0x5B,
	consoleBrightAquaOnYellow = 0x6B,
	consoleBrightAquaOnWhite = 0x7B,
	consoleBrightAquaOnGray = 0x8B,
	consoleBrightAquaOnBrightBlue = 0x9B,
	consoleBrightAquaOnBrightGreen = 0xAB,
	consoleBrightAquaOnBrightAqua = 0xBB,
	consoleBrightAquaOnBrightRed = 0xCB,
	consoleBrightAquaOnBrightPurple = 0xDB,
	consoleBrightAquaOnBrightYellow = 0xEB,
	consoleBrightAquaOnBrightWhite = 0xFB,
	consoleBrightRedOnBlack = 0x0C,
	consoleBrightRedOnBlue = 0x1C,
	consoleBrightRedOnGreen = 0x2C,
	consoleBrightRedOnAqua = 0x3C,
	consoleBrightRedOnRed = 0x4C,
	consoleBrightRedOnPurple = 0x5C,
	consoleBrightRedOnYellow = 0x6C,
	consoleBrightRedOnWhite = 0x7C,
	consoleBrightRedOnGray = 0x8C,
	consoleBrightRedOnBrightBlue = 0x9C,
	consoleBrightRedOnBrightGreen = 0xAC,
	consoleBrightRedOnBrightAqua = 0xBC,
	consoleBrightRedOnBrightRed = 0xCC,
	consoleBrightRedOnBrightPurple = 0xDC,
	consoleBrightRedOnBrightYellow = 0xEC,
	consoleBrightRedOnBrightWhite = 0xFC,
	consoleBrightPurpleOnBlack = 0x0D,
	consoleBrightPurpleOnBlue = 0x1D,
	consoleBrightPurpleOnGreen = 0x2D,
	consoleBrightPurpleOnAqua = 0x3D,
	consoleBrightPurpleOnRed = 0x4D,
	consoleBrightPurpleOnPurple = 0x5D,
	consoleBrightPurpleOnYellow = 0x6D,
	consoleBrightPurpleOnWhite = 0x7D,
	consoleBrightPurpleOnGray = 0x8D,
	consoleBrightPurpleOnBrightBlue = 0x9D,
	consoleBrightPurpleOnBrightGreen = 0xAD,
	consoleBrightPurpleOnBrightAqua = 0xBD,
	consoleBrightPurpleOnBrightRed = 0xCD,
	consoleBrightPurpleOnBrightPurple = 0xDD,
	consoleBrightPurpleOnBrightYellow = 0xED,
	consoleBrightPurpleOnBrightWhite = 0xFD,
	consoleBrightYellowOnBlack = 0x0E,
	consoleBrightYellowOnBlue = 0x1E,
	consoleBrightYellowOnGreen = 0x2E,
	consoleBrightYellowOnAqua = 0x3E,
	consoleBrightYellowOnRed = 0x4E,
	consoleBrightYellowOnPurple = 0x5E,
	consoleBrightYellowOnYellow = 0x6E,
	consoleBrightYellowOnWhite = 0x7E,
	consoleBrightYellowOnGray = 0x8E,
	consoleBrightYellowOnBrightBlue = 0x9E,
	consoleBrightYellowOnBrightGreen = 0xAE,
	consoleBrightYellowOnBrightAqua = 0xBE,
	consoleBrightYellowOnBrightRed = 0xCE,
	consoleBrightYellowOnBrightPurple = 0xDE,
	consoleBrightYellowOnBrightYellow = 0xEE,
	consoleBrightYellowOnBrightWhite = 0xFE,
	consoleBrightWhiteOnBlack = 0x0F,
	consoleBrightWhiteOnBlue = 0x1F,
	consoleBrightWhiteOnGreen = 0x2F,
	consoleBrightWhiteOnAqua = 0x3F,
	consoleBrightWhiteOnRed = 0x4F,
	consoleBrightWhiteOnPurple = 0x5F,
	consoleBrightWhiteOnYellow = 0x6F,
	consoleBrightWhiteOnWhite = 0x7F,
	consoleBrightWhiteOnGray = 0x8F,
	consoleBrightWhiteOnBrightBlue = 0x9F,
	consoleBrightWhiteOnBrightGreen = 0xAF,
	consoleBrightWhiteOnBrightAqua = 0xBF,
	consoleBrightWhiteOnBrightRed = 0xCF,
	consoleBrightWhiteOnBrightPurple = 0xDF,
	consoleBrightWhiteOnBrightYellow = 0xEF,
	consoleBrightWhiteOnBrightWhite = 0xFF,
};

void sendLog(uint16_t color, char const* info, char const* fmt, ...);
void createConsoleAndRedirectIo();
void removeConsoleAndIoRedirect();
