#include "list.h"
#include <stdio.h>    

int a = 5;
int b = 3;

bool filter_fn(const void* a, const unsigned short i,const void* _) {
    if ((*(int*)(a)) == b) {
        return false;
    }
    return true;
};

 int main() {
    	//cbuffer_t buff = cbuffer_create()
	printf("test list\n\n");
	list l = list_create(8, sizeof(int));
	printf("newly initialized list should have size 0\n\n");
	if(list_get_length(l) != 0) {
		return 1;
	}

	list_push(l, &a);
	printf("list should have size 1 after push\n\n");
	if (list_get_length(l) != 1) {
        printf("FAIL");
		return 1;
	}	

	printf("list should have 1 item after filter");
	list_push(l, &b);
	list_filter(l, &filter_fn, NULL);
	if(list_get_length(l) != 1) {
        printf("FAIL");
		return 1;
	}
	return 0;
 } 
