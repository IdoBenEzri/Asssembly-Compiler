#include "Assembler.h"
#define LABELMAXLENGTH 32
#define LINEMAXLENGTH 80



int isImmediate(char *word)
{
    int src=0;
     if(word[0]=='#')
     {
        removeChar(word,'#');
        src=atoi(word);
        if (src==0)
        { 
            if (isZero(word))
                src=1;
            else    
                printf("Error- expected number after the sign #  .\n" );          
        }
     }   
     return src;                                   
}
int isRelative(char*word)
{
    Label *label;
    int boolean=0;
    if(strlen(word)>1 && word[0]=='%')
    {
        removeChar(word,'%');
        label=createLabel(0,".code",word);
        if(label!=NULL)
        {
            boolean=1;
        } 
        removeLabel(label);
    }
    return boolean;
}
int isRegDirect(char*word)
{
    
    int num=0,i;
    const char *registers[]={"r0","r1","r2","r3","r4","r5","r6","r7"};
     if (strlen(word)>0)
     {
        for(i=0;i<8;i++)
            {
                if(strcmp(registers[i],word)==0)
                    {
                        return i;
                    }
            }            
     }
     return -1;
}
int getTransMethod(char *word)
{
    Label *label;
    int method=-1;
    if(strlen(word)==0 || strcmp(word,"\n")==0)
        return -1;
    if (isImmediate(word)!=0)
        method=0;   
    else if (isRelative(word))    
        method=2;
    else if (isRegDirect(word)>=0)
        method=3;
    else
    { 
        label = createLabel(5,"code",word);
        if(label!=NULL)
            method=1;
        removeLabel(label);  
    }  
    return method;
}
int firstScan(FILE* f,LabelList *list,BinaryLineList *binlist)
{ 
   
    int DC =0, IC=100,labelDec=0,labelEnd,i,wordcounter,index,count,method,errors=0;                   
    char line[LINEMAXLENGTH],*token,*linecpy;  
    char** words;
    Label *label;  
    BinaryLine *binline;
    BinaryWord *binword;
    OprTable *table=malloc(sizeof(OprTable));
    OperatorTable_build(table); 
    linecpy = malloc(sizeof(char)*LINEMAXLENGTH);   
    while(fgets(line,sizeof(line),f)!=NULL)     /*file scan lines Loop*/
    {  
        words = malloc(sizeof(char*)*LINEMAXLENGTH);     
        strcpy(linecpy,line);
        token = strtok(line," ,");       
        for(wordcounter=0; token!=NULL;wordcounter++)
        {      
            words[wordcounter]=(char*)malloc(sizeof(char)*strlen(token)); 
            strcpy(words[wordcounter],token);
            if(words[wordcounter][strlen(words[wordcounter])-1]=='\n')    /*to prevent errors related to white characters at end of line I chose to mark a flag at end of words */
                    words[wordcounter][strlen(words[wordcounter])-1]='\0';    
            token = strtok(NULL, " ,");   
        }
        words[wordcounter]=(char*)malloc(sizeof(char)*1); /*prevent Out of range exception errors in words.*/
        strcpy(words[wordcounter],"\n");
        
        if(strlen(words[wordcounter-1])==0)
            wordcounter--;   
        labelEnd = getLabelEnd(words[0]);    
        if(labelEnd>0)
        {
            labelDec=1;                     /* labelDec used in this program as a flag to label declaration,(and as an index to the next word after label(if exist)*/
            words[0][labelEnd]= '\0';        
        }
        if (strcmp(words[labelDec],".data")==0)     /*First Scenario - Operator in this line is .data - */
        {
          if(labelDec==1)
          {
            label = createLabel(DC,".data",words[0]);
            if(InsertLabel(list,label,list->head)==0)
                    errors++;
          }
           for(i=1;i<=wordcounter;i++)
            {   
                   
                count=atoi(words[labelDec+i]);          /*count initialized to be the number given as operand to .data operator. */                                     
                if(count!=0 )
                {
                    binline=createBinLine(IC+DC); 
                    DC++;     
                    binword=createBinWord(decToBin(atoi(words[labelDec+i]),12),'A');
                    addWordtoline(binline,binword);
                    addLineToList(binlist,binline,binlist->head);
                }        
            }                  
        }
        /*End of .Data scenario. */
        else if (strcmp(words[labelDec],".string")==0)   /*Second Scenario - Operator in this line is .String - */
        {
           if(labelDec==1)
            {
                label = createLabel(DC,".data",words[0]);
                if(InsertLabel(list,label,list->head)==0) 
                    errors++;
                
            }  
            count=CountMarks(linecpy);  
            if(count==2)  
            {
                index=indexOfMarks(linecpy);
                for(i=index+1;linecpy[i]!='"';i++)
                {             
                    binword=createBinWord(decToBin(((int)linecpy[i]),12),'A'); 
                    binline=createBinLine(IC+DC);
                    DC++;
                    addWordtoline(binline,binword);
                    addLineToList(binlist,binline,binlist->head);
                }
                binword=createBinWord(decToBin(0,12),'A');
                binline=createBinLine(IC+DC);
                DC++;
                addWordtoline(binline,binword);
                addLineToList(binlist,binline,binlist->head);
            }
            else  /*number of quote marks in this line is invalid.*/
            {
                printf("Error - Invalid use of \".string\" declaration, line - \"%s\"\n",linecpy);
                errors++;
            }    

        }
        
        /*End of .String scenario. */
        else if(strcmp(words[labelDec],".extern")==0 ||strcmp(words[labelDec],".entry")==0 ) /*Third Scenario - Operator in this line is .extern or .entry- */
        {  
           if(strcmp(words[labelDec],".extern")==0)
           {
                label = createLabel(0,"external",words[labelDec+1]);
                if(InsertLabel(list,label,list->head)==0) 
                    errors++;
           }    
        }
        /*End of .extern/.entry Scenario */


        else   /*Last Scenario - Line is a Command Line.*/
        { 
            if(labelDec==1)        /*label Declaration check*/
            {
                label = createLabel(IC,"code",words[0]);
                if(InsertLabel(list,label,list->head)==0)
                    errors++;  
            }
            if (strlen(words[labelDec])>0 && strcmp(words[labelDec],"\n")!=0 &&(getFunction(table,words[labelDec])==-1 || getOpcode(table,words[labelDec])==-1))  /*Checks if operator is invalid.*/
            {     
                printf("Syntax error - Operator: \"%s\" is not recognized.\n,",words[labelDec]);
                errors++;
            }
            
            else if(labelDec<wordcounter &&(strlen(words[labelDec])>0))    /*Operator is valid case. */
            { 
                
                count=wordcounter-(labelDec+1);   /* count initialized to be the number of operands in this line.*/
                binline=createBinLine(IC);      
                binword=createBinWord(decToBin(getOpcode(table,words[labelDec]),4),'A');
                addToBinWord(binword,decToBin(getFunction(table,words[labelDec]),4));
                addWordtoline(binline,binword);
                if(count==0)  
                {
                    if(transferCheck(table,words[labelDec],0,count,0)>0) 
                        addToBinWord(binline->first,decToBin(0,4));
                    else binline=NULL;    
                }
                for(i=labelDec+1;i<wordcounter && strcmp(words[i],"\n")!=0;i++) /*Loop scanning the operands in this line*/
                {
                    index=i-labelDec;   /** index initialized to be the position of the operand - 1 if its source operand 2 if its target*/
                    method= getTransMethod(words[i]);    
                    if(transferCheck(table,words[labelDec],method,count,index)>0)    /*Operand is valid and match the operator in this line scenario.*/
                    { 
                        if(count==2)  
                            addToBinWord(binline->first,decToBin(method,2));       
                        else if(count==1) 
                            addToBinWord(binline->first,decToBin(0,4));             
                        else                                                        
                            addToBinWord(binline->first,decToBin(method,4));
                       if (method==0)
                        { 
                            binword=createBinWord(decToBin(atoi(words[i]),12),'A');
                            addWordtoline(binline,binword);
                        }
                        else if (method==1||method==2)
                        {
                            binword=createBinWord("?",'?');
                            addWordtoline(binline,binword);    
                        }
                        else if (method==3)
                        {
                          binword=createBinWord(turnOnBit(isRegDirect(words[i])),'A');
                          addWordtoline(binline,binword);
                        }
                    } 
                    else    /*transferCheck failed - invalid operands error scenario. */
                    {      
                            binline=NULL;
                            errors++;
                            break;
                    }
                }
                if(binline==NULL || binline->address==0)      /*Line is valid scenario */
                {
                    printf("error -  operands  given for operator: \"%s\" are invalid\n line: \"%s\"\n",words[labelDec],linecpy); 
                    errors++;    
                }        
                else
                {
                    addLineToList(binlist,binline,binlist->head);
                    IC+=numOfWordsInLine(binline);       
                }                   
            } 
        } /*end of last scenario.*/
        for(i=0;i<wordcounter;i++) /*free allocated dynamic memory allocated before redeclaration in loop.*/
        {
            if(words[i]!=NULL)
                free(words[i]);   
        }
        labelDec=0;
        free(words);       
    }  
    /*End of loop - file scanned completly.*/
    OperatorTable_destroy(table);
    addValueToLabels(list->head,IC,".data"); 
   
    return errors;    
}  





