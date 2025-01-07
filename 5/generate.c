#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parcel.h"

void generate_parcel(Parcel *parcel){
	srand(time(NULL));
	
	int f_name = rand() % 10 + 1;
	int l_name = rand() % 10 + 1;
	int patronymic = rand() % 10 + 1;
	int n_full_name = f_name + l_name + patronymic;
	parcel->full_name = calloc(n_full_name + 3, sizeof(char));
	parcel->full_name[f_name] = 32;
	parcel->full_name[f_name + 1 + l_name] = 32;
	parcel->full_name[0] = (rand() % 26) + 65;
	parcel->full_name[f_name + 1] = (rand() % 26) + 65;
	parcel->full_name[f_name + l_name + 2] = (rand() % 26) + 65;
	for(int i = 1; i < f_name; i++){
		parcel->full_name[i] = (rand() % 26) + 97;
	}
	for(int i = f_name + 2; i < f_name + l_name + 1; i++){
		parcel->full_name[i] = (rand() % 26) + 97;
	}
	for(int i = f_name + l_name + 3; i < f_name + l_name + patronymic + 2; i++){
		parcel->full_name[i] = (rand() % 26) + 97;
	}
	
	parcel->id[0] = rand() % 10 + 48;
	parcel->id[1] = rand() % 10 + 48;
	for(int i = 2; i < 9; i++){
		if(i != 4){
			parcel->id[i] = (rand() % 26) + 97;
		}
		else{
			parcel->id[i] = '-';	
		}
	}
	
	parcel->time = rand();	
}

/*
void generate_data(Parcel *data, int size){

}













int compar_time(const void *p1, const void *p2){
	return (((Parcel*)p1)->time - ((Parcel*)p2)->time);
}

int compar_time_r(const void *p1, const void *p2){
	return (((Parcel*)p2)->time - ((Parcel*)p1)->time);
}

int compar_id(const void *p1, const void *p2){
	return strcmp(((Parcel*)p1)->id, ((Parcel*)p2)->id);
}

int compar_id_r(const void *p1, const void *p2){
	return strcmp(((Parcel*)p2)->id, ((Parcel*)p1)->id);
}

int compar_name(const void *p1, const void *p2){
	return strcmp(((Parcel*)p1)->full_name, ((Parcel*)p2)->full_name);
}

int compar_name_r(const void *p1, const void *p2){
	return strcmp(((Parcel*)p2)->full_name, ((Parcel*)p1)->full_name);
}

void comb_sort(void *data, int num, int size, int (*compar) (const void*, const void*)){
	int gap = num;
	int flag = 1;
	while((gap > 1) || (flag)){
		if((gap-1) >= 1){
			gap -= 1;
		}
		flag = 0;
		for(int i = 0; i < ((num - gap) * size); i += size){
			int j = i + gap * size;
			if(compar(data + i, data + j) > 0){
				void *tmp = calloc(size, sizeof(void));
				memcpy(tmp, data + i, size);
				memcpy(data + i, data + j, size);
				memcpy(data + j, tmp, size);
				flag = 1;
				free(tmp);
			}
		}
	}
}

void shell_sort(void *data, int num, int size, int (*compar) (const void*, const void*)){
	int inc = num / 2;
	while(inc){
		for(int i = 0; i < num * size; i += size){
			void *tmp = calloc(size, sizeof(void));
			memcpy(tmp, data + i, size);
			while((i >= inc * size) && (compar(data + i - inc * size, tmp) > 0)){
				memcpy(data + i, data + i - inc * size, size);
				i -= inc * size;
			}
			memcpy(data + i, tmp, size);
			free(tmp);
		}
		inc = (inc == 2) ? 1 : (inc * 5 / 11);
	}
}

void sort(void *data, int num, int size, char* s_value, int flag_f, char* f_value, int flag_r){
	int (*compar) (const void*, const void*);
	if((flag_f == 0) || (strcmp(f_value, "time") == 0)){
		if(flag_r == 0){
			compar = compar_time;
		}
		else{
			compar = compar_time_r;
		}
	}

	else if(strcmp(f_value, "id") == 0){
		if(flag_r == 0){
			compar = compar_id;
		}
		else{
			compar = compar_id_r;
		}
	}
	
	else if(strcmp(f_value, "full_name") == 0){
		if(flag_r == 0){
			compar = compar_name;
		}
		else{
			compar = compar_name_r;
		}
	}

	if(strcmp(s_value, "comb") == 0){
		comb_sort(data, num, size, compar);
	}
	else if(strcmp(s_value, "shell") == 0){
		shell_sort(data, num, size, compar);
	}
	else if(strcmp(s_value, "qsort") == 0){
		qsort(data, num, size, compar);
	}
}*/
