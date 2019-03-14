#ifndef HISTORY_H_
#define HISTORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/myUtils.h"

struct history
{
   char * com;
   char ** argvCom;
   int numInArgv;
};
typedef struct history History;

void cleanTypeHistory(void * ptr);
void * buildTypeHistory(char *s);
void * buildTypeHistoryFromFile(FILE * fin);
void printTypeHistory(void * passedIn);
int compareHistory(const void * p1, const void * p2);
void printToFileTypeHistory(FILE * fout, void * passedIn);
char * mainDataTypeHistory(void * passedIn);


#endif
