#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcel.h"

int compar_time(const void *p1, const void *p2){
	return (((Parcel*)p1)->time - ((Parcel*)p2)->time);
}

int compar_time_r(const void *p1, const void *p2){
	return (((Parcel*)p2)->time - ((Parcel*)p1)->time);
}

int compar_id(const void *p1, const void *p2){
	return strcmp(((Parcel*)p1)->id, ((Parcel*)p2)->id);
}

int compar_id_r(const void *p1, const void *p2){
	return strcmp(((Parcel*)p2)->id, ((Parcel*)p1)->id);
}

int compar_name(const void *p1, const void *p2){
	return strcmp(((Parcel*)p1)->full_name, ((Parcel*)p2)->full_name);
}

int compar_name_r(const void *p1, const void *p2){
	return strcmp(((Parcel*)p2)->full_name, ((Parcel*)p1)->full_name);
}

void swap(void *ptr1, void *ptr2, size_t size){
	void *tmp = calloc(size, sizeof(void));
	memcpy(tmp, ptr1, size);
	memcpy(ptr1, ptr2, size);
	memcpy(ptr2, tmp, size);
	free(tmp);
}

void comb_sort(void *data, int num, size_t size, int (*compar) (const void*, const void*)){
	int gap = num;
	int flag = 1;
	while((gap > 1) || (flag)){
		if((gap / 1.3) >= 1){
			gap /= 1.3;
		}
		flag = 0;
		for(size_t i = 0; i < ((num - gap) * size); i += size){
			int j = i + gap * size;
			if(compar(data + i, data + j) > 0){
				swap(data + i, data + j, size);
				flag = 1;
			}
		}
	}
}

void shell_sort(void *data, int num, size_t size, int (*compar) (const void*, const void*)){
	int inc = num / 2;
	while(inc){
		for(size_t i = 0; i < num * size; i += size){
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

void sort(void *data, int num, int size, char *s_value, int compar_index){
	int (*compar[])(const void*, const void*) = {compar_name, compar_name_r, compar_id, compar_id_r, compar_time, compar_time_r};
	if(strcmp(s_value, "comb") == 0){
		comb_sort(data, num, size, compar[compar_index]);
	}
	else if(strcmp(s_value, "shell") == 0){
		shell_sort(data, num, size, compar[compar_index]);
	}
	else if(strcmp(s_value, "qsort") == 0){
		qsort(data, num, size, compar[compar_index]);
	}
}
