#ifndef LIST_H
#define LIST_H

typedef struct Node{
	char data;
	struct Node *next;
}Node;

typedef struct List{
	Node *head;
}List;

List list_readline(char *PROMPT);
void list_clear(List *list);
void process(List *list, char *prefix);
void list_print(List *list, char *PROMPT);
List list_from_str(char *s);

#endif
