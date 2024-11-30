#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROMPT "> "

int my_strlen(char* s);
char *get_str();
char *process(char*);

int main(){
    char *input = get_str();
    while(input != NULL){
        printf("input: \"%s\"\n", input);
        char *output = process(input);
        printf("output: \"%s\"\n", output);
        free(input);
        free(output);
        input = get_str();
    }
    return 0;
}

int my_strlen(char* s){
	int res = 0;
	while(s[res] != '\0'){
		res += 1;
	}
	return res;
}


char *get_str(){
	char buf[81] = {0};
	char *res = NULL;
	int len = 0;
	int flag = 0;
	
	do{
		flag = scanf("%80[^\n]", buf);
		if(flag < 0){
			if(!res){
				return NULL;
			}
		}
		if(flag > 0){
			int chunk_len = my_strlen(buf);
			int new_len = len + chunk_len;
			res = realloc(res, new_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = new_len;
		}
		if(flag == 0){
			scanf("%*1[\n]");
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

char *my_strdup(char *s){
	char *res = NULL;
	int len = my_strlen(s);
	res = calloc(len + 1, sizeof(char));
	for(int i = 0; i < len; i++){
		res[i] = s[i];
	}
	return res;
}

int my_strin(char *s, char symbol){
	int len = my_strlen(s);
	for(int i = 0; i < len; i++){
		if(s[i] == symbol){
			return 1;
		}
	}
	return 0;		
}

char *my_strtok(char *s, char *delim){
	static char *ptr = NULL;
	if(s != NULL){
		ptr = s;
	}
	if(ptr == NULL){
		return NULL;
	}
	char *res = calloc(my_strlen(ptr) + 1, sizeof(char));
	int i = 0;
	while(ptr[i] != '\0'){
		if(!my_strin(delim, ptr[i])){
			res[i] = ptr[i];
		}
		else{
			res = realloc(res, (i+1) * sizeof(char));
			ptr += i + 1;
			return res;
		}	
		i++;
	}
	res = realloc(res, (i+1) * sizeof(char));
	ptr = NULL;
	return res;
}

char *process(char *input){
    char *s = my_strdup(input);
    int s_len = my_strlen(s);
    char *res = calloc(s_len + 2, sizeof(char));
    int len = 0;
    char *word = my_strtok(s, "\t ");
    while(word != NULL){
        int w_len = my_strlen(word);
        if((w_len % 2) == 0){
			memcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            len++;
        }
		word = my_strtok(NULL, "\t ");
	}
    free(s);
    if(len > 0){
        len--;
    }
    res[len] = '\0';
    res = realloc(res, (len + 1) * sizeof(char));
    return res;
}

