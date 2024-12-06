#include <stdio.h>
#include <stdlib.h>

size_t my_strlen(const char* s){
	int res = 0;
	while(s[res] != '\0'){
		res += 1;
	}
	return res;
}

void *my_memcpy(void *s, const void *ct, size_t n){
	char *cs = (char *)s;
	const char *cct = (const char*)ct;
	for(size_t i = 0; i < n; i++){
		cs[i] = cct[i];
	}
	return cs;
}

char *get_str(const char *prompt){
	printf("%s", prompt);
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
			my_memcpy(res + len, buf, chunk_len);
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

char *my_strdup(const char *s){
	char *res = NULL;
	int len = my_strlen(s);
	res = calloc(len + 1, sizeof(char));
	for(int i = 0; i < len; i++){
		res[i] = s[i];
	}
	return res;
}

char *my_strchr(const char *s, int c){
	int len = my_strlen(s);
	for(int i = 0; i < len; i++){
		if(s[i] == c){
			return (char *)(s+i);
		}
	}
	return NULL;	
}

char *my_strtok(char *s, const char *delim){
	static char *ptr = NULL;	
	if(s != NULL){
		ptr = s;
	}
	if(ptr == NULL){
		return NULL;
	}
	while((*ptr != '\0') && (my_strchr(delim, *ptr))){
		*ptr = '\0';
		ptr += 1;
	}
	char *res = ptr;
	int i = 0;
	while(ptr[i] != '\0'){
		if(!my_strchr(delim, ptr[i])){
			res[i] = ptr[i];
		}
		else{
			ptr[i] = '\0';
			ptr += i + 1;
			return res;
		}
		i++;
	}
	ptr = NULL;
	if(i == 0){
		return NULL;
	}
	return res;
}

