#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0, j = 0;
	uint8_t path[8]; 

	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}

		printf("%04x:%04x (bus %d, device %d)",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));

		r = libusb_get_port_numbers(dev, path, sizeof(path));
		if (r > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < r; j++)
				printf(".%d", path[j]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
    printf("Hello World!\n");
    
    libusb_device **devs;
	int r;
	ssize_t cnt;

	r = libusb_init_context(/*ctx=*/NULL, /*options=*/NULL, /*num_options=*/0);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
    printf("Device Count %ld\n", cnt);
	if (cnt < 0){
		libusb_exit(NULL);
		return (int) cnt;
	}

	print_devs(devs);
	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);
	return 0;
}

