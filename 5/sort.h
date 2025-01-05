#ifndef SORT_H
#define SORT_H

int compar_time(const void *p1, const void *p2);
void comb_sort(void *data, int num, int size, int (*compar) (const void*, const void*));

#endif
