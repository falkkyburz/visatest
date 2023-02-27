/* Example Visa program:
 * Compile gcc -I. -L. -lvisa64 -mconsole -o visafind visafind.c
 * Run: ./visafind.exe
 */

#include "visa.h"
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    ViChar buffer [VI_FIND_BUFLEN];
    ViRsrc matches = buffer;
    ViUInt32 numInstrs;
	ViFindList findList;
	ViStatus status;
	ViSession defaultRM, instr;
	status = viOpenDefaultRM(&defaultRM);
	if ( status < VI_SUCCESS ) {
		printf("Could not open a session to the VISA Resource Manager!");
		exit(0);
	}
	status = viFindRsrc( defaultRM, "?*INSTR", &findList, &numInstrs, matches );
	if ( status < VI_SUCCESS ) {
		printf("An error occurred while finding resources.");
		exit(0);
	}
	if ( numInstrs > 0 ) {
		printf("%s found!\n", matches);
	}
	viClose (defaultRM);
	while ( --numInstrs ) {
		status = viFindNext( findList, matches );
		if ( status < VI_SUCCESS ) {
			printf("An error occurred finding the next resource.");
			exit(0);
		}
	}
	viClose(findList);   
    return 0;
}