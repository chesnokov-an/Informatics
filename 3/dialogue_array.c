#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "input.h"
#include "array.h"

err dialogue_change_memory(int **data, int *len, int *capacity){
    int extra_capacity = 0;
    printf("\tВведите количество ячеек памяти, которое нужно выделить (довыделить) под массив. (Если хотите уменьшить их количество, введите отрицательное число): ");
    int flag = input_int(&extra_capacity, INT_MIN, INT_MAX);
    if(flag == -1){
        return ERR_EOF;
    }
    return change_memory(data, capacity, *len, extra_capacity);
}

err dialogue_add_element(int **data, int *len, int *capacity){
    if(*len == *capacity){
        printf("\tВсе ячейки памяти заполнены.\n");
        return ERR_OK;
    }
    int elem = 0;
    int pos = 0; 
    printf("\tВставка нового элемента:\n\tВведите элемент, который нужно добавить в массив: ");
    int flag = input_int(&elem, INT_MIN, INT_MAX);
    if(flag == -1){
        return ERR_EOF;
    }
    printf("\tВведите позицию, на которую нужно добавить элемент: ");
    flag = input_int(&pos, 0, INT_MAX);
    if(flag == -1){
        return ERR_EOF;
    }
    return add_element(*data, elem, pos, len);
}

err dialogue_delete_element(int **data, int* len, int *capacity){
    if(*len == 0){
        printf("\tМассив пуст.\n");
        return ERR_OK;
    }
    int pos = 0;
    printf("\tУдаление элемента:\n\tВведите позицию элемента, который требуется удалить: ");
    int flag = input_int(&pos, 0, *len-1);
    if(flag == -1){
        return ERR_EOF;
    }
    return delete_element(*data, pos, len);
}

err dialogue_individual(int** data, int* len, int* capacity){
    int *data_ind = NULL;
    int len_ind = 0;
	int new_capacity = 0;
    printf("\tИндивидуальное задание:\n");
    if(*len == 0){
        printf("\tМассив пуст.\n");
        return ERR_OK;
    }
    return individual(*data, &data_ind, len, &len_ind, &new_capacity);
}

void memory_warning(){
    printf("\tОшибка: не удалось выделить память.\n");
}

void position_warning(){
    printf("\tОшибка: введено некорректное значение.\n");
}








