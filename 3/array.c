#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "input.h"
#include "array.h"
#include "dialogue_array.h"

int sum_data(const int* data, int start, int end){
    int s = 0;
    for(int k = start; k <= end; k++){
        s += data[k];
    }
    return s;
}

err change_memory(int **data, int *capacity, int len, int extra_capacity){
	if (data == NULL || capacity == NULL){
		return ERR_NULL;
	}
    if((*capacity + extra_capacity) < len){
        return ERR_POS;
    }
    *capacity += extra_capacity;
    if(*capacity == 0){
        free(*data);
		*data = NULL;
        return ERR_OK;
    }
	*data = realloc(*data, *capacity * sizeof(int));
    return ERR_OK;
}

err initialization(int **data, int *len, int *capacity){
	if (data == NULL || len == NULL || capacity == NULL){
		return ERR_NULL;
	}
    printf("\n\tИнициализация массива:\n\tПод массив выделено %d ячеек памяти.\n\tВведите длину массива: ", *capacity);
    int input_flag = input_int(len, 0, *capacity);
    if(input_flag == 1){
        return ERR_EOF;
    }
    printf("\tВведите элементы массива через Enter:\n");
    input_flag = 0;
    for(int i = 0; i < *len; i++){
        input_flag = input_int(*data+i, INT_MIN, INT_MAX);
        if(input_flag == 1){
            return ERR_EOF;
        }
    }
    return ERR_OK;
}

err add_element(int *data, int elem, int pos, int* len){
	if (len == NULL){
		return ERR_NULL;
	}
    if(pos < 0){
        return ERR_POS;
    }
    if(pos > *len){
        pos = *len;
    }
    *len += 1;
    for(int i = *len - 2; i >= pos; i--){
        data[i+1] = data[i];
    }
    data[pos] = elem;
    return ERR_OK;
}

err delete_element(int *data, int pos, int* len){
	if (len == NULL){
		return ERR_NULL;
	}

    if((pos < 0) || (pos >= *len) || (*len == 0)){
        return ERR_POS;   
    }
    *len -= 1;
    for(int i = pos; i < *len; i++){
        data[i] = data[i+1];
    }
    return ERR_OK;
}

err individual(int* data, int** new_data, int* len, int* new_len, int* new_capacity){
	if (len == NULL || new_data == NULL || new_len == NULL){
		return ERR_NULL;
	}
    if(*len == 0){
        return ERR_POS;
    }
    int s = 0;
    int res_i = 0;
    int res_j = 0;
    int max_s = INT_MIN;
    for(int i = 0; i < *len; i++){
        for(int j = i; j < *len; j++){
            s = sum_data(data, i, j);
            if(max_s < s){
                max_s = s;
                res_i = i;
                res_j = j;
            }
        }
    }
    finish_work(new_data, new_len);
    *new_len = res_j - res_i + 1;
	change_memory(new_data, new_capacity, 0, *new_len);
    if(!new_data){
        return ERR_MEM;
    }
    int pos_flag = 0;
    for(int k = res_j; k >= res_i; k--){
        (*new_data)[k-res_i] = data[k];
        pos_flag = delete_element(data, k, len);
        if(pos_flag == 2){
            return ERR_POS;
        }
    }
    pos_flag = print_data(new_data, new_len, new_len);
    free(*new_data);
    return pos_flag;
}

err print_data(int **data, int *len, int *capacity){
	if (data == NULL || len == NULL || capacity == NULL){
		return ERR_NULL;
	}
    printf("\tВыделено пямяти под массив: %d\n\tДлина массива: %d\n\tМассив: ", *capacity, *len);
    if(*len == 0){
        printf("Массив пуст.\n");
        return ERR_OK;
    }
    for(int i = 0; i < *len; i++){
        printf("%d ", (*data)[i]);
    }
    printf("\n");
    return ERR_OK;
}

err finish_work(int** data, int *len){
	if (data == NULL || len == NULL){
		return ERR_NULL;
	}
    if(*len > 0){
        free(*data);
        *len = 0;
    }
	return ERR_OK;
}

