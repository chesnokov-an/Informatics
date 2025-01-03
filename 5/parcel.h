#ifndef PARCEL_H
#define PARCEL_H

typedef struct Parcel {
	char *full_name;
	long time;
	char id[10];
} Parcel;

err console_input_data(Parcel **data, int *size_data);
err txt_input_data(FILE* file_name, Parcel **data, int *size_data);
err bin_input_data(FILE* file_name, Parcel **data, int *size_data);

void print_parcel(Parcel parcel);
void txt_print_parcel(FILE *file_name, Parcel parcel);
void bin_print_parcel(FILE *file_name, Parcel parcel);

#endif
