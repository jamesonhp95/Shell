#include "pipes.h"

int containsPipe(char *s)
{
   char * temp = NULL;
   int count = -1;
   char copy[100];
   strcpy(copy, s);
   char * token = strtok_r(copy, "|", &temp);
   while(token != NULL)
   {
      token = strtok_r(NULL, "|", &temp);
      count++;
   }
   if(count <= 0)
      return -1;
   else
      return count;
}

char ** parsePrePipe(char *s, int * preCount)
{
   char * temp = NULL;
   char copy[100];
   strcpy(copy, s);
   char ** pre = NULL;
   char * token = strtok_r(copy, "|", &temp);
   *preCount = makeargs(token, &pre, " ");
   return pre;
}

char ** parsePostPipe(char *s, int * postCount)
{
   char * temp = NULL;
   char theCopy[100];
   strcpy(theCopy, s);
   char ** post = NULL;
   char * token = strtok_r(theCopy, "|", &temp);
   token = strtok_r(NULL, "|", &temp);
   strip(token);
   *postCount = makeargs(token, &post, " ");
   return post;
}

void pipeIt(char ** prePipe, char ** postPipe)
{
   int status;
   int res;
   int fd[2];
   pid_t pid = fork();
   if(pid == 0)
   {
      res = pipe(fd);
      if(res < 0)
      {
         printf("Pipe Failure \n");
         exit(-1);
      }
      pid_t pid2 = fork();
      if(pid2 == 0)
      {
         close(fd[0]);
		   close(1);
		   dup(fd[1]);
		   close(fd[1]);
         execvp(prePipe[0], prePipe);
         exit(-1);
      }//grandchild of a.out
      else
      {
         waitpid(pid2, &status, 0);
         if(status > 0)
         {
            printf("Invalid command: %s \n", prePipe[0]);
            exit(-1);
         }
         close(fd[1]);
         close(0);
         dup(fd[0]);
         close(fd[1]);
         execvp(postPipe[0], postPipe);
         printf("Invalid command: %s \n", postPipe[0]);
         exit(-1);
      }
   }//child of a.out
   else
   {
      waitpid(pid, &status, 0);
   }//To get shell back
}

void pipeItRedirectToFile(char ** prePipe, char ** postPipe, char * postRedirectToFile)
{
   int status;
   int res;
   int fd[2];
   FILE * fin = fopen(postRedirectToFile, "w");
   int myfd = fileno(fin);
   pid_t pid = fork();
   if(pid == 0)
   {
      res = pipe(fd);
      if(res < 0)
      {
         printf("Pipe Failure \n");
         exit(-1);
      }
      pid_t pid2 = fork();
      if(pid2 == 0)
      {
         close(fd[0]);
		   close(1);
		   dup(fd[1]);
		   close(fd[1]);
         execvp(prePipe[0], prePipe);
         exit(-1);
      }//grandchild of a.out
      else
      {
         waitpid(pid2, &status, 0);
         if(status > 0)
         {
            printf("Invalid command: %s \n", prePipe[0]);
            exit(-1);
         }
         close(fd[1]);
         close(0);
         dup(fd[0]);
         close(fd[1]);
         close(1);
         dup2(myfd, STDOUT_FILENO);
         fclose(fin);
         execvp(postPipe[0], postPipe);
         printf("Invalid command: %s \n", postPipe[0]);
         exit(-1);
      }
   }//child of a.out
   else
   {
      fclose(fin);
      waitpid(pid, &status, 0);
   }//To get shell back
}
void pipeItRedirectFromFile(char ** prePipe, char ** postPipe, char * postRedirectFromFile)
{
   int status;
   int res;
   int fd[2];
   FILE * fin = fopen(postRedirectFromFile, "r");
   int myfd = fileno(fin);
   pid_t pid = fork();
   if(pid == 0)
   {
      res = pipe(fd);
      if(res < 0)
      {
         printf("Pipe Failure \n");
         exit(-1);
      }
      pid_t pid2 = fork();
      if(pid2 == 0)
      {
         close(fd[0]);
		   close(1);
		   dup(fd[1]);
		   close(fd[1]);
         execvp(prePipe[0], prePipe);
         exit(-1);
      }//grandchild of a.out
      else
      {
         waitpid(pid2, &status, 0);
         if(status > 0)
         {
            printf("Invalid command: %s \n", prePipe[0]);
            exit(-1);
         }
         close(fd[1]);
         close(0);
         dup(fd[0]);
         close(fd[1]);
         close(0);
		   dup2(myfd, STDIN_FILENO);
         fclose(fin);
         execvp(postPipe[0], postPipe);
         printf("Invalid command: %s \n", postPipe[0]);
         exit(-1);
      }
   }//child of a.out
   else
   {
      fclose(fin);
      waitpid(pid, &status, 0);
   }//To get shell back
}
void pipeItRedirectAppend(char ** prePipe, char ** postPipe, char * postRedirectAppend)
{
   int status;
   int res;
   int fd[2];
   FILE * fin = fopen(postRedirectAppend, "a");
   int myfd = fileno(fin);
   pid_t pid = fork();
   if(pid == 0)
   {
      res = pipe(fd);
      if(res < 0)
      {
         printf("Pipe Failure \n");
         exit(-1);
      }
      pid_t pid2 = fork();
      if(pid2 == 0)
      {
         close(fd[0]);
		   close(1);
		   dup(fd[1]);
		   close(fd[1]);
         execvp(prePipe[0], prePipe);
         exit(-1);
      }//grandchild of a.out
      else
      {
         waitpid(pid2, &status, 0);
         if(status > 0)
         {
            printf("Invalid command: %s \n", prePipe[0]);
            exit(-1);
         }
         close(fd[1]);
         close(0);
         dup(fd[0]);
         close(fd[1]);
         close(1);
		   dup2(myfd, STDOUT_FILENO);
         fclose(fin);
         execvp(postPipe[0], postPipe);
         printf("Invalid command: %s \n", postPipe[0]);
         exit(-1);
      }
   }//child of a.out
   else
   {
      fclose(fin);
      waitpid(pid, &status, 0);
   }//To get shell back

}