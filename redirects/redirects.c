#include "redirects.h"


int containsRedirectToFile(char *s)
{
   char * temp = NULL;
   int count = -1;
   char copy[100];
   strcpy(copy, s);
   char * token = strtok_r(copy, ">", &temp);
   while(token != NULL)
   {
      token = strtok_r(NULL, ">", &temp);
      count++;
   }
   if(count <= 0)
      return -1;
   else
      return count;
}

int containsRedirectAppendToFile(char *s)
{
   char * temp = NULL;
   int count = -1;
   char copy[100];
   strcpy(copy, s);
   char * token = strtok_r(copy, ">>", &temp);
   while(token != NULL)
   {
      token = strtok_r(NULL, ">>", &temp);
      count++;
   }
   if(count <= 0)
      return -1;
   else
      return count;
}

int containsRedirectFromFile(char *s)
{
   char * temp = NULL;
   int count = -1;
   char copy[100];
   strcpy(copy, s);
   char * token = strtok_r(copy, "<", &temp);
   while(token != NULL)
   {
      token = strtok_r(NULL, "<", &temp);
      count++;
   }
   if(count <= 0)
      return -1;
   else
      return count;
}

char ** parsePreRedirectToFile(char *s, int * preRedirectToFile)
{
   char * temp = NULL;
   char copy[100];
   strcpy(copy, s);
   char ** pre = NULL;
   char * token = strtok_r(copy, ">", &temp);
   *preRedirectToFile = makeargs(token, &pre, " ");
   return pre;
}

char * parsePostRedirectToFile(char *s, int * postRedirectToFile)
{
   char * temp = NULL;
   char theCopy[100];
   strcpy(theCopy, s);
   char * token = strtok_r(theCopy, ">", &temp);
   strip(token);
   token = strtok_r(NULL, " ", &temp);
   strip(token);
   char * post = (char *)calloc(strlen(token)+1, sizeof(char));
   *postRedirectToFile = strlen(token);
   strcpy(post, token);
   return post;
}

char ** parsePreRedirectFromFile(char *s, int *preRedirectFromFile)
{
   char * temp = NULL;
   char copy[100];
   strcpy(copy, s);
   char ** pre = NULL;
   char * token = strtok_r(copy, "<", &temp);
   *preRedirectFromFile = makeargs(token, &pre, " ");
   return pre;
}

char * parsePostRedirectFromFile(char *s, int * postRedirectFromFile)
{
   char * temp = NULL;
   char theCopy[100];
   strcpy(theCopy, s);
   char * token = strtok_r(theCopy, "<", &temp);
   token = strtok_r(NULL, " ", &temp);
   strip(token);
   char * post = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(post, token);
   return post;
}

char ** parsePreRedirectAppendToFile(char *s, int *preRedirectAppendToFile)
{
   char * temp = NULL;
   char copy[100];
   strcpy(copy, s);
   char ** pre = NULL;
   char * token = strtok_r(copy, ">>", &temp);
   *preRedirectAppendToFile = makeargs(token, &pre, " ");
   return pre;
}

char * parsePostRedirectAppendToFile(char *s, int *postRedirectAppendToFile)
{
   char * temp = NULL;
   char theCopy[100];
   strcpy(theCopy, s);
   char * token = strtok_r(theCopy, ">>", &temp);
   token = strtok_r(NULL, " ", &temp);
   token = strtok_r(NULL, " ", &temp);
   strip(token);
   char * post = (char *)calloc(strlen(token)+1, sizeof(char));
   strcpy(post, token);
   return post;
}

void redirectItToFile(char ** preRedirectToFile, char * postRedirectToFile)
{
   int status;
   int res = 1;
   int fd[2];
   pid_t pid = fork();
   if(pid == 0)
   {
      FILE * fin = fopen(postRedirectToFile, "w");
      if(fin == NULL)
         res = -1;
      if(res < 0)
      {
         printf("Redirect to file Failure \n");
         exit(-1);
      }
      int myfd = fileno(fin);
      close(1);
		dup2(myfd, STDOUT_FILENO);
      fclose(fin);
      execvp(preRedirectToFile[0], preRedirectToFile);
      exit(-1);
      
   }
   else
   {
      waitpid(pid, &status, 0);
   }//To get shell back

}
void redirectItFromFile(char ** preRedirectFromFile, char * postRedirectFromFile)
{
   int status;
   int res = 1;
   int fd[2];
   pid_t pid = fork();
   if(pid == 0)
   {
      FILE * fin = fopen(postRedirectFromFile, "r");
      if(fin == NULL)
         res = -1;
      if(res < 0)
      {
         printf("Redirect to file Failure \n");
         exit(-1);
      }
      int myfd = fileno(fin);
      close(0);
		dup2(myfd, STDIN_FILENO);
      fclose(fin);
      execvp(preRedirectFromFile[0], preRedirectFromFile);
      exit(-1);
      
   }
   else
   {
      waitpid(pid, &status, 0);
   }//To get shell back
}
void redirectItAppendToFile(char ** preRedirectAppendToFile, char * postRedirectAppendToFile)
{
   int status;
   int res = 1;
   int fd[2];
   pid_t pid = fork();
   if(pid == 0)
   {
      FILE * fin = fopen(postRedirectAppendToFile, "a");
      if(fin == NULL)
         res = -1;
      if(res < 0)
      {
         printf("Redirect to file Failure \n");
         exit(-1);
      }
      int myfd = fileno(fin);
      close(1);
		dup2(myfd, STDOUT_FILENO);
      fclose(fin);
      execvp(preRedirectAppendToFile[0], preRedirectAppendToFile);
      exit(-1);
      
   }
   else
   {
      waitpid(pid, &status, 0);
   }//To get shell back
}