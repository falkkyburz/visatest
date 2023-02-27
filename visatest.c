/* Example Visa program:
 * Compile gcc -I. -L. -lvisa64 -mconsole -o visatest visatest.c
 * Run: ./visatest.exe
 */

#include "visa.h"
#include <stdio.h>

int main (void) {
    ViSession defaultRM, vi;
    ViStatus res;
    char buf [256] = {0};
    /* Open session to GPIB device at address 22 */
    res = viOpenDefaultRM(&defaultRM);
    res = viOpen(defaultRM, "USB0::0xF4EC::0xEE38::SDM35FAC3R0218::INSTR",VI_NULL,VI_NULL, &vi);
    /* Initialize device */
    res = viPrintf(vi, "*RST\n");
    /* Send an *IDN? string to the device */
    res = viPrintf(vi, "*IDN?\n");
    /* Read results */
    res = viScanf(vi, "%t", buf);
    /* Print results */
    printf("Instrument identification string: %s\n", buf);
    /* Initialize measurement */
    res = viPrintf(vi, "INIT\n");
    /* Query latest value */
    res = viQueryf(vi, "READ?\n", "%t", buf);
    /* Print value */
    printf("Ret= %i, Value: %s\n", res, buf);
    /* Initialize device */
    res = viPrintf(vi, "*RST\n");
    /* Close session */
    viClose(vi);
    viClose(defaultRM);
    return 0;
}