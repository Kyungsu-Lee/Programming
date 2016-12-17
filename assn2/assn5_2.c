#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjectList.h"
#include "studentList.h"

void fill_student(FILE* input, SLIST* List);
void fill_list(LIST* List, FILE* file);
void case1(LIST* List, SLIST* sList);

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

	sList = (SLIST*)malloc(sizeof(SLIST));
	List = (LIST*)malloc(sizeof(LIST));

	if(!(input_subject && input_student))
	{
		printf("파일을 읽어올 수 없습니다.\n");
		exit(-1);
	}

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
			case 1: case1(List, sList);break;
			case 2: break;
		}
	}
}

void fill_list(LIST* List, FILE* file)
{
	SUBJECT data;
	
	if(!file)
		printf("hello\n");

	while(!feof(file))
	{
		fscanf(file, "%s %s %d", data.sub_code, data.sub_name, &(data.credit));
		insert_node(List, data);
	}
}


void fill_student(FILE* input, SLIST* List)
{
	STUDENT data;
	int i = 0;
	int m, n;
	STUDENT* tmp;

	while(!feof(input))
	{
		n = fscanf(input, "%d %s %s %d", &(data.id), data.name, data.dept, &(data.level));
		if(n == -1) return;
		if(n == 4) 
		{
			i = 0; 
			insert_list_student(List, data); 
			for(tmp = List->head; tmp->next; tmp = tmp->next);	
			tmp->sub_num = 0;
			if(n == -1) return;
		}
		printf("%d\n", n);
		fscanf(input, "%s %s", tmp->subjects[i].sub_code, tmp->subjects[i].grade);
		tmp->sub_num++;
		i++;
	}
}


void case1(LIST* List, SLIST* sList)
{
	SUBJECT* tmp;
	STUDENT* stmp;
	int i;

	printf("\n");
	printf("학번\t | 이름\t  | 학과(학년)\t");
	for(tmp = List->head; tmp; tmp = tmp->next)
		printf(" | %s\t", tmp->sub_code);
	printf(" | 평점평균\n");

	for(stmp = sList->head; stmp; stmp = stmp->next)
	{
		printf("%d | %s | %s(%d)\t", stmp->id, stmp->name, stmp->dept, stmp->level);
		for(tmp = List->head; tmp; tmp = tmp->next)
		{
			for(i=0; i<stmp->sub_num; i++)
				if(!strcmp(stmp->subjects[i].sub_code, tmp->sub_code))
					printf("| %s %s\t", stmp->subjects[i].sub_code,stmp->subjects[i].grade);
			if(i == stmp->sub_num)
				printf(" | - \t");
		}
		printf("\n");
	}
}
