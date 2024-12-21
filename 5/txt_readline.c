#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *txt_readline(FILE* file_name){
	char buf[81] = {0};
	char *res = NULL;
	int len = 0;
	int flag = 0;
	
	do{
		flag = fscanf(file_name, "%80[^\n]", buf);
		if(flag < 0){
			if(!res){
				return NULL;
			}
		}
		if(flag > 0){
			int chunk_len = strlen(buf);
			int new_len = len + chunk_len;
			res = realloc(res, new_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = new_len;
		}
		if(flag == 0){
			fscanf(file_name, "%*1[\n]");
		}
	}while(flag > 0);
	if(len > 0){
		res[len] = '\0';
	}
	else{
		res = calloc(1, sizeof(char));
	}
	return res;
}
