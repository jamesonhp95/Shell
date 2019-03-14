#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./history/history.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/requiredIncludes.h"
#include "./utils/fileUtil.h"
#include "./alias/alias.h"
#include "./redirects/redirects.h"

int main()
{
  int argc, pipeCount, redirectToFile, redirectFromFile, redirectAppend;	
  char **argv = NULL, s[MAX];
  char copyS[100];
  int preCount = 0, postCount = 0, preRedirectCount = 0, postRedirectCount = 0;
  char ** preRedirect = NULL;
  char * postRedirect = NULL;
  char ** prePipe = NULL, ** postPipe = NULL;
  int histC = 100;
  int histFC = 1000;
  int aliasCount = 0;
  int msshrcLines = 0;
  int msshrcHistFileLines = 0;
  char * path = NULL;
  char * getFromListHistory = NULL;
  char * getFromListAlias = NULL;
  char * token = NULL;
  char * holder;
  int unaliasCall = 0;
  int takenCareOf = 0;
  char cwd[1024];
  char * startPath = NULL;
  if(getcwd(cwd, sizeof(cwd)) != NULL)
  {
      strip(cwd);
      startPath = (char *)calloc(strlen(cwd)+1, sizeof(char));
      strcpy(startPath, cwd);
  }
  LinkedList * aliasList = linkedList(1000);
  
  FILE * msshrc = fopen(".msshrc", "r");
  if(msshrc != NULL)
  {
      msshrcLines = countRecords(msshrc, 1);
      if(msshrcLines > 3)
      {
         getCounts(msshrc, &histC, &histFC, &aliasCount, &path);
         fgets(s, MAX, msshrc);
         fgets(s, MAX, msshrc);
         fgets(s, MAX, msshrc);
         buildListTotal(aliasList, msshrcLines-5, msshrc, buildTypeAliasFromFile);
      }
      else
      {
         getCounts(msshrc, &histC, &histFC, &aliasCount, &path);
         fclose(msshrc);
      }
  }
  LinkedList * historyList = linkedList(histC);
  FILE * msshrcHistFile = fopen(".mssh_history", "r");
  if(msshrcHistFile != NULL)
  {
      msshrcHistFileLines = countRecords(msshrcHistFile, 1);
      buildListTotal(historyList, msshrcHistFileLines, msshrcHistFile, buildTypeHistoryFromFile);
  }
  if(path != NULL)
      putenv(path);
  printf("command?: ");
  fgets(s, MAX, stdin);
  strip(s);
  addLast(historyList, buildNodeWithoutFile(s, buildTypeHistory));
  
  while(strcmp(s, "exit") != 0)
  {
   
   
   //See if string is alias, to be used later:
   containsItem(&getFromListAlias, s, aliasList, compareAliasNick, mainDataTypeAlias);
   //End check if string is alias.
   
   //Check if unalias is being called:
   if(strstr(s, "unalias") != NULL)
   {
      copyS[100];
      strcpy(copyS, s);
      strip(copyS);
      token = strtok_r(copyS, " ", &holder);
      token = strtok_r(NULL, " ", &holder);
      strcpy(s, token); 
      unaliasCall = 1;
   }//End check if unalias exists.
   
   //Check if it is ! or !!:
   if(strstr(s, "!") != NULL)
   {
      if(strcmp(s, "!!") ==0)
      {
         getLastMainData(&getFromListHistory, s, historyList, mainDataTypeHistory);
         if(strcmp(getFromListHistory, "Not Found") != 0)
         {
            strcpy(s, getFromListHistory);
            free(getFromListHistory);
            getFromListHistory = NULL;
         }
         else
         {
            free(getFromListHistory);
            getFromListHistory = NULL;
         }
      }
      else
      {
         copyS[100];
         strcpy(copyS, s);
         strip(copyS);
         token = strtok_r(copyS, "!", &holder);
         int theIndex = atoi(token);
         getIndexMainData(theIndex, &getFromListHistory, historyList, mainDataTypeHistory);
         if(strcmp(getFromListHistory, "Not Found") != 0)
         {
            strcpy(s, getFromListHistory);
            free(getFromListHistory);
            getFromListHistory = NULL;
         }
         else
         {
            free(getFromListHistory);
            getFromListHistory = NULL;
         }
      }
   }//End check if it is ! or !!
   
   //Check if it is an alias:
   else if((strcmp(getFromListAlias, "Not Found") != 0) && (unaliasCall == 0))
   {
      strcpy(s, getFromListAlias);
      free(getFromListAlias);
      getFromListAlias = NULL;
      takenCareOf = 0;
   }//End check if it is an alias.
   
   //Check if it is making an alias.
   else if(strstr(s, "alias") != NULL && strstr(s, "unalias") == NULL)
   {
      if(strcmp(getFromListAlias, "Not Found") != 0)
      {
         removeItem(aliasList, buildNodeWithoutFile(s, buildTypeAlias), cleanTypeAlias, compareAlias);
         addLast(aliasList, buildNodeWithoutFile(s, buildTypeAlias));
      }
      else
      {
         addLast(aliasList, buildNodeWithoutFile(s, buildTypeAlias));
      }
      strcpy(s, getFromListAlias);
      free(getFromListAlias);
      getFromListAlias = NULL;
      takenCareOf = 1;
   }//End check if it is making an alias
   
   //Check if it is unaliasing an alias
   else if(strstr(s, "unalias") != NULL)
   {
      if(strcmp(getFromListAlias, "Not Found") == 0)
         printf("Invalid command. No alias found to unalias. \n");
      else
      {
         removeItem(aliasList, buildNodeWithoutFile(s, buildTypeAlias), cleanTypeAlias, compareAlias);
      }
      strcpy(s, getFromListAlias);
      free(getFromListAlias);
      getFromListAlias = NULL;
      takenCareOf = 1;
   }//End check if it is unaliasing an alias
   
   //Check if it has a Pipe
	pipeCount = containsPipe(s);
   redirectToFile = containsRedirectToFile(s);
   redirectFromFile = containsRedirectFromFile(s);
   redirectAppend = containsRedirectAppendToFile(s);
   printf("pipeCount: %d redirectToFile: %d redirectFromFile: %d redirectAppend: %d \n", pipeCount, redirectToFile, redirectFromFile, redirectAppend);
   if(redirectToFile > 0 && strstr(s, ">>") == NULL && pipeCount < 0)
   {
      preRedirect = parsePreRedirectToFile(s, &preRedirectCount);
      postRedirect = parsePostRedirectToFile(s, &postRedirectCount);
      redirectItToFile(preRedirect, postRedirect);
      clean(preRedirectCount, preRedirect);
      free(postRedirect);
   }
   else if(redirectAppend > 0 && pipeCount < 0)
   {
      preRedirect = parsePreRedirectAppendToFile(s, &preRedirectCount);
      postRedirect = parsePostRedirectAppendToFile(s, &postRedirectCount);
      redirectItAppendToFile(preRedirect, postRedirect);
      clean(preRedirectCount, preRedirect);
      free(postRedirect);
   }
   else if(redirectFromFile > 0 && pipeCount < 0)
   {
      preRedirect = parsePreRedirectFromFile(s, &preRedirectCount);
      postRedirect = parsePostRedirectFromFile(s, &postRedirectCount);
      redirectItFromFile(preRedirect, postRedirect);
      clean(preRedirectCount, preRedirect);
      free(postRedirect);
   }
   else if(pipeCount > 0 && redirectFromFile < 0 && redirectToFile < 0 && redirectAppend < 0)
	{
      
		prePipe = parsePrePipe(s, &preCount);
		postPipe = parsePostPipe(s, &postCount);
      pipeIt(prePipe, postPipe);
		clean(preCount, prePipe);
      clean(postCount, postPipe);
	}// end if pipeCount	  
   else if(pipeCount > 0)
   {
      strcpy(copyS, s);
      if(strstr(copyS, "<") != NULL)
      {
         token = strtok_r(copyS, "<", &holder);
         strip(token);
         prePipe = parsePrePipe(token, &preCount);
		   postPipe = parsePostPipe(token, &postCount);
         token = strtok_r(NULL, " ", &holder);
         strip(token);
         postRedirect = (char *)calloc(strlen(token)+1, sizeof(char));
         strcpy(postRedirect, token);
         pipeItRedirectFromFile(prePipe, postPipe, postRedirect);
         clean(preCount, prePipe);
         clean(postCount, postPipe);
         free(postRedirect);
      }
      else if(strstr(copyS, ">") != NULL && strstr(s, ">>") == NULL)
      {
         token = strtok_r(copyS, ">", &holder);
         strip(token);
         prePipe = parsePrePipe(token, &preCount);
		   postPipe = parsePostPipe(token, &postCount);
         token = strtok_r(NULL, " ", &holder);
         strip(token);
         postRedirect = (char *)calloc(strlen(token)+1, sizeof(char));
         strcpy(postRedirect, token);
         pipeItRedirectToFile(prePipe, postPipe, postRedirect);
         clean(preCount, prePipe);
         clean(postCount, postPipe);
         free(postRedirect);
           
      }
      else if(strstr(copyS, ">>") != NULL)
      {
         token = strtok_r(copyS, ">>", &holder);
         prePipe = parsePrePipe(token, &preCount);
		   postPipe = parsePostPipe(token, &postCount);
         token = strtok_r(NULL, " ", &holder);
         token = strtok_r(NULL, " ", &holder);
         strip(token);
         postRedirect = (char *)calloc(strlen(token)+1, sizeof(char));
         strcpy(postRedirect, token);
         pipeItRedirectAppend(prePipe, postPipe, postRedirect);
         clean(preCount, prePipe);
         clean(postCount, postPipe);
         free(postRedirect);
      }
   }
   //Check if command is history:
   else if(strcmp(s, "history") == 0)
   {
      printList(historyList, printTypeHistory);
   }
   //End check if command is history.
   
   //Check if cd
   else if(strstr(s, "cd") != NULL)
   {
      strcpy(copyS, s);
      token = strtok_r(copyS, " ", &holder);
      token = strtok_r(NULL, " ", &holder);
      strip(token);
      int returned;
      returned = chdir(token);
   }//end check if cd.
   
   //Check if change path
   else if(strstr(s, "PATH") != NULL)
   {//command style; PATH=$PATH:/data/myprogs
      putenv(s);
   }//end check if change path
   //Else try executing like normal:
	else if(takenCareOf == 0)
	{
		argc = makeargs(s, &argv, " ");
	  	if(argc != -1)
	  		forkIt(argv);
	  
	  	clean(argc, argv);
	  	argv = NULL;
      free(getFromListAlias);
      getFromListAlias = NULL;
	}//End try executing like normal.
	
   
	printf("command?: ");
	fgets(s, MAX, stdin);
   strip(s);
   addLast(historyList, buildNodeWithoutFile(s, buildTypeHistory));
  }// end while
  
  msshrcHistFile = fopen(".mssh_history", "w");
  writeListToFile(msshrcHistFile, histFC, historyList, printToFileTypeHistory);
  /*
  msshrc = fopen(".msshrc", "w");
  fprintf(msshrc, "HISTCOUNT=%d\n", histC);
  fprintf(msshrc, "HISTFILECOUNT=%d\n\n", histFC);
  writeListToFile(msshrc, 1000, aliasList, printToFileTypeAlias);
  msshrc = fopen(".msshrc", "a");
  if(aliasList->size != 0)
      fprintf(msshrc, "\n");
  if(startPath != NULL)
      fprintf(msshrc, "PATH=$PATH:%s", startPath);
  fclose(msshrc);*/
  free(startPath);
  clearList(historyList, cleanTypeHistory);
  clearList(aliasList, cleanTypeAlias);
  free(historyList);
  free(aliasList);
  historyList = NULL;
  aliasList = NULL;
  if(path != NULL)
  {
   free(path);
   path = NULL;
  }
  return 0;

}// end main

