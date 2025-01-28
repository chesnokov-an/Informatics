#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

List* list_readline(char* PROMPT){
	printf("%s", PROMPT);
	
	char data = getchar();
	Node *ptr = NULL;
	
	List *list = NULL;
	if(data != EOF){
		list = calloc(1, sizeof(List));
	}

	while((data != '\n') && (data != EOF)){
		Node *node = (Node *)malloc(sizeof(Node));
		node->data = data;
		node->next = NULL;
		if(list->head == NULL){
			list->head = node;
			ptr = node;
		}
		else{
			ptr->next = node;
			ptr = node;	
		}
		data = getchar();
	}
	if(data == EOF){
		list_clear(list);
		return NULL;
	}
	if(list->head == NULL){
		Node *node = (Node *)malloc(sizeof(Node));
		node->next = NULL;
		node->data = '\0';
		list->head = node;
	}
	return list;
}

void list_clear(List *list){
	if(list == NULL){
		return;
	}
	while(list->head != NULL){
		Node *tmp = list->head;
		list->head = list->head->next;
		free(tmp);
	}
	free(list);
}

void delete_pre_spaces(List *list){
	if(!list->head){
		return;
	}

	Node *node = list->head;
	while((node) && ((node->data == ' ') || (node->data == '\t'))){
		list->head = list->head->next;
		free(node);
		node = list->head;
	}
}

void delete_big_spaces(List *list){
	if(!list->head){
		return;
	}

	Node *pre_node = list->head;
	Node *node = pre_node->next;
	while(node){
		if(node->data == '\t'){
			node->data = ' ';
		}
		if((node->data == ' ') && (pre_node->data == ' ')){
			pre_node->next = node->next;
			free(node);
			node = pre_node->next;
		}
		else{
			pre_node = node;
			node = node->next;
		}
	}
}

List* list_from_str(char *s){
	List *list = NULL;
	list = calloc(1, sizeof(List));
	Node *ptr = NULL;
	int i = 0;
	while(*(s + i)){
		Node *node = (Node *)malloc(sizeof(Node));
		node->data = *(s + i);
		node->next = NULL;
		if(list->head == NULL){
			list->head = node;
			ptr = node;
		}
		else{
			ptr->next = node;
			ptr = node;	
		}
		i++;
	}
	return list;
}

Node* get_tail(List *list){
	Node *node = list->head;
	if(node){
		while(node->next){
			node = node->next;
		}
	}
	return node;
}

void add_prefix(List *list, char *prefix){
	if(!list->head){
		return;
	}
	Node *node = list->head;
	Node *pre_node = NULL;
	while(node){
		if((node->data != '\0') && strchr("BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz", node->data) && ((pre_node == NULL) || (pre_node->data == ' '))){
			List *list_prefix = list_from_str(prefix);
			Node *new_node = get_tail(list_prefix);
			new_node->next = node;
			if(pre_node == NULL){
				pre_node = new_node;
				list->head = list_prefix->head;
			}
			else{
				pre_node->next = list_prefix->head;
			}
			free(list_prefix);
		}
		pre_node = node;
		node = node->next;
	}
}

void process(List *list, char *prefix){
	if(!list->head){
		return;
	}

	delete_pre_spaces(list);
	delete_big_spaces(list);
	add_prefix(list, prefix);
	Node *node = list->head;
	Node *pre_node = NULL;
	if(node){
		while(node->next){
			pre_node = node;
			node = node->next;
		}
		if(node->data == ' '){
			pre_node->next = NULL;
			free(node);
		}
	}
}


void list_print(List *list, char *PROMPT){
	printf("%s\'", PROMPT);
	Node *node = list->head;
	while(node){
		printf("%c", node->data);
		node = node->next;
	}
	printf("\'\n");
}
