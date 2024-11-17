#ifndef ARRAY_H
#define ARRAY_H

typedef enum err{
    ERR_OK = 0,
    ERR_EOF = -1,
    ERR_MEM = 1,
    ERR_POS = 2,
}err;

err change_memory(int**, int*, int, int);
err initialization(int**, int*, int*);
err add_element(int**, int, int, int*);
err delete_element(int**, int, int*);
err individual(int**, int**, int*, int*);
err print_data(int**, int*, int*);
void finish_work(int**, int*);

#endif
