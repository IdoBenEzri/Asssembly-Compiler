
#include "SymbolTable.h"

Label *createLabel(int val, char* att,char*symbol)
{
    int i;
    const char *forbiddens[] = {"r0","r1","r2","r3","r4","r5","r6","r7","mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","jsr","red","prn","rts","stop",":"};
    Label *newLabel = malloc(sizeof(Label));
    newLabel->symbol = (char*)malloc(sizeof(char)*strlen(symbol));
    newLabel->attribute = (char*)malloc(sizeof(char)*strlen(att));
    if(strlen(symbol)==0)
        return NULL;
    if(strlen(symbol)>maxLength)
    {
        printf("Label is invalid- Label \"%s\" ,have too many characters in name.\n", symbol);
        removeLabel(newLabel);
        return NULL;
    }
    if(atoi(symbol)!=0 || isZero(symbol)==1)/*Numbers cannot be label names.*/
    {
        printf("Label is invalid - \"%s\" have invalid name.\n", symbol);
        removeLabel(newLabel);
        return NULL;
    }    
    else
    {         
        for(i=0;i<sizeof(forbiddens)/sizeof(char*);i++)
        {
            if(strcmp(symbol,forbiddens[i])==0)
            {
            printf("Label is invalid - \"%s\" have invalid name.\n", symbol);
            removeLabel(newLabel);
            return NULL;
            }
        } 
        strcpy(newLabel->symbol,symbol);
        strcpy(newLabel->attribute,att);
        newLabel->value = val;   
        newLabel->next = NULL;
        return newLabel;
    }
}

void removeLabel(Label *label)
{
    if(label)
    {
        free(label->attribute);
        free (label->symbol);
        free (label);
        label=NULL;
    }
}
int InsertLabel(LabelList *list,Label *nlabel,Label *listLabel)
{
    if (nlabel==NULL)
        {
            return 0;
        }    
    if(list->head==NULL)
    {
        list->head=nlabel;
        return 1;
    }    
    if(listLabel->next==NULL)
    {
        listLabel->next=nlabel;
        return 1;  
    }
    if (strcmp(listLabel->symbol,nlabel->symbol)==0)
    {
        printf("label declaration is illegal - label %s is already declared.\n",nlabel->symbol);
        return 0;
    }    
    else return InsertLabel(list,nlabel,listLabel->next); 
}

void RemoveList(LabelList *list, Label *label)
{
    if (label!=NULL)
        RemoveList(list,label->next);
    removeLabel(label); 
    if (list->head == NULL)
        free(list);
}

LabelList *createList() 
{
    LabelList *list = malloc(sizeof(LabelList));
    list->head = NULL;
    return list;
}
void printList(Label *label)
{
    if(label!=NULL)
    {
        printf("symbol - %s\tvalue - %d\tattribute -%s\n",label->symbol,label->value,label->attribute);
        printList(label->next);
    }
}
void addValueToLabels(Label *label,int toadd,char * attribute)
{
    if(label==NULL)
        return;
    if (strcmp(label->attribute,attribute)==0)
        label->value+=toadd;
    addValueToLabels(label->next,toadd,attribute);    
}
int addAttributeToLabel(Label *label,char*toadd, char* symbol,int count)
{
    char*temp;
    if(label==NULL)
        return count;            
    if(strcmp(label->symbol,symbol)==0)
    {   
        temp=malloc(sizeof(char)*(strlen(toadd)+strlen(label->attribute)));
        strcpy(temp,label->attribute);
        strcat(temp,toadd);
        free(label->attribute);
        label->attribute=temp; 
        count++;        
    }
     return addAttributeToLabel(label->next,toadd,symbol,count);
}
Label * getLabel(Label *listlabel,char*symbol)
{
    if(listlabel==NULL)
        return NULL;
    if(strcmp(listlabel->symbol,symbol)==0)
        return listlabel;        
    return getLabel(listlabel->next,symbol);
}
char getlabelARE(Label *label)
{
    if(strcmp(label->attribute,"external")==0)
        return 'E';
    return 'R';    
}


Label* copyLabel(Label *label)
{
    
    if(label!=NULL)
    {
        Label *cpy=createLabel(label->value,label->attribute,label->symbol);
        return cpy;
    }
    return NULL;
}


void *getEntryLabels(LabelList *newlist,Label *listlabel)
{
    Label*temp;
    if(listlabel==NULL)
        return;
     
    if(strstr(listlabel->attribute,".entry")!=NULL)
        {
            temp=copyLabel(listlabel);
            InsertLabel(newlist,temp,newlist->head);
        }
    getEntryLabels(newlist,listlabel->next);   
}
void printLabelstoFile(Label *listlabel,FILE* fp)
{
    if (listlabel==NULL)
        return;
    fprintf(fp,"%04d\t%s\n",listlabel->value,listlabel->symbol);
    printLabelstoFile(listlabel->next,fp);   
}


void InsertExtLabel(LabelList *list,Label *nlabel)
{
    if (nlabel==NULL)
            return;  
    if(list->head==NULL)
    {
        list->head=nlabel;
        return;
    }        
    nlabel->next=list->head;
    list->head=nlabel;
}       