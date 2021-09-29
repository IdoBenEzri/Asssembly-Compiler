#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "HelpTools.h"
#include "SymbolTable.h"
typedef struct BinaryWord BinaryWord;
struct BinaryWord 
{
    char *word;
    char ARE; 

};


typedef struct BinaryLine BinaryLine;
struct BinaryLine 
{
    BinaryWord *first;
    BinaryWord *second;
    BinaryWord *third;
    BinaryLine *next;
    int address;
};


typedef struct BinaryLineList
{
    BinaryLine *head;
} BinaryLineList;


/*
Function createBinWord-(builder)
Function allocate dynamic memory and initialize a Binaryword, Using the String given as argument "word", and the character given as argument "c".
*/
BinaryWord *createBinWord(char*word,char c);


/*
Function addtoBinWord-
Function adds the String given as argument - "str" to the BinaryWord given as argument - "binword".
*/
void addToBinWord(BinaryWord *binword,char*str);


/*
Function printBinWord
Function print the BinaryWord given as argument "binword".
*/
void printBinWord(BinaryWord *binword);


/*
Function removeBinWord-
Free the alocated dynamic memory of BinaryWord given as argument -"bword".
*/
void removeBinWord(BinaryWord*bword);


/*
Function createBinLine-
Function allocate dynamic memory to initialize a BinaryLine - sets all three BinaryWord slots (pointers) to NULL,and the address to the given argument - "address".
*/
BinaryLine *createBinLine(int address);


/*
Function numOfwordsInLine-
Function return the number of BinWord slots that not availible (= number of initialized BinWords) in the BinaryLine given as argument - "line".
*/
int numOfWordsInLine(BinaryLine *line);


/*
Function addWordtoline-
Function adds the BinaryWord given as Argument - "binword" to the BinaryLine "line".
*/
void addWordtoline(BinaryLine *line,BinaryWord *binword);



/*
Function printBinLine- 
prints a Binary line given as argument "line".
*/
void printBinLine(BinaryLine *line);


/*
Function removeBinaryLine-
Remove the BinaryLine given as argument -"line". free the allocated memory.
*/
void removeBinLine(BinaryLine *line);



/*
Function createBinList-
Function allocate dynamic memory to initialize a BinaryLineList - sets the head of the list to NULL.
*/
BinaryLineList *createBinList();
 

/*
Function addLineToList-
Recursive function -  adds the given BinaryLine given as argument "linetoadd",to listLine given as argument "listline".
*/
void addLineToList(BinaryLineList *list,BinaryLine *linetoadd, BinaryLine *listline);


/*
Function printBinList-
Recursive function -  prints a BinaryLine list. - first call to function need to be with list->head as "line". 
*/
void printBinList(BinaryLine *line);


/*
Function RemoveBinList-
Recursive function - remove the Binarylist "line" and free the allocated memory given in createBinList - first call to function need to be with list->head as argument "line". 
*/
void RemoveBinList(BinaryLineList*list, BinaryLine *line);



/*
Recursive function fixBinLine -
Function fill BinaryWords coding to the all the BinaryLines in the LineList given by argument "listline"(recursive) Using the method given as int "method" and A/R/E character given as argument -"ARE" 
and Label address in file given as method "value".
If  Label has external declaration, function add it to the external Labels list given as argument - "extlist".

*/
void fixBinLine(BinaryLine *listline,Label *label, char ARE,int method, LabelList *extlist);


/*
Function printHexList-
Recursive function - given the BinaryLine list with argument "listline",(recursive) function print all the binary line saved during first and second scans in each binary word presented in hexadecimal base.
*/
void printHexList(BinaryLine*listline);


/*
Function printBinListToFile-
Recursive function - same as printHexList but printing to file "fp" given as argument.
*/ 
void printBinListToFile(BinaryLine*listline,FILE *fp);
