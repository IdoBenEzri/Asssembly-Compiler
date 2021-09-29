#include <stdio.h>
#include <stdlib.h>
#include "OperatorTable.h"
#include "MachineCoder.h"



/*
Function firstScan-
Function get Assembly file pointer as argument - "f", empty LabelList  "list" and empty BinaryLineList "binlist", Function firstScan commit the first scan as described in project algorithm, 
returns int "errors" that present the number of errors occurred durring this file scan.
Function -Initialize both binary list and label list based on the given assembly file.
*/
int firstScan(FILE* f,LabelList *list,BinaryLineList *binlist);


/*
Function seconScan-
Function get Assembly file pointer as argument - "f", Labellist pointer "list" and BinaryLineList pointer "binlist" - after firstScan changes , Function secondScan commit the second scan as described in project algorithm,
returns int errors that present the nubmer of errors occurred
 durring this file scan.
fills the binarylines missing lines if there any. 
*/
int secondScan(FILE* f,LabelList *list,BinaryLineList *binlist,LabelList *extlist);





/*
Function isImmediate-
Function check if the Operand given as argument - "word", need to be transfered with immediate method. returns boolean value (int initialized to 1 or 0)
Note- If the operand need to be transfered with Immediate method, first character in word is "#",function will remove the first character in this case to help the assembler in other processes later.
*/
int isImmediate(char *word);

/*Given string "word"  that present assembly commands line  operand as argument - Function check if the operand need to be transfered with relative method. returns int boolean value to present the answer (initialized to 1 or 0)
Note- If the operand need to be transfered with relative method, first character in word is "%",function will remove the first character in this case.
*/
int isRelative(char*word);

/*
Function isRegDirect-
Given string "word"  that present assembly commands line  operand as argument - Function check if the operand is a name of a register, if it does, returns the number of register, if not returns -1.
*/
int isRegDirect(char*word);
/*
   Given string "word" that present assembly commands line operand as argument - Function checks the transfer method that suit for the operand and return the number that present the method. 
   If there is no transfer method that match the given operand, function return -1.
*/
int getTransMethod(char *word);

void createOutPut(char*namecpy,LabelList *list,BinaryLineList *binlist,LabelList *extlist);