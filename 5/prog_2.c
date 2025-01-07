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
#include "generate.h"

int main(int argc, char **argv){
	int cmd = 0;
	char flag_s = 0, flag_r = 0, flag_f = 0, flag_n = 0, flag_N = 0;

	char *s_value = NULL;
	char *f_value = NULL;
	int n_value = 10;
	int N_value = 10;
	
	opterr = 0;


	while((cmd = getopt(argc, argv, "s:f:rn:N:h")) != -1){

		switch(cmd){
			case 'h':
				printf("\n./prog_2 [options]\n\n\t-s <sort>\t\tselect the sorting type: comb/shell/qsort\n\t-r\t\t\treverse sorting\n\t-f <field>\t\tselect the sorting field: full_name/id/time\n\t-n <num>\t\tnumber of elements in the arrays\n\t-N <num>\t\tnumber of arrays generated\n\n");
				return 0;
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
			case 'n':
				flag_n += 1;
				n_value = atoi(optarg);
				if(!n_value){
					fprintf(stderr, "Ypu should use number after flag -n\n");
					return 1;
				}
				break;

			case 'N':
				flag_N += 1;
				N_value = atoi(optarg);
				if(!N_value){
					fprintf(stderr, "Ypu should use number after flag -N\n");
					return 1;
				}
				break;
			case '?':
				if(strchr("sfnN", optopt)){
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
	if((flag_s > 1) || (flag_f > 1) || (flag_r > 1) || (flag_n > 1) || (flag_N > 1)){
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
	}
	int size_data = 1;
	Parcel *data = NULL;
	data = calloc(1, sizeof(Parcel));
	generate_parcel(data);
	print_parcel(data[0]);
	free(data[0].full_name);
	free(data);













	/*

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
		char *magic_word = bin_readline(file);
		if(strcmp(magic_word, "DWRF") != 0){
			free(magic_word);
			printf("Incorrect file\n");
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
		sort(data, size_data, sizeof(Parcel), s_value, flag_f, f_value, flag_r);
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
		int len_magic_word = 5;
		char magic_word[5] = "DWRF";
		fwrite(&len_magic_word, 1, sizeof(int), file);
		fwrite(magic_word, 5, sizeof(char), file);
		fwrite(&size_data, 1, sizeof(int), file);
		for(int i = 0; i < size_data; i++){
			bin_print_parcel(file, data[i]);
			free(data[i].full_name);
		}
		fclose(file);
	}

	if(data != NULL){
		free(data);
	}*/
	return 0;
}
