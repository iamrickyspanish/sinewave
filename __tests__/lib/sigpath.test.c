#include "sigpath.h"
#include <stdio.h>    

 int main() {
	printf("test sigpath\n\n");
	sigpath sp = sigpath_create();
	printf("newly initialized sigpath: output should be 0\n\n");
	if(sigpath_out(sp) != 0) {
        printf("FAIL, expected 0, received: %i \n\n", sigpath_out(sp));
		return 1;
	}
	printf("CHECK \n\n");
	
	return 0;
 } 
