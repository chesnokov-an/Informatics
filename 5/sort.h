#ifndef SORT_H
#define SORT_H
/*
int compar_time(const void *p1, const void *p2);
int compar_time_r(const void *p1, const void *p2);
int compar_id(const void *p1, const void *p2);
int compar_id_r(const void *p1, const void *p2);
int compar_name(const void *p1, const void *p2);
int compar_name_r(const void *p1, const void *p2);*/

void comb_sort(void *data, int num, int size, int (*compar) (const void*, const void*));
void shell_sort(void *data, int num, int size, int (*compar) (const void*, const void*));
void sort(void *data, int num, int size, char* s_value, int flag_f, char* f_value, int flag_r);


#endif
