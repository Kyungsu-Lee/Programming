#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "subjectList.h"

void init_list(LIST *pList)
{
	pList->head = NULL;
	pList->count = 0;
}


void insert_node (LIST *List, SUBJECT data)
{
	SUBJECT* node = (SUBJECT*)malloc(sizeof(SUBJECT));
	SUBJECT* tmp = List->head;

	strcpy(node->sub_code, data.sub_code);
	strcpy(node->sub_name, data.sub_name);
	node->credit = data.credit;

	if(!(List->head))
	{
		List->head = node;
		return;
	}



	if(!tmp->next || strcmp(node->sub_code, tmp->sub_code) < 0)
	{
		if(strcmp(node->sub_code, tmp->sub_code) < 0)
		{
			node -> next = List->head;
			List->head = node;
			return;
		}
		else
		{
			tmp->next = node;
			return;
		}
	}


	else
	{
		for(tmp = List->head; tmp->next && !(strcmp(node->sub_code, tmp->sub_code) > 0 && strcmp(node->sub_code, tmp->next->sub_code) < 0) ; tmp = tmp->next)
		{
			if(!strcmp(node->sub_code, tmp->sub_code))
				return;
		}
		node->next = tmp->next;
		tmp->next = node;
		return;


	}
}

void delete_node(LIST* List, char sub_code[])
{
	SUBJECT* tmp;
	SUBJECT* before;

	for(tmp = List->head; tmp && strcmp(tmp->sub_code, sub_code); before = tmp, tmp = before->next);

	if(!tmp)
	{
		printf("Not found\n\n");
	}

	else if(tmp != List->head)
	{
		before->next = tmp->next;
		free(tmp);
	}
	else
	{
		List->head = tmp->next;
		free(tmp);
	}
}