int secondScan(FILE* f,LabelList *list,BinaryLineList *binlist,LabelList *extlist)
{
    int labelDec=0,labelEnd,i,wordcounter,count,method,errors=0;
    char line[LINEMAXLENGTH],*token,*linecpy;  
    char** words;
    Label *label;      
    while(fgets(line,sizeof(line),f)!=NULL)
    {
        words = malloc(sizeof(char*)*LINEMAXLENGTH);     
        strcpy(linecpy,line);
        token = strtok(line," ,");       
        for(wordcounter=0; token!=NULL;wordcounter++)    /*Scanning again the file with scan lines loop   */
        {      
            words[wordcounter]=(char*)malloc(sizeof(char)*strlen(token)); 
            strcpy(words[wordcounter],token);
            if(words[wordcounter][strlen(words[wordcounter])-1]=='\n')     /*to prevent errors related to white characters at end of line I chose to mark a flag at end of words */
                    words[wordcounter][strlen(words[wordcounter])-1]='\0';    
            token = strtok(NULL, " ,");   
        }
        words[wordcounter]=(char*)malloc(sizeof(char)*1);
        strcpy(words[wordcounter],"\n");                                   /*prevent Out of range exception errors in words.*/
        labelEnd=getLabelEnd(words[0]);   
        if(labelEnd>0)
        {
            labelDec=1;
            words[0][labelEnd]= '\0';         
        }  
        if((strcmp(words[labelDec],".data")==0 ||strcmp(words[labelDec],".string")==0||strcmp(words[labelDec],".extern")==0)) /*data/string/extern operators in this line- ignore it.*/  
            {
                labelDec=0;
                continue;
            }    
        else if(strcmp(words[labelDec],".entry")==0) 
        {
            count=addAttributeToLabel(list->head,".entry",words[labelDec+1],0);
            if(count==0) /* symbol not in the label list.*/ 
            {
                printf("Error- cannot recognize label after \".entry\" declaration.");
                errors++; 
            }       
        }
        else
        /*Last Scenario - Line is a Command Line.*/
        {
            
            for(i=labelDec+1;i<wordcounter && strcmp(words[i],"\n")!=0;i++)   /*scanning operands in line.*/
                {
                    method= getTransMethod(words[i]);
                    if (method==1||method==2) /*there are labels in this line.*/
                    { 
                        label=getLabel(list->head,words[i]);
                        if(label==NULL)     /* Label not in the LabelList.*/ 
                        {
                            printf("Error- cannot recognizee label - \"%s\"\n",words[i]);
                            errors++;
                        }   
                        else 
                        
                        fixBinLine(binlist->head,label,getlabelARE(label),method,extlist);    /* label is in the  label list case*/         
                    }
                }
        }/*end of Last scenario*/  
       labelDec=0; 
    }
    /*File scanned completly 2 times  */    
   return errors;
}

