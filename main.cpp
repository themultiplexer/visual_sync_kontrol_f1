#include <stdio.h> 
#include <wchar.h> 
#include <hidapi.h>

#define MAX_STR 255


void setLED(hid_device *handle, bool on) {
	int res;
	unsigned char buf[65];
	// Toggle LED (cmd 0x80). The first byte is the report number (0x0).
	buf[0] = 0x0;
	buf[1] = 0x80;
	res = hid_write(handle, buf, 65);
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

	setLED(handle, true);

	while (true) {
		unsigned char buf[22];
		// Read requested state
		res = hid_read(handle, buf, 22);

		// Print out the returned buffer.
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
