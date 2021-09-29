
#define OPERATORTABLE_H 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZEOFTABLE 16
struct OperatorTable
{
    int function[SIZEOFTABLE];
    int opcode[SIZEOFTABLE]; 
    char *operators[SIZEOFTABLE]; 
};
typedef struct OperatorTable OprTable;


/*
Function Operator_build-
function allocate dynamic memory to the table and  initialize all the values needed in the operators table.
*/
void OperatorTable_build(OprTable *table);


/*
Function_OperatorTable_destroy
function remove the table and free the allocated memory given with OperatorTable_builld
*/
void OperatorTable_destroy(OprTable *table);



/*
Function getOpcode-
Given Operator table "table" and char pointer "word" (that present operator name) as arguments - function return the opcode number (in decimal form) that used to present the operator in binary code
If the given operator cannot be found in the operator table, function return -1.
*/
int getOpcode(OprTable *table, char* word);
 

/*
Function getFunction-
Given Operator table "table" and char pointer "word" (that present operator name) as arguments - function return the function number (in decimal form) that used to present the operator in binary code
If the given operator cannot be found in the operator table, function return -1.
*/ 
int getFunction(OprTable *table, char* word);


/*
Function transferCheck
 function check if given Operator "operator" can match with given transfer method "method" of operand. To do so the function using the Operator table "table",
 int count that presend the number of operands in current line and int position that present the position of current operand in the line (source/target).
 returns 1 if the match is valid.   
*/ 
int transferCheck(OprTable *table ,char*operator,int method,int count,int position);