void createOutPut(char*namecpy,LabelList *list,BinaryLineList *binlist,LabelList *extlist)
    {
        FILE *fp;
        LabelList *entlist;
        char *filename=malloc(sizeof(char)*(strlen(namecpy)+3));
        printList(list->head);
        strcpy(filename,namecpy);
        strcat(filename,".ob");
        fp = fopen(filename, "w");
        printBinListToFile(binlist->head,fp);
        fclose(fp);
        strcpy(filename,namecpy);
        strcat(filename,".ent");
        entlist =createList();
        getEntryLabels(entlist,list->head);
        fp = fopen(filename, "w");  
        printLabelstoFile(entlist->head,fp);
        fclose(fp);
        strcpy(filename,namecpy);
        strcat(filename,".ext");
        fp = fopen(filename, "w");
        printLabelstoFile(extlist->head,fp);
        fclose(fp);
        free(filename);
         if(entlist!=NULL)    
                RemoveList(entlist,entlist->head);
    }
int main(int argc,char* argv[])
{
    FILE *f;
    int errors=0,i;
    char*filename,*namecpy;
    LabelList *list = createList(),*entlist,*extlist=createList();
    BinaryLineList *binlist=createBinList();
    for(i=1;i<argc;i++)/*Loop scan over the files given as command line aruments "argv" */
    {
        filename=malloc(sizeof(char)*(strlen(argv[i])+3));
        namecpy=malloc(sizeof(char)*(strlen(argv[i])+3));
        strcpy(filename,argv[i]);
        strcpy(namecpy,filename);
        strcat(filename,".as");
        f= fopen(filename,"r");
        printf("%s\n", filename);
        if(f==NULL)
            printf("cannot open file\n");
        else
        {    
            errors=firstScan(f,list,binlist);
            if(errors>0)  
            {
                free(filename);
                errors=0;
                continue;     
            }
            
            fclose(f);
            f = fopen(filename, "r");
            errors=secondScan(f,list,binlist,extlist);
            if(errors>0)  
            {
                free(filename);
                errors=0;
                continue;
            }
            else createOutPut(namecpy,list,binlist,extlist);
            fclose(f);
            free(filename);
            free(namecpy);
         
            if(binlist)
                RemoveBinList(binlist,binlist->head);
            if(list)    
                RemoveList(list,list->head);
           
            if(extlist)    
                RemoveList(extlist,extlist->head);
                 
        }
         
    }
    printf("ok");

}    