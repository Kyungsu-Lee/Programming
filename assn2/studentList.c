#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "studentList.h"


void init_list_student(SLIST *pList)
{
	pList->head = NULL;
}


void insert_list_student(SLIST* List, STUDENT data)
{
	int i;	
	STUDENT* node = (STUDENT*)malloc(sizeof(STUDENT));
	STUDENT* tmp;

	node->id = data.id;
	strcpy(node->name, data.name);
	strcpy(node->dept, data.dept);
	node->level = data.level;
	//node->sub_num = data.sub_num;
	//for(i=0; i<data.sub_num; i++)
	//	node->subjects[i] = data.subjects[i];

	if(!(List->head)) // empty
	{
		List->head = node;
	}

	else
	{
		for(tmp = List->head; tmp->next; tmp = tmp->next);
		tmp->next = node;
	}
}
