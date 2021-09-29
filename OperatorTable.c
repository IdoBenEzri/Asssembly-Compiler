#include "OperatorTable.h"
#include <stdio.h>
#include <string.h>
void OperatorTable_build(OprTable *table)
{ 
    int i;
    const int  functions[SIZEOFTABLE] = {0,0,10,11,0,10,11,12,13,10,11,12,0,0,0,0};
    const int opcodes[SIZEOFTABLE] =  {0,1,2,2,4,5,5,5,5,9,9,9,12,13,14,15};
    const char *operators[SIZEOFTABLE] = {"mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","jsr","red","prn","rts","stop"};
     
   for(i =0; i<16; i++)
   {
       table->function[i] = functions[i];
       table->opcode[i] = opcodes[i]; 
       table->operators[i] = (char*)malloc(sizeof(char)*strlen(operators[i]));
       strcpy(table->operators[i], operators[i]);
   }
}
int getOpcode(OprTable *table, char* word)
{
    
    int i;
    for(i=0;i<16;i++)   
    {
        if (strcmp(table->operators[i],word)==0)
            return table->opcode[i];    
    }        
    return -1;
}
int getFunction(OprTable *table, char* word)
{   
    int i;
    for(i=0;i<16;i++)   
    {
        if (strcmp(table->operators[i],word)==0)
            return table->function[i];    
    }        
    return -1
    ;
}
void OperatorTable_destroy(OprTable *table)
{   
    int i;
        for(i=0;i<16;i++) 
            free(&(table->operators[i]));           
}
int transferCheck(OprTable *table ,char*operator,int method,int count,int position)
{

    const int source[5][3]={{0,1,3},{0,1,3},{0,1,3},{0,1,3},{1,1,1}};    /*both source and target arrays initialized with the legal methods for each function, order by same order as operator table function*/
    const int target[14][3]={{1,3},{0,1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,2},{1,2},{1,2},{1,3},{0,1,3}};
    int boolean=0,i,j;
    if(count>2||count<0 )     /* Invalid number of operands.*/
        return boolean;
    for(i=0;i<SIZEOFTABLE;i++)
    {
        if(strcmp(operator,table->operators[i])==0)
            break;
    }
    if (count==0)/*Zero operands scenario*/
    {
        if (i==14 || i==15)/*Only operators that located at the operator table in lines 14-15 have no operands.*/
                boolean=1;               
    }        
    else if (count==1)    /*One operand scenario*/
    {  
        if(4<i && i<14)    /*Only operators that located at the operator table in lines 0-13 can have 1 operand.*/
        {
            for(j=0;j<3;j++) 
            {
                if (target[i][j]==method)
                    boolean=1;
            }
        }                         
    }
    else if (count==2)   /*Two operands scenario-Source Operator scenario*/
    {
        if(i<=4)    /*Only operators that located at the operator table in lines 0-5 can have 2 operands.*/
        {
                for(j=0;j<3;j++) 
                {
                    if ((position==1 && source[i][j]==method)||(position==2 &&target[i][j]==method))
                    boolean=1; 
                }                 
        }   
    }
return boolean; 
}
