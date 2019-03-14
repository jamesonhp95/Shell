#include "alias.h"
#include "../tokenize/makeArgs.h"


void cleanTypeAlias(void * alias)
{
   Alias * temp = (Alias*)(alias);
   free(temp->nickName);
   free(temp->commandString);
   int x = 0;
   for(x = 0; x < temp->numInCommand; x++)
   {
      free(temp->theCommand[x]);
   }
   free(temp->theCommand);
   temp->numInCommand = 0;
   free(temp);
   temp = NULL;
   
}

void * buildTypeAlias(char *s)
{
   char * str;
   char copy[100];
   strcpy(copy, s);
   strip(copy);
   Alias * alias = (Alias *)calloc(1, sizeof(Alias));
   char * token = strtok_r(copy, " ", &str);
   strip(token);
   token = strtok_r(NULL, "=", &str);
   strip(token);
   alias->nickName = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(alias->nickName, token);
   token = strtok_r(NULL, "\"", &str);
   int numTokens;
   alias->commandString = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(alias->commandString, token);
   numTokens = makeargs(token, &(alias->theCommand), " ");
   alias->numInCommand = numTokens;
   return alias;
}

void * buildTypeAliasFromFile(FILE * fin)
{
   //input style alias LL="ls -al"
   char * str;
   char temp[100];
   fgets(temp, 100, fin);
   strip(temp);
   char copy[100];
   strcpy(copy, temp);
   strip(copy);
   Alias * alias = (Alias *)calloc(1, sizeof(Alias));
   char * token = strtok_r(copy, " ", &str);
   strip(token);
   token = strtok_r(NULL, "=", &str);
   strip(token);
   alias->nickName = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(alias->nickName, token);
   token = strtok_r(NULL, "\"", &str);
   alias->commandString = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(alias->commandString, token);
   int numTokens;
   numTokens = makeargs(token, &(alias->theCommand), " ");
   alias->numInCommand = numTokens;
   return alias;
}

void printTypeAlias(void * passedIn)
{
   Alias * temp = (Alias*)(passedIn);
   printf("Alias %s=\"", temp->nickName);
   int x = 0;
   for(x = 0; x < temp->numInCommand; x++)
   {
      printf("%s", temp->theCommand[x]);
   }
   printf("\" \n");
}

int compareAlias(const void * p1, const void * p2)
{
   Alias * left = (Alias*)(p1);
   Alias * right = (Alias*)(p2);
   return (int)(strcmp(left->nickName, right->nickName));

}

int compareAliasNick(char * s, const void * p2)
{
   Alias * right = (Alias*)(p2);
   return (int)(strcmp(s, right->nickName));
}

void printToFileTypeAlias(FILE * fout, void * passedIn)
{
   Alias * temp = (Alias*)(passedIn);
   fprintf(fout, "Alias %s=\"", temp->nickName);
   fprintf(fout, "%s ", temp->theCommand[0]);
   fprintf(fout, "%s", temp->theCommand[1]);
   fprintf(fout, "\"\n");
}

char * mainDataTypeAlias(void * passedIn)
{
   Alias * temp = (Alias*)(passedIn);
   return temp->commandString;
}