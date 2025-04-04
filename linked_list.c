#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
	struct list_node *node = NULL;

	node = malloc(sizeof(struct list_node));

	node->value = value;
	node->next = NULL;

	return node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
	struct list_node * node = new_node(value);

	node->next = list->head;

	list->head = node;

	return;
}

void insert_at_tail(struct linked_list *list, size_t value) {
	
	struct list_node * node = new_node(value);
		
	struct list_node * testNode = list->head;

	if(testNode == NULL)
	{
		list->head = node;
		//printf("%ld", node->value);
		return;
	}

	
	
	while(testNode->next != NULL)
	{
		testNode = testNode->next;
	}

	testNode->next = node;

	return;
}

size_t remove_from_head(struct linked_list *list) { 
	
	struct list_node * node = list->head;

	size_t num = node->value;

	list->head = list->head->next;
	
	free(node);

	return num;
}

size_t remove_from_tail(struct linked_list *list) { 

	struct list_node * testNode = list->head;
	size_t num;


	if(testNode == NULL)
	{
		return 0;
	}

	if(testNode->next == NULL)
	{
		list->head = NULL;
		free(testNode);
		return 0;
	}

	while(testNode->next->next != NULL)
	{
		testNode = testNode->next;
	}

	num = testNode->next->value;
	free(testNode->next);


	return num; 
}

void free_list(struct linked_list list) {
	struct list_node * node;

	while(list.head != NULL)
	{
		node = list.head;
		list.head = list.head->next;
		free(node);
	}
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
