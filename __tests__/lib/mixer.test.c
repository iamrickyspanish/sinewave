#include "mixer.h"
#include <stdio.h>    

int a = 5;
int b = 3;

int main() {
	printf("test mixer\n\n");
	mixer m = mixer_create(2);
	printf("newly initialized mixer should output sum 0 and have all channels on max level\n\n");
	if(
        mixer_get_lvl(m, 0) != 100 ||
        mixer_get_lvl(m, 1) != 100 ||
        mixer_out(m) != 0
    ) {
        printf("FAIL");
		return 1;
	}
    printf("CHECK \n\n");


    printf("should mix signals togeether correcty\n\n");
	mixer_in(m, 0, 100);
    mixer_in(m, 1, 100);
    mixer_set_lvl(m, 0, 50);
    int out = mixer_out(m);

    if(
        mixer_get_lvl(m, 0) != 50 ||
        mixer_get_lvl(m, 1) != 100 ||
        out != 75
    ) {
        printf("FAIL, expected 75, received %i", out);
		return 1;
	}
	printf("CHECK \n\n");
    mixer_destroy(m);
	return 0;
 } 
