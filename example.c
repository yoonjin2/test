#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "custom.h"


		


int main(void) {

	bytes string = (bytes)malloc(sizeof(char)*LIMIT);
	bind_addr();
	int i=1;
	for(;i<LIMIT*2;i++) {
		sprintf(string, "Thanks! Currently I received this %d times." , i);
		rw_data(string);
		usleep(500);
	}

	return 0;
}
