#pragma once

#include "hidapi.h"

void ProcessHID(hid_device* handle, int res);

void HideConsole();

void ShowConsole();

bool IsConsoleVisible();