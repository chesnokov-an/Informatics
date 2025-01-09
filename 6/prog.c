#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

#define PREFIX '#'

int main(){
	List list = {NULL};
	printf("input: ");
	err flag = list_readline(&list);
	while(flag != ERR_EOF){
		if(flag == ERR_MEM){
			fprintf(stderr, "Ошибка выделения памяти.");
			return 1;
		}
		process(&list, PREFIX);
		list_print(&list);
		list_clear(&list);
		printf("input: ");
		flag = list_readline(&list);
	}
	return 0;
}

