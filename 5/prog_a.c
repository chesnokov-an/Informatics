#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include "err.h"
#include "input_int.h"

//#define _XOPEN_SOURCE

typedef struct Parcel {
	char *full_name;
	char id[10];
	int time;

} Parcel;

void print_parcel(Parcel parcel){
	if(parcel.full_name == NULL){
		return;
	}
	printf("\nФИО: %s\n", parcel.full_name);
	printf("ID: %s\n", parcel.id);
	time_t unix_time = (int)parcel.time;
	struct tm *time = localtime(&unix_time);
	time->tm_isdst = -1;		// надо для valgrind, т.к. не эта переменная не инициалищируется по умолчанию
	char str_time[20];
	strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", time);

	printf("Время отправления: %s\n\n", str_time);
}

err correct_id(char *id){
	if(id == NULL){
		return ERR_EOF;
	}
	if(strlen(id) != 9){
		return ERR_VAL;
	}
	if(!isdigit(id[0]) || !(isdigit(id[1]))){
		return ERR_VAL;
	}
	for(int i = 2; i < 9; i++){
		if((i == 4) && (id[i] != '-')){
			return ERR_VAL;
		}
		if((i != 4) && !isalpha(id[i])){
			return ERR_VAL;
		}
	}
	return ERR_OK;
}

err input_console(Parcel *parcel){
	char *full_name = readline("Введите ФИО: ");
	if(full_name == NULL){
		return ERR_EOF;
	}

	char *id = readline("Введите ID посылки: ");
	err flag_id = correct_id(id);
	while(flag_id != ERR_OK){
		if(flag_id == ERR_EOF){
			free(full_name);
			return ERR_EOF;
		}
		free(id);
		id = readline("Повторите ввод: ");
		flag_id = correct_id(id);
	}
	
	struct tm time;
	char *str_time = readline("Введите время отправления: ");
	if(str_time == NULL){
		free(full_name);
		free(id);
		return ERR_EOF;
	}
	while(strptime(str_time, "%Y-%m-%d %H:%M:%S", &time) == NULL){
		free(str_time);
		str_time = readline("Повторите ввод: ");
		if(str_time == NULL){
			free(full_name);
			free(id);
			return ERR_EOF;
		}
	}
	free(str_time);
	time.tm_isdst = -1;		// надо для valgrind, т.к. не эта переменная не инициалищируется по умолчанию
	
	int unix_time = (int)(mktime(&time));

	parcel->full_name = malloc((strlen(full_name) + 1) * sizeof(char));
	strcpy(parcel->full_name, full_name);
	strcpy(parcel->id, id);
	parcel->time = unix_time;
	free(full_name);
	free(id);
	return ERR_OK;
}

int main(){
	int size_data = 0;
	err input_flag = input_int(&size_data, 0, INT_MAX);
	if(input_flag == ERR_EOF){
		return 0;
	}

	Parcel *data = calloc(size_data, sizeof(Parcel));
	err flag = ERR_OK;
	
	for(int i = 0; i < size_data; i++){
		flag = input_console(&(data[i]));
		if(flag == ERR_EOF){
			break;
		}
	}

	for(int i = 0; i < size_data; i++){
		print_parcel(data[i]);
		free(data[i].full_name);
	}
	free(data);

	return 0;
}

