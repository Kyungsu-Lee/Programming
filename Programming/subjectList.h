#ifndef __SUBJECTLIST_H
#define __SUBJECTLIST_H

typedef struct subject
{
	char sub_code[8];
	char sub_name[41];
	int credit;
	struct subject *next;
} SUBJECT;

typedef struct
{
	int count;
	SUBJECT* head;
}LIST;

void init_list(LIST *pList);
void insert_node (LIST *List, SUBJECT data);
void delete_node(LIST* List, char* sub_code);

#endif
