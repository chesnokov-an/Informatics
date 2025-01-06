#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcel.h"

int compar_time(const void *p1, const void *p2){
	return (((Parcel*)p1)->time - ((Parcel*)p2)->time);
}

void comb_sort(void *data, int num, int size, int (*compar) (const void*, const void*)){
	int gap = num;
	int flag = 1;
	while((gap > 1) || (flag)){
		if((gap-1) >= 1){
			gap -= 1;
		}
		flag = 0;
		for(int i = 0; i < ((num - gap) * size); i += size){
			int j = i + gap * size;
			if(compar(data + i, data + j) > 0){
				void *tmp = calloc(size, sizeof(void));
				memcpy(tmp, data + i, size);
				memcpy(data + i, data + j, size);
				memcpy(data + j, tmp, size);
				flag = 1;
				free(tmp);
			}
		}
	}
}

void shell_sort(void *data, int num, int size, int (*compar) (const void*, const void*)){
	int inc = num / 2;
	while(inc){
		for(int i = 0; i < num * size; i += size){
			void *tmp = calloc(size, sizeof(void));
			memcpy(tmp, data + i, size);
			while((i >= inc * size) && (compar(data + i - inc * size, tmp) > 0)){
				memcpy(data + i, data + i - inc * size, size);
				i -= inc * size;
			}
			memcpy(data + i, tmp, size);
			free(tmp);
		}
		inc = (inc == 2) ? 1 : (inc * 5 / 11);
	}
}
