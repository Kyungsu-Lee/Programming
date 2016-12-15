#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void fill_list(LIST* List, FILE* file);
void print_list(LIST* List);

int main(int argc, char* argv[])
{
	FILE* input_file;
	char* input = "subject.txt";
	LIST* List = (LIST*)malloc(sizeof(LIST));
	char input_str[10];

	if(argc != 1)
	{
		input = argv[1];
	}

	if( !(input_file = fopen(input, "r")) )
	{
		printf("파일을 읽어올 수 없습니다.\n");
		//system("pause");
		exit(1);
	}

	init_list(List);
	fill_list(List, input_file);
	printf("과목목록\n");
	print_list(List);
	while(1)
	{
	printf("\n>> "); scanf("%s", input_str);

	if(!strcmp(input_str, "add"))
	{	
		
	}
	else if(!strcmp(input_str, "show"))
	{
		printf("과목목록\n");
		print_list(List);
	}
	else if(!strcmp(input_str, "delete"))
	{
		
	}
	else if(!strcmp(input_str, "quit"))
	{
		
	}
}
}

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
	node->next = List->head;

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
		for(tmp = List->head; !(strcmp(node->sub_code, tmp->sub_code) > 0 && strcmp(node->sub_code, tmp->next->sub_code) < 0) && tmp->next; tmp = tmp->next)
		{
			if(!strcmp(node->sub_code, tmp->sub_code))
				return;
		}

		node->next = tmp->next;
		tmp->next = node;
		return;


	}

}

void delete_node(LIST* List, char* sub_code)
{
	SUBJECT* tmp;
	SUBJECT* before;

	for(tmp = List->head; tmp && strcmp(tmp->sub_code, sub_code); before = tmp, tmp = tmp->next);

	if(!tmp)
	{
		printf("Not found\n\n");
	}

	else
	{
		before->next = tmp->next;
		free(tmp);
	}
}

void fill_list(LIST* List, FILE* file)
{
	SUBJECT data;

	while(!feof(file))
	{
		fscanf(file, "%s %s %d", data.sub_code, data.sub_name, &(data.credit));
		insert_node(List, data);
	}
}

void print_list(LIST* List)
{
	SUBJECT* tmp;
	int i=0;

	for(tmp = List->head; tmp; tmp = tmp->next, i++)
	{
		printf("  %d %s %s (%d학점)\n", i+1, tmp->sub_code, tmp->sub_name, tmp->credit);
	}

	printf("\n");
}
