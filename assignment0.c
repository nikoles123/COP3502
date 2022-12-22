#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100000

int main(void) 
{
  char myString[100000];
  char garbage;
  // Read in the integer on the first line    
  int n;   
  scanf("%d", &n); 

  //get rid of first newline character
  scanf("%c",&garbage);
  while(garbage != '\n')
  {
    scanf("%c", &garbage);
  }   
 
  //this loop is going to take in as many names as we entered for n
  for(int i=0; i<n; i++)   
  {
    //scanning in string
    fgets(myString, MAX, stdin); 
    int length = strlen(myString);
    //this prints out the first letter of the string 
    printf("%c", myString[0]);
    //this is going to look through the string
    for(int j=0; j<length; j++)
    {
      //if theres a space, print what is before/after it
      if(myString[j] == ' ')
      {
        printf("%c%c", myString[j-1], myString[j+1]);
      }
      //if there is a \n character, print what was before the newline
      //printing out the last character in the string
      if(myString[j] == '\n')
      {
        printf("%c\n", myString[j-1]);
      }
    }
  }   
  return 0;
}