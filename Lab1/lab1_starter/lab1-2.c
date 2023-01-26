#include "xparameters.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_types.h"

// Get device IDs from xparameters.h
#define BTN_ID XPAR_AXI_GPIO_BUTTONS_DEVICE_ID
#define LED_ID XPAR_AXI_GPIO_LED_DEVICE_ID
#define BTN_CHANNEL 1
#define LED_CHANNEL 1
#define BTN_MASK 0b1111
#define LED_MASK 0b1111

int LEDOutput() {
	XGpio_Config *cfg_ptr;
	XGpio led_device, btn_device;
	u32 data;

	xil_printf("Entered function main\r\n");

	// Initialize LED Device
	
	

	// Initialize Button Device
	
	

	// Set Button Tristate
	

	// Set Led Tristate
	

	while (1) {

	}

	return XST_SUCCESS; /* Should be unreachable */
}

int main() {
	int Status;

	/* Execute the LED output. */
	Status = LEDOutput();
	if (Status != XST_SUCCESS) {
		xil_printf("GPIO output to the LEDs failed!\r\n");
	}

	return 0;
}
