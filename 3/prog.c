#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "input.h"
#include "array.h"
#include "dialogue_array.h"

int main(){
    int option = -1;
    int* data = NULL;
    int* data_ind = NULL;
    int len = 0;
    int len_ind = 0;
    int capacity = 0;
    err flag = 0;
    err (*func_array[])(int**, int*, int*) = {dialogue_change_memory, initialization, dialogue_add_element, dialogue_delete_element, dialogue_individual, print_data};
    do{
        printf("\n\n---------- МЕНЮ ----------\nВозможные команды:\n\n");
        printf("0: Завершение программы.\n1: Выделение памяти под массив.\n2: Инициализация массива.\n3: Вставка нового элемента.\n4: Удаление элемента.\n5: Индивидуальное задание.\n6: Вывод содержимого массива.\n");
        printf("\nВыберите команду: ");
        flag = (err)input_int(&option, 0, 6);
        printf("\n");
        if(flag == ERR_EOF){
            goto end_program;
        }
        if(option == 0){
            goto end_program;
        }
        flag = func_array[option-1](&data, &len, &capacity);
        
        if(flag == ERR_EOF){
            goto end_program;
        }
        if(flag == ERR_MEM){
            memory_warning();
        }
        if(flag == ERR_POS){
            position_warning();
        }        
    }while(option != 0);
    
    return 0;
    
end_program:
    finish_work(&data, &capacity);
    finish_work(&data_ind, &len_ind);
    return 0;
}

