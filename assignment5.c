#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack Stack;
typedef struct Node Node;

struct Stack{
  Node * head;
};
struct Node{
  int money;
  char * name;
  Node * next;
  int mvpValue;
  char * mvpName;
};

// LL operations
Node * createNode(char * name, int money, char * mvpName, int mvpValue);
Node * addToHead(Node * head, char * name, int money, char * mvpName, int mvpValue);
Node * removeHead(Node * head);
void   destroyNode(Node * node);

// Stack operations
void push(Stack * stack, char * name, int money, char * mvpName, int mvpValue);
void pop(Stack * stack);
char * top(Stack * stack);
Stack * createStack();
void destroyStack(Stack * stack);

int main(void) 
{
  //declaring variables
  int number;
  int money;
  char name[21];

  Stack * stack1 = createStack();

  //just for the first time so that we go into the for loop
  number = 1;
  //while the user is not entering 0
  scanf("%d %d %s", &number, &money, name);
  //if the stack is empty, the person automatically becomes the mvp
  if(stack1->head == NULL)
  {
    push(stack1, name, money, name, money);
  }
  while(number != 0)
  {
    //scan in the #
    scanf("%d", &number);
    //if its a one, a new person is entering
    if(stack1->head == NULL)
    {
      //same as above
      push(stack1, name, money, name, money);
    }
    if(number == 1)
    {
      //push to stack
      scanf("%d %s", &money, name);
      //if the new person has more money than the previous person
      //add them to the MVP stack
      if(money > stack1->head->mvpValue)
      {
        push(stack1, name, money, name, money);
        stack1->head->mvpValue = money;
        stack1->head->mvpName = strdup(name);
      }
      //if the person has less money than the mvpValue, push them onto the stack 
      //but do not change the mvp
      if(money < stack1->head->mvpValue)
      {
        push(stack1, name, money, stack1->head->mvpName, stack1->head->mvpValue);
      }
    }
    //if the # is 2, someoene is leaving
    if(number == 2)
    {
      //pop most recent player from stack
      pop(stack1);
    }
    //if the # is 3, print out the MVP
    if(number == 3)
    {
      //print out the player with the most money
      //the player at the top of the stack is the MVP
      printf("%s\n", stack1->head->mvpName);
    }
  }
  //destroy allocated memory
  destroyStack(stack1);
  return 0;
}

// LL operations
Node * createNode(char * name, int money, char * mvpName, int mvpValue) 
{  
  //allocating memory 
  Node * ret = calloc(1, sizeof(Node));
  //since we are adding to the front, the next value is NULL 
  ret->next = NULL;    
  //assigning values to our node
  ret->name = name;
  ret->money = money;
  ret->mvpName = strdup(mvpName);
  ret->mvpValue = mvpValue;    
  return ret;
}
Node * addToHead(Node * head, char * name, int money, char * mvpName, int mvpValue) 
{  
  //adding the node to the head  
  Node * newHead = createNode(name, money, mvpName, mvpValue);    
  newHead->next = head;    
  return newHead;
}
Node * removeHead(Node * head) 
{    
  if (head == NULL)        
    return NULL;    
  Node * newHead = head->next;    
  destroyNode(head);    
  return newHead;
}
// Method to destroy a node
void destroyNode(Node * node) 
{    
  free(node);
}
// Stack operations
// Stack has a head in the struct
// Add a value to the top of the stack
void push(Stack * stack, char * name, int money, char * mvpName, int mvpValue) 
{    
  Node * oldHead = stack->head;    
  Node * newHead = addToHead(oldHead, name, money, mvpName, mvpValue);    
  stack->head = newHead;
}
// Remove the top of the stack
void pop(Stack * stack) 
{  
  Node * oldHead = stack->head; 
  Node * newHead = removeHead(oldHead);
  stack->head = newHead;
}
// Determine the value on the top of the stack
char * top(Stack * stack) 
{    
  Node * head = (*stack).head;    
  if (head == NULL)        
    return "empty";    
  return head->name; 
}

// Function to create a section of memory for the stack
Stack * createStack() 
{    
  Stack * ret = calloc(1, sizeof(Stack));
  ret->head = NULL;    
  return ret;
}

// Function to destroy all the memory left over from the stack
void destroyStack(Stack * stack) 
{    
  // empty the stack first  
  while (strcmp(top(stack), "empty") != 0)       
  pop(stack);    
  // Remove the stack memory    
  free(stack);
}