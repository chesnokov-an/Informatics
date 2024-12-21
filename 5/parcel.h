#ifndef PARCEL_H
#define PARCEL_H

typedef struct Parcel {
	char *full_name;
	long time;
	char id[10];
} Parcel;

void print_parcel(Parcel parcel);
err correct_id(char *id);
err console_input_parcel(Parcel *parcel);
err console_input_data(Parcel **data, int *size_data);
err txt_input_parcel(FILE* file_name, Parcel *parcel);
err txt_input_data(FILE* file_name, Parcel **data, int *size_data);



#endif
