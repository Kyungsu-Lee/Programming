#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjectList.h"

int main(int argc, char* argv[])
{	
	FILE* input_subject;
	FILE* input_student;
	char input_subj[20];
	char input_stu[20];

	int input;

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

