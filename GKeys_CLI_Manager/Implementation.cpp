#include "Main.h";
#include "GKeys.h"
#include "Windows.h"
#include <cstdint>
#include <iostream>

void ProcessHID(hid_device* handle, int res) {
	unsigned char buf[65];
	unsigned char buf_temp[3]{ 0,0,0 };

	std::uint32_t key_now = 0;
	std::uint32_t key_last = 0;

	while (true) {
		buf[0] = 0x3;
		res = hid_read(handle, buf, 65);

		key_now = (buf[16] << 16) | (buf[17] << 8) | buf[18];

		if (key_now != key_last)
		{
			//printf("buf[16]: %d buf[17]: %d buf[18]: %d \n", buf[16], buf[17], buf[18]);

			//std::cout << key_now << "\n";

			for (int i = 16; i < 32; i++)
				if ((key_now & (1 << i)) && !(key_last & (1 << i))) {
					G_Pressed(key_now & (1 << i));
				}
				else if (!(key_now & (1 << i)) && (key_last & (1 << i))) {
					G_Released(key_last & (1 << i));
				}

			for (int i = 8; i < 10; i++)
				if ((key_now & (1 << i)) && !(key_last & (1 << i))) {
					G_Pressed(key_now & (1 << i));
				}
				else if (!(key_now & (1 << i)) && (key_last & (1 << i))) {
					G_Released(key_last & (1 << i));
				}

			for (int i = 0; i < 8; i++)
				if ((key_now & (1 << i)) && !(key_last & (1 << i))) {
					G_Pressed(key_now & (1 << i));
				}
				else if (!(key_now & (1 << i)) && (key_last & (1 << i))) {
					G_Released(key_last & (1 << i));
				}
		}

		key_last = key_now;

		//Sleep(250);
	}
}