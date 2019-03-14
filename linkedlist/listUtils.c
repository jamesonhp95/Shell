#include "listUtils.h"


Node * buildNode(FILE * in, void *(*buildData)(FILE * in) )
{
   Node * nn = (Node *)calloc(1, sizeof(Node));
   nn->data = buildData(in);
   return nn;
}

Node * buildNodeWithoutFile(char * s, void *(*buildData)(char * s))
{
   Node * nn = (Node *)calloc(1, sizeof(Node));
   nn->data = buildData(s);
   return nn;
}

Node * buildNode_Type(void * passedIn)
{
   Node * nn = (Node *)calloc(1, sizeof(Node));
   nn->data = passedIn;
   return nn;
}

void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
   if(theList == NULL)
      exit(-99);
   if(theList->size == 0 || theList->size == 1)
      printf("Empty List or only one Element.\n");
   else
   {
      Node * start = theList->head->next;
      Node * search;
      Node * min;
      while(start->next != NULL)
      {
         min = start;
         search = start->next;
         while(search != NULL)
         {
            if(compare(min->data, search->data) > 0)
            {
               min = search;
            }
            
            search = search->next;
         }
         void * temp = start->data;
         start->data = min->data;
         min->data = temp;
         start = start->next;
      }
   }
}

void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in))
{
   if(myList == NULL)
      exit(-99);
   if(total <= 0)
      exit(-99);
   int x = 0;
   for(x = 0; x < total; x++)
   {
      addLast(myList, buildNode(fin, buildData));
   }
   
   myList->size = total;
   fclose(fin);
}