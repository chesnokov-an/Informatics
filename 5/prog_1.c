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
#include "file_readline.h"
#include "sort.h"

int main(int argc, char **argv){
	int cmd = 0;
	char flag_t = 0, flag_T = 0, flag_b = 0, flag_B = 0, flag_s = 0, flag_r = 0, flag_f = 0;
	int comparator_index = 4;
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
				return 0;
			case 't':
				t_value = optarg;
				flag_t += 1;
				break;
			case 'T':
				T_value = optarg;
				flag_T += 1;
				break;
			case 'b':
				b_value = optarg;
				flag_b += 1;
				break;
			case 'B':
				B_value = optarg;
				flag_B += 1;
				break;
			case 's':
				s_value = optarg;
				flag_s += 1;
				break;
			case 'f':
				f_value = optarg;
				flag_f += 1;
				break;
			case 'r':
				flag_r += 1;
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
	if(((flag_t + flag_b) > 1) || ((flag_T + flag_B) > 1)){
		fprintf(stderr, "You can't use more then 1 file\n");
		return 1;
	}
	if((flag_s > 1) || (flag_f > 1) || (flag_r > 1)){
		fprintf(stderr, "You can't use flag more then 1 time\n");
		return 1;
	}
	if(flag_s == 1){
		if((strcmp(s_value, "comb") != 0) && (strcmp(s_value, "shell") != 0) && (strcmp(s_value, "qsort") != 0)){
			fprintf(stderr, "Wrong option after flag -s\n");
			printf("Use flag -h to find help\n");
			return 1;
		}
	}
	if(flag_f == 1){
		if((strcmp(f_value, "full_name") != 0) && (strcmp(f_value, "id") != 0) && (strcmp(f_value, "time") != 0)){
			fprintf(stderr, "Wrong option after flag -f\n");
			printf("Use flag -h to find help\n");
			return 1;
		}
		if(strcmp(f_value, "full_name") == 0){
			comparator_index = 0; 
		}
		else if(strcmp(f_value, "id") == 0){
			comparator_index = 2; 
		}
		else if(strcmp(f_value, "time") == 0){
			comparator_index = 4; 
		}
	}
	comparator_index += (int)(flag_r == 1);
	
	int size_data = 0;
	Parcel *data = NULL;

	// input from console
	if((flag_t == 0) && (flag_b == 0)){
		err input_flag = console_input_data(&data, &size_data);
		if(input_flag == ERR_EOF){
			return 0;
		}
	}

	//input from txt
	if(flag_t == 1){
		FILE *file = fopen(t_value, "r");
		if(!file){
			fprintf(stderr, "Unknown file\n");
			return 0;
		}
		char *magic_word = txt_readline(file);
		if(strcmp(magic_word, "DWRF") != 0){
			free(magic_word);
			printf("Incorrect file\n");
			fclose(file);
			return 0;
		}
		free(magic_word);
		err input_flag = txt_input_data(file, &data, &size_data);
		if(input_flag != ERR_OK){
			printf("Incorrect data\n");
			fclose(file);
			return 0;
		}
		fclose(file);
	}

	//input from bin
	if(flag_b == 1){
		FILE *file = fopen(b_value, "rb");
		if(!file){
			fprintf(stderr, "Unknown file\n");
			return 0;
		}
		char *magic_word = bin_read_n_symbols(file, 4);
		if(strcmp(magic_word, "DWRF") != 0){
			free(magic_word);
			printf("Incorrect file\n");
			fclose(file);
			return 0;
		}
		free(magic_word);
		err input_flag = bin_input_data(file, &data, &size_data);
		if(input_flag != ERR_OK){
			printf("Incorrect data\n");
			fclose(file);
			return 0;
		}
		fclose(file);
	}
	
	// sort data
	if(flag_s == 1){
		sort(data, size_data, sizeof(Parcel), s_value, comparator_index);
	}

	// output to console
	if((flag_T == 0) && (flag_B == 0)){
		for(int i = 0; i < size_data; i++){
			print_parcel(data[i]);
			free(data[i].full_name);
		}
	}
	
	// output to txt
	if(flag_T == 1){
		FILE *file = fopen(T_value, "w");
		fprintf(file, "DWRF\n");
		fprintf(file, "%d\n", size_data);
		for(int i = 0; i < size_data; i++){
			txt_print_parcel(file, data[i]);
			free(data[i].full_name);
		}
		fclose(file);
	}

	// output to bin
	if(flag_B == 1){
		FILE *file = fopen(B_value, "wb");
		char magic_word[4] = "DWRF";
		fwrite(magic_word, 4, sizeof(char), file);
		fwrite(&size_data, 1, sizeof(int), file);
		for(int i = 0; i < size_data; i++){
			bin_print_parcel(file, data[i]);
			free(data[i].full_name);
		}
		fclose(file);
	}

	if(data != NULL){
		free(data);
	}
	return 0;
}
