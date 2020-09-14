#include "GKeys.h"
#include "Main.h";
#include <iostream>
#include <Windows.h>

std::unordered_map<std::uint32_t, int> GKeys_Map
{
	{GKEY_G1, 0xC1},
	{GKEY_G2, 0xC2},
	{GKEY_G3, 0xC3},
	{GKEY_G4, 0xC4},
	{GKEY_G5, 0xC5},
	{GKEY_G6, 0xC6},
	{GKEY_G7, 0xC7},
	{GKEY_G8, 0xC8},
	{GKEY_G9, 0xC9},
	{GKEY_G10, 0xCA},
	{GKEY_G11, 0xCB},
	{GKEY_G12, 0xCC},
	{GKEY_G13, 0xCD},
	{GKEY_G14, 0xCE},
	{GKEY_G15, 0xCF},
	{GKEY_G16, 0xD0},
	{GKEY_G17, 0xD1},
	{GKEY_G18, 0xD2}
};

std::unordered_map<std::uint32_t, int> GKeys_Function_Map
{
	{GKEY_G1, 0x76},
	{GKEY_G2, 0x77},
	{GKEY_G3, 0x78},
	{GKEY_G4, 0x79},
	{GKEY_G5, 0x7A},
	{GKEY_G6, 0x7B},
	{GKEY_G7, 0x7C},
	{GKEY_G8, 0x7D},
	{GKEY_G9, 0x7E},
	{GKEY_G10, 0x7F},
	{GKEY_G11, 0x80},
	{GKEY_G12, 0x81},
	{GKEY_G13, 0x82},
	{GKEY_G14, 0x83},
	{GKEY_G15, 0x84},
	{GKEY_G16, 0x85},
	{GKEY_G17, 0x86},
	{GKEY_G18, 0x87}
};

std::unordered_map<std::uint32_t, std::string> GKeys_Names_Map
{
	{GKEY_G1, "G1"},
	{GKEY_G2, "G2"},
	{GKEY_G3, "G3"},
	{GKEY_G4, "G4"},
	{GKEY_G5, "G5"},
	{GKEY_G6, "G6"},
	{GKEY_G7, "G7"},
	{GKEY_G8, "G8"},
	{GKEY_G9, "G9"},
	{GKEY_G10, "G10"},
	{GKEY_G11, "G11"},
	{GKEY_G12, "G12"},
	{GKEY_G13, "G13"},
	{GKEY_G14, "G14"},
	{GKEY_G15, "G15"},
	{GKEY_G16, "G16"},
	{GKEY_G17, "G17"},
	{GKEY_G18, "G18"}
};

bool IsFunctionMode = false;

void G_Pressed(std::uint32_t key) {
	if (IsConsoleVisible())
		std::cout << GKeys_Names_Map[key] << " Pressed\n";

	// If Shift + Control + G18 is pressed, then toggle console
	if (key == GKEY_G1 && GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000) {
		if (IsConsoleVisible())
		{
			HideConsole();
		}
		else
		{
			ShowConsole();
		}
	}
	else if (key == GKEY_G2 && GetKeyState(VK_SHIFT) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000) {
		IsFunctionMode = !IsFunctionMode;

		if (IsConsoleVisible())
			std::cout << "Toggled Function Mode, now:" << IsFunctionMode << "\n";
	}
	else {
		if (IsFunctionMode) {
			keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(GKeys_Function_Map[key], 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(GKeys_Function_Map[key], 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
		else {
			keybd_event(0xFF, GKeys_Map[key], 0, 0);
		}
	}
}
void G_Released(std::uint32_t key) {
	if (IsConsoleVisible())
		std::cout << GKeys_Names_Map[key] << " Released\n";
}