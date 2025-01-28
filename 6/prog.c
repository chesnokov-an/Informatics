#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

#define PREFIX "(o_O)"
int main(){
	List *list = list_readline("input: ");
	while(list){
		process(list, PREFIX);
		list_print(list, "output: ");
		list_clear(list);
		list = list_readline("input: ");
	}
	return 0;
}

