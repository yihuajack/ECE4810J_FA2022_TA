#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_multiplier.h" // Contains hls_multiplier macros and functions

// we will use the Base Address of the RTL_MULTIPLIER
Xuint32 *baseaddr_rtl_multiplier = (Xuint32 *) XPAR_RTL_MULTIPLIER_0_S00_AXI_BASEADDR;

// global for HLS MULTIPLIER
XHls_multiplier do_hls_multiplier;
XHls_multiplier_Config *do_hls_multiplier_cfg;

// function that prompts user for 2 numbers (ints)
void get_inputs(int *c, int*d) {
	int a, b;
	// get first operand
	xil_printf("Enter operand A: ");
	scanf("%d", &a);
	xil_printf("%d\r\n", a);
	// get second operand
	xil_printf("Enter operand B: ");
	scanf("%d", &b);
	xil_printf("%d\r\n", b);
	// return the two numbers
	*c = a;
	*d = b;
	return;
}

//function that multiplies with RTL multiplier
void multiply_rtl(int a, int b) {
	// concatenate the two integers to a 32-bit value to be passed to RTL multiplier
	int passing_int = (a << 16) + b;
	// Write multiplier inputs to register 0

	*(baseaddr_rtl_multiplier + 0) = passing_int;
	xil_printf("Wrote to register 0: 0x%08x \r\n", *(baseaddr_rtl_multiplier + 0));

	// Read multiplier output from register 1
	xil_printf("Read from register 1: 0x%08x \r\n", *(baseaddr_rtl_multiplier + 1));

	xil_printf("End of test RTL_MULTIPLIER \r\n");
}

// initialize the HLS multiplier
void init_HLS_multiplier(){
	// Vitis HLS generates
	int status;
	// Create hls_multiplier pointer
	do_hls_multiplier_cfg = XHls_multiplier_LookupConfig(XPAR_HLS_MULTIPLIER_0_DEVICE_ID);

	if (!do_hls_multiplier_cfg) {
		xil_printf("Error loading configuration for do_hls_multiplier_cfg \r\n");
	}

	status = XHls_multiplier_CfgInitialize(&do_hls_multiplier, do_hls_multiplier_cfg);
	if (status != XST_SUCCESS) {
		xil_printf("Error initializing for do_hls_multiplier \r\n");
	}

	XHls_multiplier_Initialize(&do_hls_multiplier, XPAR_HLS_MULTIPLIER_0_DEVICE_ID); // this is optional in this case
}

// function that multiplies with HLS multiplier
void multiply_hls(int a, int b) {
	unsigned int p;
	p = 0;

	// Write multiplier inputs to register 0
	XHls_multiplier_Set_a(&do_hls_multiplier, a);
	XHls_multiplier_Set_b(&do_hls_multiplier, b);
	xil_printf("Write a: 0x%08x \r\n", a);
	xil_printf("Write b: 0x%08x \r\n", b);

	// Start hls_multiplier
	XHls_multiplier_Start(&do_hls_multiplier);
	xil_printf("Started hls_multiplier \r\n");

	// Wait until it's done (optional here)
	while (!XHls_multiplier_IsDone(&do_hls_multiplier));

	// Get hls_multiplier returned value
	p = XHls_multiplier_Get_return(&do_hls_multiplier);

	xil_printf("Read p: 0x%08x \r\n", p);

	xil_printf("End of test HLS_MULTIPLIER \r\n");
}

int main() {
	// setup
	init_platform();
	init_HLS_multiplier();
	int *c, *d;
	// Infinite loop steps: (1) test RTL multiplier with user inputs and (2) test HLS multiplier with user inputs
	while (1) {
		////////////////////////////////////////////////////////////////////////////////////////
		// RTL MULTIPLIER TEST
		xil_printf("Performing a test of the RTL_MULTIPLIER... \r\n");
		// prompt user for 2 numbers (to be used for RTL multiplication)
		get_inputs(c, d);
		// perform RTL multiplication
		multiply_rtl(*c, *d);

		////////////////////////////////////////////////////////////////////////////////////////
		// HLS MULTIPLIER TEST
		xil_printf("Performing a test of the HLS_MULTIPLIER... \r\n");
		// prompt user for 2 numbers (to be used for HLS multiplication)
		get_inputs(c, d);
		// perform HLS multiplication
		multiply_hls(*c, *d);
	}

	cleanup_platform();
	return 0;
}
