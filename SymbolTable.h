#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HelpTools.h"
#define maxLength 32
typedef struct Label Label;

struct Label
{
    char* symbol;
    int value;
    char* attribute;
    Label *next;
};

typedef struct LabelList
{
    Label *head;
} LabelList;


/*
Function createLabel-
Function allocates dynamic memory to new Label, and sets the label symbol to argument "symbol", sets Label value to argument "val" and sets attribute to arguments "att" ,sets the pointer to the next label to NULL
if the values given are valid,the function returns pointer to the new label.
 prints error massage and return NULL.
 */
Label *createLabel(int val, char* att,char*symbol);


/*
allocate dynamic memory to new LabelList, set the head of the list to NULL, 
returns pointer to the new List.  
 */
LabelList *createList();


/*
Function removeLabel-
remove label "lab" given as argument, and free the allocated memory given by createLabel
 */
void removeLabel(Label *lab);


/*
Function InsertLabel-
function insert the new "nlabel" label given as argument to the end of the LabelList "list", 
If the new label given is already in the given list,print error massage and label will now be inserted again.
returns boolean int that present weather the label is inserted or not.
 */
int InsertLabel(LabelList *list,Label *nlabel,Label *listLabel);


/*
Function RemoveList-
Recursive function on Labellist - remove the LabelList and free the allocated memory, first call will be with list->head as "label".
 */
void RemoveList(LabelList *list, Label *label);


/*
Function printList-
Recursive function on Labellist - print LabelList, first call will be with list->head as "label".
 */
void printList(Label *label);


/*
Function addValueToLabels-
Recursive function on Labellist - add given value "toadd" to all labels value field in the  list that match with the given attribute.first call will be with list->head as "label".
*/
void addValueToLabels(Label *label,int toadd,char * attribute);


/*
Function addAttributeToLabel-
Recursive function on Labellist - add the attribute given as string "toadd" to all the labels in the list that have the same symbol as given String argument -"symbol".
function calaculate with  with the argument "count" how many match cases there is in the list and returns the total.
first call will be with list->head as "label".
*/
int addAttributeToLabel(Label *label,char*toadd, char* symbol,int count);


/*
Function getLabel-
Recursive function on Labellist - return the label matches with the given symbol as argument - if label cannot be found -returns NULL
*/
Label * getLabel(Label *listlabel,char*symbol);


/*
Function getEntryLabels-
function returns the A,R,E character value depends if the label is external or not.
*/
char getlabelARE(Label *label);


/*
Function getEntryLabels-
Recursive function on Labellist-(builder)
build a new LabelList that include every label with ".entry" from the complete labellist.
first call will be with list->head as "listlabel" 
*/
void *getEntryLabels(LabelList *newlist,Label *listlabel);



/* 
Function printLabelstoFile-
Recursive function - print Labellist to file given with pointer argument "fp"
first call will be with list->head as "listlabel"
*/
void printLabelstoFile(Label *listlabel,FILE* fp);


/*
Function copyLabel- 
Function create and returns new Label, copy all values from given label "label" except the  pointer "label->next" which sets to NULL.
If cannot copy given Label given as argument -"label" function returns NULL.
*/
Label* copyLabel(Label *label);


/*
Function InsertExtLabel-
Funnction Inserets the Label (with external attribute) given as argument - "extlabel" to the LabelList given as argument - "list".
*/
void InsertExtLabel(LabelList *list,Label *extlabel);