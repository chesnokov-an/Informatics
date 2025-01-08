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
	if(flag_s == 0 || flag_f == 0 || flag_n == 0 || flag_N == 0){
		fprintf(stderr, "You should use flags -s -f -n and -N to set conditions\n");
		return 1;
	}

	double sr_time = 0;
	for(int j = 0; j < N_value; j++){
		Parcel *data = calloc(n_value, sizeof(Parcel));
		generate_data(data, n_value);

		clock_t start = 0;
		clock_t end = 0;
		double i_time = 0;
		
		start = clock();
		sort(data, n_value, sizeof(Parcel), s_value, flag_f, f_value, flag_r);
		end = clock();
		i_time = (double)(end - start) / CLOCKS_PER_SEC;
		sr_time += i_time;

		for(int i = 0;i < n_value; i++){
			free(data[i].full_name);
		}
		free(data);
	}
	sr_time /= (double)N_value;
	printf("Усреднённое за %d итераций время сортировки массива из %d элементов составило %lf секунд.\n", N_value, n_value, sr_time);

	return 0;
}
