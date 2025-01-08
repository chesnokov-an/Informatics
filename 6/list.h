#ifndef LIST_H
#define LIST_H

typedef struct Node{
	char data;
	struct Node *next;
}Node;

typedef struct List{
	Node *head;
	Node *tail;
}List;

typedef enum err{
	ERR_OK = 0,
	ERR_EOF = -1,
	ERR_MEM = 1,
	ERR_VAL = 2,
	ERR_NULL = 3,
}err;

err list_readline(List *list);
void list_clear(List *list);
void process(List *list, char prefix);
void list_print(List *list);

#endif
