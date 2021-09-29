#define BINWORDSIZE 12
#include "MachineCoder.h"

BinaryWord *createBinWord(char*word, char c)
{ 
       BinaryWord *binword=malloc(sizeof(BinaryWord));
       binword->word = malloc(sizeof(char)*BINWORDSIZE);
       strcpy(binword->word,word);
       binword->ARE=c;
       return binword;
}

void addToBinWord(BinaryWord *binword,char*str)
{
    if(binword==NULL)
        return;
    if (strlen(binword->word)+strlen(str)<=BINWORDSIZE)
        strcat(binword->word,str);    
}

void printBinWord(BinaryWord*bword)
{   
    if(bword==NULL)
        return;
    else printf("%s\t%c\n",bword->word,bword->ARE);    
}

void removeBinWord(BinaryWord*bword)
{
    if(bword==NULL)
        return;
    free(bword->word);
    free(bword);
    bword=NULL;      
}

BinaryLine *createBinLine(int address)
{
  
    BinaryLine *line = malloc(sizeof(BinaryLine));
    line->first=NULL;
    line->second=NULL;
    line->third=NULL;
    line->address =address;
    line->next=NULL;
    return line;
}

void addWordtoline(BinaryLine *line,BinaryWord *binword)
{
    if(line && binword)
    {
        if(line->first==NULL)
             line->first=binword;    
        else if (line->second==NULL)
            line->second=binword;   
        else if(line->third==NULL)
            line->third=binword;      
    }
}

void printBinLine(BinaryLine *line)
{
    if(line==NULL)
        return;
    printf("address:%d\n",line->address);  
        printBinWord(line->first); 
        printBinWord(line->second);  
        printBinWord(line->third);          
}

void removeBinLine(BinaryLine *line)
{
    if(line==NULL)
        return;   
    removeBinWord(line->first);
    removeBinWord(line->second);
    removeBinWord(line->third);
    free(line); 
    line=NULL;       
}

BinaryLineList *createBinList() 
{
    BinaryLineList *list = malloc(sizeof(BinaryLineList));
    list->head = NULL;
    return list;
}

void addLineToList(BinaryLineList *list,BinaryLine *linetoadd, BinaryLine *listline)
{
    if(linetoadd->address==0)
        return;
   if(list->head==NULL)

        list->head=linetoadd;
    else if(listline->next==NULL)
        listline->next=linetoadd;         
    else addLineToList(list,linetoadd,listline->next); 
}

void printBinList(BinaryLine *line)
{
    
    if(line==NULL || line->address==0)    
            return;  
    if(line->next==NULL)
        {
            printBinLine(line);      
            return;  
        }
   printBinLine(line);
   printBinList(line->next);            
}
int numOfWordsInLine(BinaryLine *line)
{
    int num=0;
    if(line)
    {
        if(line->first)
            num++;
        if(line->second)
            num++;
        if(line->third)
            num++;                  
    }
    return num;
}

void RemoveBinList(BinaryLineList*list, BinaryLine *line)
{ 
    BinaryLine *cpy;
   if(line==NULL || line->address==0)
   { 
        free(list);   
        return;
   }          
    cpy=line->next;
    removeBinLine(line);
    RemoveBinList(list,cpy);
    
}


void fixBinLine(BinaryLine *listline,Label *label, char ARE,int method, LabelList *extlist)
{
    Label *extlabel;
    BinaryWord *binword;
   
    if(listline==NULL)
        return;
           
    if(method==1)
    { 
        binword=createBinWord(decToBin(label->value,12),ARE); 
    }
    if(method==2)
    {
       binword=createBinWord(decToBin((label->value)-(listline->address+1),12),'A'); 
    }   
    if(listline->second!=NULL &&strcmp(listline->second->word,"?")==0)
    {   
        removeBinWord(listline->second);
        listline->second=binword;
         if(label->value==0)
            {
                extlabel=createLabel(listline->address+1,"external",label->symbol);
                InsertExtLabel(extlist,extlabel);
            } 
        
    }
    else if(listline->third!=NULL&&strcmp(listline->third->word,"?")==0)
    {
        removeBinWord(listline->third);
        listline->third=binword;
        if(label->value==0)
            {
                extlabel=createLabel(listline->address+2,"external",label->symbol);
                InsertExtLabel(extlist,extlabel);
            }  
    }
    else 
    {
        removeBinWord(binword);
        fixBinLine(listline->next,label,ARE,method,extlist);
    }
}


void printHexList(BinaryLine*listline)
{
    BinaryWord *binword;
    if(listline==NULL)
        return;
    printf("\t%04d\t%03X\t%c\n",listline->address,binToHex(listline->first->word),listline->first->ARE); 
    if(listline->second!=NULL)
    {
       printf("\t%04d\t%03X\t%c\n",listline->address+1,binToHex(listline->second->word),listline->second->ARE);   
    }
    if(listline->third!=NULL)
    {
       printf("\t%04d\t%03X\t%c\n",listline->address+2,binToHex(listline->third->word),listline->third->ARE);
    }
    printHexList(listline->next);
}
void printBinListToFile(BinaryLine*listline,FILE *fp)
{
    BinaryWord *binword;
    if(listline==NULL)
        return;
    fprintf(fp,"\t%04d\t%03X\t%c\n",listline->address,binToHex(listline->first->word),listline->first->ARE); 
    if(listline->second!=NULL)
    {
       fprintf(fp,"\t%04d\t%03X\t%c\n",listline->address+1,binToHex(listline->second->word),listline->second->ARE);   
    }
    if(listline->third!=NULL)
    {
       fprintf(fp,"\t%04d\t%03X\t%c\n",listline->address+2,binToHex(listline->third->word),listline->third->ARE);
    }
    
    printBinListToFile(listline->next,fp);
}