#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

#include "err.h"
#include "input_int.h"
#include "parcel.h"

//int main(){


int main(int argc, char **argv){
	int cmd = 0;
	char flag_t = 0, flag_T = 0, flag_b = 0, flag_B = 0, flag_s = 0, flag_r = 0, flag_f = 0;

	char *t_value = NULL;
	char *T_value = NULL;
	char *b_value = NULL;	
	char *B_value = NULL;
	char *s_value = NULL;
	char *f_value = NULL;
	
	opterr = 0;


	while((cmd = getopt(argc, argv, "t:T:b:B:s:f:rh")) != -1){
		switch(cmd){
			case 'h':
				printf("\n./prog_a [options]\n\n\t-t <file_name>\t\tread from txt file\n\t-T <file_name>\t\twrite to txt file\n\t-b <file name>\t\tread from binery file\n\t-B <file_name>\t\twrite to binery file\n\t-s <sort>\t\tselect the sorting type: comb/shell/qsort\n\t-r\t\t\treverse sorting\n\t-f <field>\t\tselect the sorting field: full_name/id/time\n\n");
				break;
			case 't':
				t_value = optarg;
				flag_t = 1;
				break;
			case 'T':
				T_value = optarg;
				flag_T = 1;
				break;
			case 'b':
				b_value = optarg;
				flag_b = 1;
				break;
			case 'B':
				B_value = optarg;
				flag_B = 1;
				break;
			case 's':
				s_value = optarg;
				flag_s = 1;
				break;
			case 'f':
				f_value = optarg;
				flag_f = 1;
				break;
			case 'r':
				flag_r = 1;
				break;
			case '?':
				if(strchr("tTbBsf", optopt)){
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
					printf("Use flag -h to find help\n");
				}
				else if(isprint(optopt)){
					fprintf(stderr, "unknown option '-%c'.\n", optopt);
					printf("Use flag -h to find help\n");
				}
				else{
					fprintf(stderr, "unknown option '\\x%x'.\n", optopt);
					printf("Use flag -h to find help\n");
				}
				return 1;
		}
	}
	
	int size_data = 0;
	Parcel *data = NULL;

	if((flag_t == NULL) && (flag_b == NULL)){
		printf("\nКритерии ID: XXYY-YYYY, где X - число, Y - буква.\n");
		printf("Критерии даты: Year-Month-Day Hour:Min:Sec\n");
		printf("\n-------------------\n\n");
		printf("Введите количество посылок: ");
		err input_flag = input_int(&size_data, 0, INT_MAX);
		if(input_flag == ERR_EOF){
			return 0;
		}

		data = calloc(size_data, sizeof(Parcel));
		err flag = ERR_OK;
		
		for(int i = 0; i < size_data; i++){
			flag = input_console(&(data[i]));
			if(flag == ERR_EOF){
				break;
			}
		}
	}
	
	if((flag_T == NULL) && (flag_B == NULL)){
		for(int i = 0; i < size_data; i++){
			print_parcel(data[i]);
			free(data[i].full_name);
		}
	}
	
	if(data != NULL){
		free(data);
	}
	return 0;
}

