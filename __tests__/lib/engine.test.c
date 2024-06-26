#include "engine.h"
#include <stdio.h>    

 int main() {
	printf("test engine\n\n");
	engine e = engine_create(1, 256);
	printf("newly initialized engine: output should be 0\n\n");
	if(engine_out(e) != 0) {
        printf("FAIL, expected 0, received: %i \n\n", engine_out(e));
		return 1;
	}
	printf("CHECK \n\n");
	
	return 0;
 } 
