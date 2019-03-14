#include "linkedList.h"

LinkedList * linkedList(int maximum)
{
   LinkedList * theList = (LinkedList *)calloc(1, sizeof(LinkedList));
   theList->head = (Node *)calloc(1, sizeof(Node));
   theList->head->data = NULL;
   theList->size = 0;
   theList->max = maximum;
   return theList;
}

void addLast(LinkedList * theList, Node * nn)
{
   if(theList->size == 0)
      addFirst(theList, nn);
      
   else
   {
      if(nn != NULL)
      {
         Node * cur = theList->head->next;
         while(cur->next != NULL)
            cur = cur->next;
            
         cur->next = nn;
         nn->prev = cur;
         theList->size = theList->size + 1;
      }
   }
}

void addFirst(LinkedList * theList, Node * nn)
{
   if(theList->size == 0)
   {
      if(nn != NULL)
      {
         theList->head->next = nn;
         nn->prev = theList->head;
         theList->size = theList->size + 1;
      }
   }
   else
   {
      if(nn != NULL)
      {
         theList->head->next->prev = nn;
         nn->next = theList->head->next;
         nn->prev = theList->head;
         theList->head->next = nn;
         theList->size = theList->size + 1;
      }
   }
}

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
   if(theList->size == 0)
      printf("Empty List.\n");
   else
   {
      Node * temp = theList->head->next;
      temp->next->prev = theList->head;
      theList->head->next = temp->next;
      removeData(temp->data);
      free(temp);
      theList->size = theList->size -1;
   }
}

void removeLast(LinkedList * theList, void (*removeData)(void *))
{
   if(theList->size == 0)
      printf("Empty List.\n");
   else
   {
      Node * cur = theList->head->next;
      while(cur->next != NULL)
         cur = cur->next;
      
      cur->prev->next = NULL;
      removeData(cur->data);
      free(cur);
      theList->size = theList->size - 1;
   }
}

void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
   Node * cur = theList->head->next;
   while (cur->next != NULL && compare(cur->data, nn->data) != 0)
      cur = cur->next;

   if(cur != NULL)
   {
      removeData(cur->data);
      if(cur->next != NULL)
         cur->next->prev = cur->prev;
      
      cur->prev->next = cur->next;
      theList->size = theList->size -1;
      
      free(cur);
      removeData(nn->data);
      free(nn);
   }
}

void containsItem(char ** stringToReturn, char * s, LinkedList * theList, int (*compare)(char *, const void *), char * (*mainData)(void *))
{
   Node * cur = theList->head->next;
   while(cur != NULL && compare(s, cur->data) != 0)
      cur = cur->next;
   if(cur == NULL)
   {
      char theReturned[100];
      strcpy(theReturned, "Not Found");
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
   else
   {
      char theReturned[100];
      strcpy(theReturned, mainData(cur->data));
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
}

void clearList(LinkedList * theList, void (*removeData)(void *))
{
   if(theList->size != 0)
   {
      Node * cur = theList->head->next;
      Node * temp;
      while(cur != NULL)
      {
         temp = cur;
         cur = cur->next;
         removeData(temp->data);
         free(temp);
      }
      free(theList->head);
      theList->head = NULL;
      theList->size = 0;
   }
   else
   {
      free(theList->head);
      theList->head = NULL;
      theList->size = 0;
   }
}

void printList(const LinkedList * theList, void (*convertData)(void *))
{
   if(theList->size == 0)
      printf("\n");
   
   else
   {
      Node * cur = theList->head->next;
      if(theList->size < theList->max)
      {
         while(cur != NULL)
         {
            convertData(cur->data);
            if(cur->next == NULL)
               printf("\n");
            cur = cur->next;
         }
      }
      else
      {
         int x = 0;
         while(x < theList->size - theList->max)
		   {
			   cur = cur->next;
			   x++;
		   }
         while(cur != NULL)
         {
            convertData(cur->data);
            if(cur->next == NULL)
               printf("\n");
            cur = cur->next;
         }
      }
   }
}

void writeListToFile(FILE * fout, int maxInFile, LinkedList * list, void (*printDataToFile)(FILE *, void *))
{
   int x = 0;
   Node * cur = list->head->next;
   if(list->size < maxInFile)
   {
      while(cur != NULL)
      {
         printDataToFile(fout, cur->data);
         cur = cur->next;
         x++;
      }
   }
   else
   {
      int x = 0;
      while(x < list->size - maxInFile)
		{
         cur = cur->next;
		   x++;
		}
      while(cur != NULL)
      {
         printDataToFile(fout, cur->data);
         cur = cur->next;
         x++;
      }
   }
   fclose(fout);
}

void getLastMainData(char ** stringToReturn, char * s, LinkedList * theList, char * (*mainData)(void *))
{
   if(theList->size != 0)
   {
      Node * last = theList->head->next;
      while(last->next->next != NULL)
      {
         last = last->next;
      }
      char theReturned[100];
      strcpy(theReturned, mainData(last->data));
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
   else
   {
      char theReturned[100];
      strcpy(theReturned, "Not Found");
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
}

void getIndexMainData(int index, char ** stringToReturn, LinkedList * theList, char * (*mainData)(void *))
{
   Node * cur = theList->head->next;
   if(index <= theList->size)
   {
      int x = 0;
      for(x = 0; x < index; x++)
         cur = cur->next;
      char theReturned[100];
      strcpy(theReturned, mainData(cur->data));
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
   else
   {
      char theReturned[100];
      strcpy(theReturned, "Not Found");
      strip(theReturned);
      char * stringReturn = (char *)calloc(strlen(theReturned)+1, sizeof(char));
      strcpy(stringReturn, theReturned);
      (*stringToReturn) = stringReturn;
   }
}