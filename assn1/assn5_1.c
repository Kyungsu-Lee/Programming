#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjectList.h"

void fill_list(LIST* List, FILE* file);
void print_list(LIST* List);
void add(LIST* List);
void delete(LIST* List);
void quit(LIST* List);

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

	fclose(input_file);

	while(1)
	{
		printf("\n>> "); scanf("%s", input_str);

		if(!strcmp(input_str, "add"))
		{	
			add(List);
		}
		else if(!strcmp(input_str, "show"))
		{
			printf("과목목록\n");
			print_list(List);
		}
		else if(!strcmp(input_str, "delete"))
		{
			delete(List);
		}
		else if(!strcmp(input_str, "quit"))
		{
			quit(List);
		}
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

}


void add(LIST* List)
{
	SUBJECT data;
	
	printf("과목코드 : "); scanf("%s", data.sub_code);
	printf("과목명 : "); scanf("%s", data.sub_name);
	printf("학점 : "); scanf("%d", &(data.credit));
	insert_node(List, data);
}

void delete(LIST* List)
{
	char str[20];
	
	printf("과목코드 : "); scanf("%s", str);
	delete_node(List, str);
}

void quit(LIST* List)
{
	char output[20];
	FILE* output_file;

	SUBJECT* before;
	SUBJECT* tmp;

	printf("파일명 : "); scanf("%s", output);
	output_file = fopen(output, "w");

	for(tmp = List->head; tmp;)
	{
		fprintf(output_file, "%s %s %d\n", tmp->sub_code, tmp->sub_name, tmp->credit);
		before = tmp;
		if(before)
		tmp = before->next;
		free(before);
	}

	free(List);
	fclose(output_file);

	exit(0);
}
