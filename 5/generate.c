#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parcel.h"

void generate_parcel(Parcel *parcel, int key){
	srand(time(NULL) + key);
	
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


void generate_data(Parcel *data, int size){
	for(int i = 0; i < size; i++){
		generate_parcel(&data[i], i);
	}
}
