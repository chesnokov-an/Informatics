#include <stdio.h>

int input_int(int *data, int start, int end){
    char end_of_scanf = ' ';
    int flag_scanf = scanf("%9d%c", data, &end_of_scanf);

    while((flag_scanf != 2) || (end_of_scanf != '\n') || (*data < start) || (*data > end)){
        if(flag_scanf == EOF){
            return -1;
        }
        if((flag_scanf != 2) || (end_of_scanf != '\n')){
            scanf("%*[^\n]");
        }
        printf("Повторите ввод: ");
        flag_scanf = scanf("%9d%c", data, &end_of_scanf);
    }
    return 0;
}

