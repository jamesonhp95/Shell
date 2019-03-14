#include "history.h"
#include "../tokenize/makeArgs.h"


void cleanTypeHistory(void * hist)
{
   History * temp = (History*)(hist);
   free(temp->com);
   int x = 0;
   for(x = 0; x < temp->numInArgv; x++)
   {
      free(temp->argvCom[x]);
   }
   free(temp->argvCom);
   temp->numInArgv = 0;
   free(temp);
   temp = NULL;
}
void * buildTypeHistory(char *s)
{
   History * theHist = (History *)calloc(1, sizeof(History));
   theHist->com = (char *)calloc(strlen(s)+1, sizeof(char));
   strcpy(theHist->com, s);
   
   int numTokens;
   char copy[100];
   strcpy(copy, s);
   strip(copy);
   numTokens = makeargs(copy, &(theHist->argvCom), " ");
   theHist->numInArgv = numTokens;
   return theHist;
}
void * buildTypeHistoryFromFile(FILE * fin)
{
   char temp[100];
   fgets(temp, 100, fin);
   strip(temp);
   History * theHist = (History *)calloc(1, sizeof(History));
   theHist->com = (char *)calloc(strlen(temp)+1, sizeof(char));
   strcpy(theHist->com, temp);
   
   int numTokens;
   numTokens = makeargs(temp, &(theHist->argvCom), " ");
   theHist->numInArgv = numTokens;
   return theHist; 
}


void printTypeHistory(void * passedIn)
{
   History * temp = (History*)(passedIn);
   printf("%s \n", temp->com);
}

void printToFileTypeHistory(FILE * fout, void * passedIn)
{
   History * temp = (History*)(passedIn);
   fprintf(fout, "%s \n", (temp->com));
}

int compareHistory(const void * p1, const void * p2)
{
   History * left = (History*)(p1);
   History * right = (History*)(p2);
   return (int)(strcmp(left->com, right->com));
}

char * mainDataTypeHistory(void * passedIn)
{
   History * temp = (History*)(passedIn);
   return temp->com;
}