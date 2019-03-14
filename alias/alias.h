#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/myUtils.h"

struct alias
{
   char * nickName;
   char * commandString;
   char ** theCommand;
   int numInCommand;
};
typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char *s);
void * buildTypeAliasFromFile(FILE * fin);
void printTypeAlias(void * passedIn);
int compareAlias(const void * p1, const void * p2);
char * returnTypeAlias(void * passedIn);
void printToFileTypeAlias(FILE * fout, void * passedIn);
char * mainDataTypeAlias(void * passedIn);
int compareAliasNick(char * s, const void * p2);


#endif
