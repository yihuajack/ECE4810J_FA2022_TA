#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for peripheral RTL_MULTIPLIER

// we will use the Base Address of the RTL_MULTIPLIER
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_RTL_MULTIPLIER_0_S00_AXI_BASEADDR;

int main() {
    init_platform();
    xil_printf("Performing a test of the RTL_MULTIPLIER...\r\n");

    // Write multiplier inputs to register 0
    *(baseaddr_p + 0) = 0x00020003;
    xil_printf("Wrote to register 0: 0x%08x\r\n", *(baseaddr_p + 0));

    // Read multiplier output from register 1
    xil_printf("Read from register 1: 0x%08x\r\n", *(baseaddr_p + 1));

    xil_printf("End of test\r\n");

    cleanup_platform();
    return 0;
}
