#include "voice.h"
#include <stdio.h>    

 int main() {
	printf("test voice\n\n");
	voice v = voice_create();
	printf("newly initialized voice: output should be 0\n\n");
	if(voice_out(v) != 0) {
        printf("FAIL, expected 0, received: %i \n\n", voice_out(v));
		return 1;
	}
	printf("CHECK \n\n");
	
	return 0;
 } 
