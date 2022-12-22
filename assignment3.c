#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this will check to see if the phrase is "pretty"
int isPretty(char ** arr, int n)
{
  int i;
  //looping through the entire phrase
  for(int i = 0; i < n - 1; i++)
  {
    //gets the length of the word
    int length1 = strlen(arr[i]);
    //if the last letter of the first word is different
    //then the first of the seconf
    if(arr[i][length1 - 1] != arr[i + 1][0])
    {
      //exit the "is pretty" function with a false
      //if the phrase is not pretty
      return 0; 
    }
  }
  //exit the is pretty function with a true
  //if the phrase is pretty
  return 1; 
}

//permutation function
int permutation(char ** listWords, char ** perm, int n, int size, int * used)
{
  //base case
  if(n == size)
  {
    //if is pretty returns as a true, print out that permutation
    if(isPretty(perm, size))
    {
      for(int i = 0; i < size; i++)
      {
        printf("%s ", perm[i]);
      }
      printf("\n");
    return 1; //we found the pretty phrase, stop the search
    }
    return 0; //the phrase is not pretty
  }
  //look at every possible spot
  for(int i = 0; i < size; i++)
  {
    //if the value in the input array is unused
    if(used[i] == 0)
    {
      //store it in the permutation array
      perm[n] = listWords[i];
      used[i] = 1; //we now used the value
      if(permutation(listWords, perm, n + 1, size, used))
      {
        return 1;
      }
      //unuse the value
      used[i] = 0;
    }
  }
  return 0;
}
 
int main() 
{
  char ** listWords;  //the original set of words
  int size; //the number of words
  int i;
  //max length 20, add one for '\0'
  char myString[21]; 

  //scanning in the # of words in the phrase
  scanf("%d", &size);
  listWords = (char **)calloc(size, sizeof(char*));

  //this array will be where the permutations go
  char ** perm;
  perm = (char**) calloc(size, sizeof(char*));

  int used[size];
  //populate an empty array of the same size as the above one
  for(i = 0; i < size; i++)
  {
    used[i] = 0;
  }

  //input the words into the array
  for(i = 0; i < size; i++)
  {
    //scanning in words for original phrase
    listWords[i] = (char *) calloc(21, sizeof(char));
    scanf("%s", myString);
    strcpy(listWords[i], myString);
  }

  //call permutations function
  permutation(listWords, perm, 0, size, used);

  //freeing allocated memory
  for(i = 0; i < size; i++)
  {
    free(listWords[i]);
  }

  free(perm);

  free(listWords);

  return 0;
}
