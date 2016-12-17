#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjectList.h"
#include "studentList.h"

void fill_student(FILE* input, SLIST* List);
void fill_list(LIST* List, FILE* file);
void addGrade(float* grade, char* str, int credit);
void case0(LIST* List, SLIST* sList);
void case1(LIST* List, SLIST* sList);
void print_list(LIST* List);
void case2(LIST* List, SLIST* sList);

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
			case 0: case0(List, sList);
			case 1: case1(List, sList);break;
			case 2: case2(List, sList); break;
		}
	}
}

void fill_list(LIST* List, FILE* file)
{
	SUBJECT data;
	int n;

	while(!feof(file))
	{
		n = fscanf(file, "%s %s %d", data.sub_code, data.sub_name, &(data.credit));
		if(n == 3) insert_node(List, data);
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
	float grade; 
	int credit;

	printf("\n");
	printf("학번\t | 이름\t  | 학과(학년)\t");
	for(tmp = List->head; tmp; tmp = tmp->next)
		printf(" | %s", tmp->sub_code);
	printf(" | 평점평균\n");

	for(stmp = sList->head; stmp; stmp = stmp->next)
	{
		grade = 0;
		credit = 0;
	
		printf("%d | %s | %s(%d)\t", stmp->id, stmp->name, stmp->dept, stmp->level);
		for(tmp = List->head; tmp; tmp = tmp->next)
		{

			for(i=0; i<stmp->sub_num; i++)
				if(!strcmp(stmp->subjects[i].sub_code, tmp->sub_code))
				{	
					printf(" | %-7s", stmp->subjects[i].grade);
					addGrade(&grade, stmp->subjects[i].grade, tmp->credit);
					credit += tmp->credit;
					break;
				}
			if(i == stmp->sub_num)
				printf(" | %-7s", "-");
		}
		printf(" | %.2f\n", grade/credit);
		printf("\n");
	}
}

void addGrade(float* grade, char* str, int credit)
{
	float tmp = 0;

	if(!strcmp(str, "A+"))
		tmp = 4.3;
	else if(!strcmp(str, "A0"))
		tmp = 4;
	else if(!strcmp(str, "A-"))
		tmp = 3.7;
	else if(!strcmp(str, "B+"))
		tmp = 3.3;
	else if(!strcmp(str, "B0"))
		tmp = 3;
	else if(!strcmp(str, "B-"))
		tmp = 2.7;
	else if(!strcmp(str, "C+"))
		tmp = 2.3;
	else if(!strcmp(str, "C0"))
		tmp = 2;
	else if(!strcmp(str, "C-"))
		tmp = 1.7;
	else if(!strcmp(str, "D+"))
		tmp = 1.3;
	else if(!strcmp(str, "D0"))
		tmp = 1;
	else if(!strcmp(str, "D-"))
		tmp = 0.7;
	else if(!strcmp(str, "F"))
		tmp = 0;

	*grade += credit * tmp;
}

void case2(LIST* List, SLIST* sList)
{
	int n;
	SUBJECT* tmp;
	STUDENT* stmp;
	int num;

	while(1)
	{
		printf("과목목록\n");
		print_list(List);	
		printf("나가기(0) >> "); scanf("%d", &n);
		printf("\n");
	
		if(n == 0)
			return;
		for(tmp = List->head; n>1; n--, tmp = tmp->next);
	
		printf("과목명 : %s(%s), 학점: %d학점\n", tmp->sub_name, tmp->sub_code, tmp->credit);
		printf("\n");
		
		for(stmp = sList->head; stmp; stmp = stmp->next)
		{
			for(num = 0; num < stmp->sub_num; num++)
				if(!strcmp(stmp->subjects[num].sub_code, tmp->sub_code))
				{	

					printf("%d | %s | %s(%d) | %s(%d) \n", stmp->id, stmp->name, stmp->dept, stmp->level, stmp->subjects[num].grade, 4.0);
				}
		}
	}
}

void case0(LIST* List, SLIST* sList)
{
	SUBJECT* before;
	SUBJECT* tmp;
	STUDENT* stmp;
	STUDENT* sbefore;

	for(tmp = List->head; tmp;)
	{
		before = tmp;
		if(before)
		tmp = before->next;
		free(before);
	}

	for(stmp = sList->head; stmp;)
	{
		sbefore = stmp;
		if(sbefore)
		stmp = sbefore->next;
		free(sbefore);
	}
	
	free(List);
	free(sList);

	exit(0);
}
