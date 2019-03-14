#ifndef REDIRECTS_H
#define REDIRECTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../tokenize/makeArgs.h"


int containsRedirectToFile(char *s);
int containsRedirectFromFile(char *s);
int containsRedirectAppendToFile(char *s);
char ** parsePreRedirectToFile(char *s, int * preRedirectToFile);
char * parsePostRedirectToFile(char *s, int * postRedirectToFile);
char ** parsePreRedirectFromFile(char *s, int *preRedirectFromFile);
char * parsePostRedirectFromFile(char *s, int * postRedirectFromFile);
char ** parsePreRedirectAppendToFile(char *s, int *preRedirectAppendToFile);
char * parsePostRedirectAppendToFile(char *s, int *postRedirectAppendToFile);
void redirectItToFile(char ** preRedirectToFile, char * postRedirectToFile);
void redirectItFromFile(char ** preRedirectFromFile, char * postRedirectFromFile);
void redirectItAppendToFile(char ** preRedirectAppendToFile, char * postRedirectAppendToFile);


#endif 