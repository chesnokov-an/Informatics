#include <stdio.h>
#include "err.h"

err bin_input_long(FILE* file_name, long *data, long start, long end){
	fread(data, sizeof(long), 1, file_name);
	if(feof(file_name)){
		return ERR_EOF;
	}
	if((ferror(file_name)) || (*data < start) || (*data > end)){
		return ERR_VAL;
	}
	return ERR_OK;
}
