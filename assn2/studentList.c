#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "studentList.h"

void init_list(LIST *pList)
{
	pList->head = NULL;
	pList->count = 0;
}
