#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

#define PREFIX "-----"

int main(){
	printf("input: ");
	List list = list_readline();
	//List list = list_from_str(PREFIX);
	while(list.head){
		process(&list, PREFIX);
		list_print(&list);
		list_clear(&list);
		printf("input: ");
		list = list_readline();
		//list = list_from_str(PREFIX);
	}
	return 0;
}

