
#include <stdio.h> 
#include <thread>
#include <wchar.h> 
#include <hidapi.h>
#include <ranges>
#include <chrono>
#include <iostream>
#include <string>

#define MAX_STR 255

// TODO this does not work yet.
// Maybe play around with written bytes (length)
void setLED(hid_device *handle, int i, bool on) {
	int res;
	unsigned char buf[80] = { 0 };
	buf[i] = on ? 127 : 0;
	res = hid_write(handle, buf, 80);
}


int main(int argc, char* argv[])
{
	int res;
	
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;

	// Initialize the hidapi library
	res = hid_init();

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(0x17cc, 0x1120, NULL);
	if (!handle) {
		printf("Unable to open device\n");
		hid_exit();
 		return 1;
	}

	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	printf("Product String: %ls\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	printf("Indexed String 1: %ls\n", wstr);

	for (int i = 0; i < 80; i++) {
		setLED(handle, i, true);
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
		setLED(handle, i, false);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
	}

	while (true) {
		unsigned char buf[22];
		// Read requested state
		res = hid_read(handle, buf, 22);

		// Print out the returned buffer.
		// TODO Here you should check for patterns(buttons)
		for (i = 0; i < 22; i++) {
			printf("buf[%d]: %d\n", i, buf[i]);
		}
	}

	// Close the device
	hid_close(handle);

	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}
