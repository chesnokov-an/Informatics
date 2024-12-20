#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
//#include <regex.h>
#include "err.h"
#include "input_int.h"
#include "parcel.h"

err correct_id(char *id){
	/*if(id == NULL){
		return ERR_EOF;
	}

	regex_t expression;
	int flag = regcomp(&expression, "[0-9]{2}[A-Za-z]{2}-[A-Za-z]{4}", 0);
	flag = regexec(&expression, id, 0, NULL, 0);
	if(flag == 0){
		return ERR_OK;
	}
	return ERR_VAL;*/

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

err correct_time(char *str_time){
	if(str_time == NULL){
		return ERR_EOF;
	}
	struct tm time;
	if(strptime(str_time, "%Y-%m-%d %H:%M:%S", &time) == NULL){
		return ERR_VAL;
	}
	return ERR_OK;
}

err input_console(Parcel *parcel){
	char *full_name = readline("\nВведите ФИО: ");
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
	
	char *str_time = readline("Введите время отправления: ");
	err flag_time = correct_time(str_time);
	while(flag_time != ERR_OK){
		if(flag_time == ERR_EOF){
			free(full_name);
			free(id);
			return ERR_EOF;
		}
		free(str_time);
		str_time = readline("Повторите ввод: ");
		flag_time = correct_time(str_time);
	}
	struct tm time;
	strptime(str_time, "%Y-%m-%d %H:%M:%S", &time);
	time.tm_isdst = -1;		// надо для valgrind, т.к. не эта переменная не инициалищируется по умолчанию
	int unix_time = (int)(mktime(&time));

	parcel->full_name = malloc((strlen(full_name) + 1) * sizeof(char));
	if(parcel->full_name == NULL){
		return ERR_MEM;
	}
	strcpy(parcel->full_name, full_name);
	strcpy(parcel->id, id);
	parcel->time = unix_time;
	free(full_name);
	free(id);
	free(str_time);
	return ERR_OK;
}

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

