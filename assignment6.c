#include <stdio.h>
#include <stdlib.h>

int currPos;
int back;
int excitement; 
int victor;
int nullCount;

typedef struct Node Node;
typedef struct Node{
  int data;
  struct Node * left;
  struct Node * right;
  int rightPlayer;
  int leftPlayer;
  int victor;
}Node;

void freeTreePostOrder(Node * root);
Node * addNode(Node * root, int value);
void postOrder(Node * root);
void insertPlayers(Node * tree, int skillLevel[], int n);
int calculateVictor(Node * tree);

int main ()
{
  //first line is the # of players
  int n;
  scanf("%d", &n);
  if(n == 0 || n == 1)
  {
    printf("0\n");
    return 0;
  }
  int i;
  int tableNum[n-1];
  Node * tree = NULL;
  //setting global variables
  currPos = 0;
  back = n - 1;
  excitement = 0;
  victor = 0;
  nullCount = 0;
  //scan in the table numbers
  for(i = 0; i < n - 1; i++)
  {
    //for loop that gets the players - 1 for table order
    //keep table order
    scanf("%d", &tableNum[i]);
  }
  //post order traversal for the tree with the values from above
  //this will add in the table numbers into a tree 
  for(i = n - 2; i >= 0 ; i--)
  {
    tree = addNode(tree, tableNum[i]);
  }
  //scan in the skill levels
  int skillLevel[n];
  for(i = 0; i < n; i++)
  {
    scanf("%d", &skillLevel[i]);
  }
  //insert the skill levels to the tables
  insertPlayers(tree, skillLevel, n);
  //find the victors and excitement
  postOrder(tree);
  //print out the excitement 
  printf("%d\n", excitement);
  //free memory
  freeTreePostOrder(tree);
  return 0;
}

// this will calculate the excitment/victor of each node
void postOrder(Node * tree) 
{ 
  int rightVictor;
  int leftVictor;
  if (tree == NULL)  
  {   
    nullCount++;   
    return;   
  }   
  postOrder(tree->left);        
  postOrder(tree->right);      
  //calculate the victor and excitment
  if(tree->left == NULL && tree->right == NULL)
  {
    //if the node has no kids
    //check to see which player will be the victor
    if(tree->leftPlayer < tree->rightPlayer)
    {
      victor = tree->rightPlayer;
      excitement = excitement + tree->rightPlayer - tree->leftPlayer;
      //this will be helpful when we recurse through the tree
      tree->victor = victor;
    }
    if(tree->leftPlayer > tree->rightPlayer)
    {
      victor = tree->leftPlayer;
      excitement = excitement + tree->leftPlayer - tree->rightPlayer;
      tree->victor = victor;
    }
  }
  else if(tree->left == NULL && tree->right != NULL)
  {
    //if the table only has a right player
    if(victor > tree->leftPlayer)
    {
      excitement = excitement + (victor - tree->leftPlayer);
      tree->victor = victor;
    }
    if(victor < tree->leftPlayer)
    {
      excitement = excitement + (tree->leftPlayer - victor);
      victor = tree->leftPlayer;
      tree->victor = victor;
    }
  }
  else if(tree->right == NULL && tree->left != NULL)
  {
    //if the table only has a left player
    if(victor > tree->rightPlayer)
    {
      excitement = excitement + (victor - tree->rightPlayer);
      tree->victor = victor;
    }
    if(victor < tree->rightPlayer)
    {
      excitement = excitement + (tree->rightPlayer - victor);
      victor = tree->rightPlayer;
      tree->victor = victor;
    }
  }
  else
  {
    //calculate the right roots victor
    rightVictor = tree->right->victor;
    //calculate the left roots victor
    leftVictor = tree->left->victor;
    //calculate the actual victor
    if(rightVictor > leftVictor)
    {
      excitement = excitement + (rightVictor - leftVictor);
      tree->victor = rightVictor;
    }
    if(rightVictor < leftVictor)
    {
      excitement = excitement + (leftVictor - rightVictor);
      tree->victor = leftVictor;
    }
  }
  // beginning the process of moving up
}

void insertPlayers(Node * tree, int skillLevel[], int n)
{
  if(tree == NULL)
  {
    return;
  }
  if(tree->left == NULL && tree->right != NULL)
  {
     //if only left = NULL, add skill from front of arrayList
    tree -> leftPlayer = skillLevel[currPos];
    //printf("%d's skill level is %d\n", tree->data, tree->leftPlayer);
    currPos++;
    //printf("%d's skill level is %d\n", tree->data, tree -> skillLevel);
  }
  if(tree->left != NULL && tree->right == NULL)
  {
    //if only right = NULL, add skill from back of the arrayList
    tree -> rightPlayer = skillLevel[back];
    //printf("%d's skill level is %d\n", tree->data, tree->rightPlayer);
    back--;
    //printf("%d's skill level is %d\n", tree->data, tree -> skillLevel);
  }
  if(tree->left == NULL && tree->right == NULL)
  {
    //if they are both NULL, add 2 skills from front
    tree->rightPlayer = skillLevel[currPos];
    tree->leftPlayer = skillLevel[currPos + 1];
    currPos = currPos + 2;
    //printf("%d's skill levels are %d and %d\n", tree->data, tree->rightPlayer, tree->leftPlayer);
  }
  insertPlayers(tree->left, skillLevel, n);
  insertPlayers(tree->right, skillLevel, n);
}

Node * addNode(Node * tree, int value)
{
  //base case
  //checks if the tree is empty
  if(tree == NULL)
  {
    //create a new node
    Node * newNode = calloc(1, sizeof(Node));
    newNode -> data = value;
    newNode -> left = NULL;
    newNode -> right = NULL;

    return newNode;
  }
  if(value < tree -> data)
  {
    //we have to go left
    tree -> left = addNode(tree -> left, value); //we want new node to be the left child of the current node
  }
  else if(value > tree -> data)
  {
    //we have to go right
    tree -> right = addNode(tree -> right, value);
  }
  return tree;
}

void freeTreePostOrder(Node * root)
{
  //empty tree or if there is a node w no children
  if(root == NULL)
  {
    return;
  }
  //left recusive step
  freeTreePostOrder(root->left);
  //right recursive step
  freeTreePostOrder(root->right);
  free(root); //accessed the root last
}
