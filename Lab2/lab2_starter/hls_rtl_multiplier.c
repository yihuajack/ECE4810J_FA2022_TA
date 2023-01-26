#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_multiplier.h" // Contains hls_multiplier macros and functions

// we will use the Base Address of the RTL_MULTIPLIER
Xuint32 *baseaddr_rtl_multiplier = (Xuint32 *) XPAR_RTL_MULTIPLIER_0_S00_AXI_BASEADDR;

int main() {
	init_platform();

	////////////////////////////////////////////////////////////////////////////////////////
	// RTL MULTIPLIER TEST
	xil_printf("Performing a test of the RTL_MULTIPLIER... \r\n");

	// Write multiplier inputs to register 0
	*(baseaddr_rtl_multiplier + 0) = 0x00020003;
	xil_printf("Wrote to register 0: 0x%08x \r\n", *(baseaddr_rtl_multiplier + 0));

	// Read multiplier output from register 1
	xil_printf("Read from register 1: 0x%08x \r\n", *(baseaddr_rtl_multiplier + 1));

	xil_printf("End of test RTL_MULTIPLIER \r\n");

	////////////////////////////////////////////////////////////////////////////////////////
	// HLS MULTIPLIER TEST
	xil_printf("Performing a test of the HLS_MULTIPLIER... \r\n");

	// Vitis HLS generates
	int status;
	// Create hls_multiplier pointer
	XHls_multiplier do_hls_multiplier;
	XHls_multiplier_Config *do_hls_multiplier_cfg;
	do_hls_multiplier_cfg = XHls_multiplier_LookupConfig(XPAR_HLS_MULTIPLIER_0_DEVICE_ID);

	if (!do_hls_multiplier_cfg) {
		xil_printf("Error loading configuration for do_hls_multiplier_cfg \r\n");
	}

	status = XHls_multiplier_CfgInitialize(&do_hls_multiplier, do_hls_multiplier_cfg);
	if (status != XST_SUCCESS) {
		xil_printf("Error initializing for do_hls_multiplier \r\n");
	}

	XHls_multiplier_Initialize(&do_hls_multiplier, XPAR_HLS_MULTIPLIER_0_DEVICE_ID); // this is optional in this case

	unsigned short int a, b;
	unsigned int p;

	a = 2;
	b = 3;
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

	cleanup_platform();
	return 0;
}
