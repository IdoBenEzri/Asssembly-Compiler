#include<stdio.h>
#include<stdlib.h>
#include <string.h>
/*
Function getLabelEnd- 
Function check if the String given as argument "word" ends with the character -':' if it does - returns the index of the character, otherwise returns -1 
*/
int getLabelEnd(char *word);

/*
Function decToBin
Function return string that sets to be the binaryValue of given int argument - "n",
the nubmer of bits to use in the presentation is determine by the given number "bits" (can be maximum 32 - if given  more then the first 32 bits will be presented in the returned string.) 
*/
char* decToBin(int n,int bits);



/*
Function isZero-
Function checks if the given string "word" is presentation of the number Zero, returns boolean value to present the value(int initialized to 1 or 0).  
*/
int isZero(char*word);



/*
Function removeChar-
Function remove any appearance of the character "garbage" in the string "str".
*/
void removeChar(char *str, char garbage); 


/*
Function indexOfMarks-
return the int of the first appearance of  quote marks in the given string, if cannot be found - returns -1.
*/
int indexOfMarks(char*source);




/*
Function countMarks-
returns the number of quote marks appearances in the given string.
*/
int CountMarks(char*source);



/*
Function turnOnBit-
returns a 12 character string presenting a register, all character sets to zero exept the one in the given "bit"position.
*/
char* turnOnBit(int bit);



/*
Function binToHex-
convert binary nubmer presented in a string (given as argument) to int.
*/
int binToHex(char*bin);
