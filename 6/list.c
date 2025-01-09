#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

err list_readline(List *list){
	char data = getchar();
	Node *ptr = NULL;
	while((data != '\n') && (data != EOF)){
		Node *node = (Node *)malloc(sizeof(Node));
		if(!node){
			return ERR_MEM;
		}
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
		return ERR_EOF;
	}
	return ERR_OK;
}

void list_clear(List *list){
	while(list->head != NULL){
		Node *tmp = list->head;
		list->head = list->head->next;
		free(tmp);
	}
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
/*
List list_from_str(char* s){
	List res = {}
}
*/
void add_prefix(List *list, char prefix){
	if(!list->head){
		return;
	}

	Node *node = list->head;
	Node *pre_node = NULL;
	while(node){
		if(strchr("BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz", node->data) && ((pre_node == NULL) || (pre_node->data == ' '))){
			Node *new_node = (Node *)malloc(sizeof(Node));
			new_node->next = node;
			new_node->data = prefix;
			if(pre_node == NULL){
				pre_node = new_node;
				list->head = new_node;
			}
			else{
				pre_node->next = new_node;
			}
		}
		pre_node = node;
		node = node->next;
	}

}

void process(List *list, char prefix){
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


void list_print(List *list){
	Node *node = list->head;
	printf("output: \'");
	while(node){
		printf("%c", node->data);
		node = node->next;
	}
	printf("\'\n");
}
