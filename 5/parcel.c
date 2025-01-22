#define _XOPEN_SOURCE
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <regex.h>
#include "err.h"
#include "input_int.h"
#include "parcel.h"
#include "file_readline.h"
#include "input_long.h"

err correct_id(char *id){
	if(id == NULL){
		return ERR_EOF;
	}

	regex_t expression;
	int flag = regcomp(&expression, "^[0-9][0-9][A-Za-z][A-Za-z]-[A-Za-z][A-Za-z][A-Za-z][A-Za-z]$", 0);
	flag = regexec(&expression, id, 0, NULL, 0);
	regfree(&expression);
	if(flag != 0){
		return ERR_VAL;
	}
	return ERR_OK;
}

err correct_full_name(char *name){
	if(name == NULL){
		return ERR_EOF;
	}

	regex_t expression;
	int flag = regcomp(&expression, "^[A-Z][a-z]*(-[A-Z][a-z]*)*\\s+[A-Z][a-z]*(-[A-Z][a-z]*)*\\s+[A-Z][a-z]*(-[A-Z][a-z]*)*$", REG_EXTENDED);
	flag = regexec(&expression, name, 0, NULL, 0);
	regfree(&expression);
	if(flag != 0){
		return ERR_VAL;
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

err console_input_parcel(Parcel *parcel){
	char *full_name = readline("\nВведите ФИО: ");
	err flag_name = correct_full_name(full_name);
	while(flag_name != ERR_OK){
		if(flag_name == ERR_EOF){
			return ERR_EOF;
		}
		free(full_name);
		full_name = readline("Повторите ввод: ");
		flag_name = correct_full_name(full_name);
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
	long unix_time = (long)(mktime(&time));

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

err txt_input_parcel(FILE* file_name, Parcel *parcel){
	char *full_name = txt_readline(file_name);
	err flag_name = correct_full_name(full_name);
	if(flag_name != ERR_OK){
		if(flag_name == ERR_VAL){
			free(full_name);
		}
		return flag_name;
	}


	char *id = txt_readline(file_name);
	err flag_id = correct_id(id);
	if(flag_id != ERR_OK){
		free(full_name);
		if(flag_id == ERR_VAL){
			free(id);
		}
		return flag_id;
	}
	
	char *str_time = txt_readline(file_name);
	err flag_time = correct_time(str_time);
	if(flag_time != ERR_OK){
		free(full_name);
		free(id);
		if(flag_time == ERR_VAL){	
			free(str_time);
		}
		return flag_time;
	}

	struct tm time;
	strptime(str_time, "%Y-%m-%d %H:%M:%S", &time);
	time.tm_isdst = -1;		// надо для valgrind, т.к. не эта переменная не инициалищируется по умолчанию
	long unix_time = (long)(mktime(&time));

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

err bin_input_parcel(FILE* file_name, Parcel *parcel){
	char *full_name = bin_readline(file_name);
	err flag_name = correct_full_name(full_name);
	if(flag_name != ERR_OK){
		if(flag_name == ERR_VAL){
			free(full_name);
		}
		return flag_name;
	}


	char *id = bin_read_n_symbols(file_name, 9);
	err flag_id = correct_id(id);
	if(flag_id != ERR_OK){
		free(full_name);
		if(flag_id == ERR_VAL){
			free(id);
		}
		return flag_id;
	}
	
	long time = 0;
	err flag_time = bin_input_long(file_name, &time, LONG_MIN, LONG_MAX);
	if(flag_time != ERR_OK){
		free(full_name);
		free(id);
		return flag_time;
	}

	parcel->full_name = malloc((strlen(full_name) + 1) * sizeof(char));
	if(parcel->full_name == NULL){
		return ERR_MEM;
	}
	strcpy(parcel->full_name, full_name);
	strcpy(parcel->id, id);
	parcel->time = time;
	free(full_name);
	free(id);
	return ERR_OK;
}

err console_input_data(Parcel **data, int *size_data){
	printf("\nКритерии ID: XXYY-YYYY, где X - число, Y - буква.\n");
	printf("Критерии даты: Year-Month-Day Hour:Min:Sec\n");
	printf("\n-------------------\n\n");
	printf("Введите количество посылок: ");
	err input_flag = input_int(size_data, 0, INT_MAX);
	if(input_flag == ERR_EOF){
		return ERR_EOF;
	}

	*data = calloc(*size_data, sizeof(Parcel));
	err flag = ERR_OK;
	
	for(int i = 0; i < *size_data; i++){
		flag = console_input_parcel(&((*data)[i]));
		if(flag == ERR_EOF){
			break;
		}
	}
	return ERR_OK;
}

err txt_input_data(FILE* file_name, Parcel **data, int *size_data){
	err input_flag = txt_input_int(file_name, size_data, 0, INT_MAX);
	if(input_flag != ERR_OK){
		return input_flag;
	}

	*data = calloc(*size_data, sizeof(Parcel));
	err flag = ERR_OK;
	
	for(int i = 0; i < *size_data; i++){
		flag = txt_input_parcel(file_name, &((*data)[i]));
		if(flag != ERR_OK){
			break;
		}
	}
	return ERR_OK;
}

err bin_input_data(FILE* file_name, Parcel **data, int *size_data){
	err input_flag = bin_input_int(file_name, size_data, 0, INT_MAX);
	if(input_flag != ERR_OK){
		return input_flag;
	}
	
	*data = calloc(*size_data, sizeof(Parcel));
	err flag = ERR_OK;
	
	for(int i = 0; i < *size_data; i++){
		flag = bin_input_parcel(file_name, &((*data)[i]));
		if(flag != ERR_OK){
			break;
		}
	}
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

void txt_print_parcel(FILE *file_name, Parcel parcel){
	if(parcel.full_name == NULL){
		return;
	}
	fprintf(file_name, "%s\n", parcel.full_name);
	fprintf(file_name, "%s\n", parcel.id);
	time_t unix_time = (int)parcel.time;
	struct tm *time = localtime(&unix_time);
	time->tm_isdst = -1;		// надо для valgrind, т.к. не эта переменная не инициалищируется по умолчанию
	char str_time[20];
	strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", time);

	fprintf(file_name, "%s\n", str_time);
}

void bin_print_parcel(FILE *file_name, Parcel parcel){
	if(parcel.full_name == NULL){
		return;
	}
	int name_len = strlen(parcel.full_name);
	int id_len = 9;
	fwrite(&name_len, 1, sizeof(int), file_name);
	fwrite(parcel.full_name, name_len, sizeof(char), file_name);
	fwrite(parcel.id, id_len, sizeof(char), file_name);
	fwrite(&parcel.time, 1, sizeof(long), file_name);
}

