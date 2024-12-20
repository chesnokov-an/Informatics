#ifndef PARCEL_H
#define PARCEL_H

typedef struct Parcel {
	char *full_name;
	char id[10];
	int time;
} Parcel;

void print_parcel(Parcel parcel);
err correct_id(char *id);
err input_console(Parcel *parcel);




#endif
