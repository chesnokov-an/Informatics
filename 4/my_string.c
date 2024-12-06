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

