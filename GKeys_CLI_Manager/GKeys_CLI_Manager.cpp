// GKeys_CLI_Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "Main.h";
#include "hidapi.h"

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

int main()
{
	HideConsole();
	int res;
	hid_device* handle;

	bool isDebug = false;

	res = hid_init();

	std::string path;
	struct hid_device_info* devs, * cur_dev;

	if (hid_init())
		return -1;

	// Corsair - K95
	devs = hid_enumerate(0x1B1C, 0x1B11);
	cur_dev = devs;
	while (cur_dev) {
		if (isDebug) {
			printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
			printf("\n");
			printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
			printf("  Product:      %ls\n", cur_dev->product_string);
			printf("  Release:      %hx\n", cur_dev->release_number);
			printf("  Interface:    %d\n", cur_dev->interface_number);
			printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
			printf("\n");
		}

		if (cur_dev->usage == 0x2 && cur_dev->usage_page == 0xFFC0)
			path = cur_dev->path;

		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	// Open the device using the VID, PID
	//handle = hid_open(0x1B1C, 0x1B11, NULL);

	handle = hid_open_path(path.c_str());
	if (!handle) {
		printf("Unable to open device\n");
		return 1;
	}

	// Read the Manufacturer String
	wchar_t wstr[255];
	wstr[0] = 0x0000;

	res = hid_get_manufacturer_string(handle, wstr, 255);
	if (res < 0)
		printf("Unable to read manufacturer string\n");
	else
		printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	wstr[0] = 0x0000;
	res = hid_get_product_string(handle, wstr, 255);
	if (res < 0)
		printf("Unable to read product string\n");
	else
		printf("Product String: %ls\n", wstr);

	// Set the hid_read() function to be non-blocking.
	//hid_set_nonblocking(handle, 1);

	ProcessHID(handle, res);

	// Close the device
	hid_close(handle);

	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}