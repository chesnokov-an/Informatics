#ifndef DIALOGUE_ARRAY_H
#define DIALOGUE_ARRAY_H

#include "array.h"

err dialogue_change_memory(int**, int*, int*);
err dialogue_add_element(int**, int*, int*);
err dialogue_delete_element(int**, int*, int*);
err dialogue_individual(int**, int*, int*);
void memory_warning();
void position_warning();

#endif
