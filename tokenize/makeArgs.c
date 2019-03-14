#include "makeArgs.h"

void clean(int argc, char **argv)
{
   int x = 0;
   for(x = 0; x < argc; x++)
   {
      free(argv[x]);
      argv[x] = NULL;
   }
   free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv, char * delim)
{
   //Make a copy of s
   char copy[100];
   strcpy(copy, s);
   //Determine number of tokens
   char * str;
   int count = 0;
   char * token = strtok_r(s, delim, &str);
   strip(token);
   while(token != NULL)
   {
      count++;
      token = strtok_r(NULL, delim, &str);
   }
   if(count <= 0)
      return -1;
   //Allocate memory for each word
   (*argv) = (char **)calloc(count+1, sizeof(char *));
   token = strtok_r(copy, delim, &str);
   strip(token);
   (*argv)[0] = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy((*argv)[0], token);
   int x = 1;
   for(x = 1; x < count; x++)
   {
      token = strtok_r(NULL, delim, &str);
      strip(token);
      (*argv)[x] = (char *)calloc(strlen(token)+1, sizeof(char));
      strcpy((*argv)[x], token); 
   }
   return count;
}// end makeArgs
