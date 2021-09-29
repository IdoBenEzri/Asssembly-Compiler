
 
#include "HelpTools.h"    

char* decToBin(int n, int bits)
{  
    int i,k;
    char number[32]= "";    
    char *num=(char*)malloc(sizeof(char)*33);

    for(i=bits-1;i>=0;i--)    
    {     
        k = n >> i;

        if (k & 1)
            strcat(number,"1");
         else
            strcat(number,"0");  
    }
    strcpy(num,number);
    return num;
}
int binToHex(char*bin)
{
char *a = bin;
int num = 0;
do {
    int b = *a=='1'?1:0;
    num = (num<<1)|b;
    a++;
} while (*a);
return num;    
}
int isZero(char*word)
{
    int len;
    int i;
    len=strlen(word);
    for (i=0;i<len;i++)
    {
        if(!(word[i]== '0'))
            return (0);
    }        
    return 1;       
}

int indexOfMarks(char*source)
{                                         
    char * found = strstr(source, "\""); 
    if (found != NULL)                                             
        return (found - source);
    return -1;
}
int CountMarks(char*source)
{ 
    int i, count=0,len;
    len=strlen(source);
    for(i=0;i<len;i++)
    {
        if(source[i] == '"')
            count++;
    }
    return count;
}
void removeChar(char *str, char garbage) 
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) 
    {
        *dst = *src;
        if(*dst != garbage) 
            dst++;
    }
    *dst = '\0';
}
char* turnOnBit(int bit)
{  
    char* str = decToBin(0,12);
    if(bit<8 && bit >=0)
    {
        str[12-(bit+1)]='1';
        return str;
    }    
    else 
    free(str);    
    return NULL;               
}
int isSubstring(char * str, char* search)
{
    int count1 = 0, count2 = 0, i, j, flag;
    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    return flag;
}


int getLabelEnd(char *word)
{   
    int len;  
    len=strlen(word);
        if (len==0 || strcmp(word,"\n")==0)
            return -1; 
        if(word[(len-1)]== ':')
            return (len-1);

    return -1;       
}
