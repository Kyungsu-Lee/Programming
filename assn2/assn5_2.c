#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjectList.h"
#include "studentList.h"

void fill_student(FILE* input, SLIST* List);
void fill_list(LIST* List, FILE* file);

int main(int argc, char* argv[])
{	
	FILE* input_subject;
	FILE* input_student;
	char input_subj[20];
	char input_stu[20];

	int input;
	SLIST* sList;
	LIST* List;

	if(argc != 3)
	{
		strcpy(input_subj, "new_subject.txt");
		strcpy(input_stu, "student.txt");
	}

	else
	{
		strcpy(input_subj, argv[1]);
		strcpy(input_stu, argv[2]);
	}

	input_subject = fopen(input_subj, "r");
	input_student = fopen(input_stu, "r");

	if(!(input_subject && input_student))
	{
		printf("파일을 읽어올 수 없습니다.\n");
		exit(-1);
	}

	printf("well\n");
	fill_student(input_student, sList);
	fill_list(List, input_subject);

	while(1){
		printf("\n");
		printf(" ### 성적관리시스템 ###\n");
		printf(" 1. 학생별 성적\n");
		printf(" 2. 과목별 성적\n");
		printf(" 0. 종료\n");
		printf(" >> "); scanf("%d", &input);

		switch(input)
		{
			case 0: exit(0);
			case 1: break;
			case 2: break;
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


void fill_student(FILE* input, SLIST* List)
{
	STUDENT data;
	char line[100];
	while(!feof(input))
	{
		fscanf(input, "%d %s %s %d", &(data.id), data.name, data.dept, &(data.level));
		fgets(line, 100, input);
		printf("%s\n", data.name);
	}
}
