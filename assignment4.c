#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct person person;
void merge_sort(person ** arr, int size);

//struct will hold name, tokens, bills, and units for each person
struct person{
  char * name;
  long long int tokens;
  long long int bills;
  long long int units;
};

int main() 
{
  //scan in the number of names
  int num;
  scanf("%d", &num);
  long long int tokens;
  long long int bills;
  int i;
  //allocate memory for the array of structs
  person ** allthepeople = malloc(num * sizeof(person *));

  for(i = 0; i < num; i++)
  {
    //allocate memory for one person & their info
    allthepeople[i] = malloc(1 * sizeof(person));
    //allocate memory for the persons name
    char * name = malloc(1 * sizeof(name[21]));
    scanf("%s", name);
    allthepeople[i]->name = name;
    scanf("%lld", &tokens);
    allthepeople[i]->tokens = tokens;
    scanf("%lld", &bills);
    allthepeople[i]->bills = bills;
  }

  //scan in values of tokens and bills
  long long int billRatio;
  long long int tokenRatio;
  scanf("%lld", &billRatio);
  scanf("%lld", &tokenRatio);

  long long int units;
  long long int billUnit;
  long long int tokenUnit;
  //this is going to calculate the value of each persons money
  for(i = 0; i < num; i++)
  {
    billUnit = allthepeople[i]->bills * billRatio;
    tokenUnit = allthepeople[i]->tokens * tokenRatio;
    units = billUnit + tokenUnit;
    //assining the units to the person in each struct
    allthepeople[i]->units = units;
  }

  //sort units
  merge_sort(allthepeople, num);

  //print out the names of sorted units
  for(i = 0; i < num; i++)
  {
    printf("%s\n", allthepeople[i]->name);
  }
  
  //freeing allocated memory
  for(i = 0; i < num; i++)
  {
    free(allthepeople[i]);
  }
  free(allthepeople);

  return 0;
}

//merge sort code for professors lecture
//altered a bit
void merge_sort(person ** arr, int size)
{ 
  //base case
  if(size <= 1)
  {
    return;
  }
  int mid = size/2;
  merge_sort(arr,mid);
  merge_sort(arr + mid, size - mid);

  //merge the array
  person ** temp = calloc(size, sizeof(person*));
  int fptr = 0;
  int bptr = mid;
  for(int i = 0; i < size; i++)
  {
    if(fptr < mid && bptr < size)
    {
      if(arr[fptr]->units > arr[bptr]->units)
      {
        //front has bigger value
        temp[i] = arr[fptr];
        fptr++;
      }
      else
      {
        //back has bigger(or equal) element
        temp[i] = arr[bptr];
        bptr++;
      }
    }
    else if(fptr < mid)
    {
      //front is non-empty, back is not
      temp[i] = arr[fptr];
      fptr++;
    }
    else
    {
      //back is not empty, front is not
      temp[i] = arr[bptr];
      bptr++;
    }
  }
  for(int i = 0; i < size; i++)
  {
    arr[i] = temp[i];
  }
  //freeing allocated memory
  free(temp);
}