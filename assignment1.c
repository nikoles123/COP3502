#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAP 10

//given in prototypes.c
typedef struct Piece Piece;
typedef struct List List;
typedef struct Board Board;

//all structs given in prototypes.c
struct Piece {    
  int rank, file, ind;
};

struct List {
  int identifier; 
  //array of pointers to pieces 
  //allocated based on number of pieces   
  Piece ** arr;    
  int size, cap;
};

struct Board {
  //stores as a pointer to all the ranks/files  
  List ** arr;    
  int size, cap;
};

//function declearations given in prototypes.c
Board * createBoard();
List * createRank(int);
Piece * createPiece(int, int, int);
void destroyBoard(Board *);
void destroyRank(List *);
void destroyPiece(Piece *);
void addPieceToRank(List *, Piece *);
void addRankToBoard(Board *, List *);
void expandRank(List *);
void expandBoard(Board *);
List * findRank(Board *, int);

int main(void) {
  //create memory (2 boards and 1 ARRAY of pieces)
  //one for row, one for column
  Board * rankBoard = createBoard();
  Board * fileBoard = createBoard();

  //n is the number of rooks the user is going to enter
  int n;
  scanf("%d", &n);  

  //(ARRAY can store all pieces in input order)
  Piece ** ARRAY = (Piece**) calloc(n, sizeof(Piece*));

  int rank = 0;
  int file = 0;

  //loop over the pieces
  for(int i = 0; i < n; i++)
  {
    //read in current pieces
    scanf("%d %d", &rank, &file);
 
    //int ind = i + 1;
  
    //this will create the piece
    //this will also populate the ARRAY
    ARRAY[i] = createPiece(rank, file, i);

    //find the rank and file for the piece from the boards
    List * rankList = findRank(rankBoard, rank);
    List * fileList = findRank(fileBoard, file);

    //insert the piece into the rank and file
    addPieceToRank(rankList, ARRAY[i]);
    addPieceToRank(fileList, ARRAY[i]);
  }
  printf("\n");
  //FIND THREATS / PRINT OUT
  //"threat" closest piece in the same row/column
  for(int j = 0; j < n; j++)
  {
    //declaing rank/file
    int rank, file;
    rank = ARRAY[j]->rank;
    file = ARRAY[j]-> file;

    //call findRank function for each index
    List * currRank = findRank(rankBoard, rank);
    List * currFile = findRank(fileBoard, file);

    //set piece * to NULL
    //the values will ONLY change if a threat is found
    Piece * rankBefore = NULL, *rankAfter = NULL, *fileBefore = NULL, *fileAfter = NULL;

    //looping through the rank for each piece in the rank
    for(int k = 0; k < currRank -> size; k++)
    {
      if(currRank -> arr[k] -> file < file && (!fileBefore || fileBefore -> file < currRank -> arr[k] -> file))
      {
        //if threat is found, set that index to fileBefore
        fileBefore = currRank -> arr[k];
      }
      if(currRank -> arr[k] -> file > file && (!fileAfter || fileAfter -> file > currRank -> arr[k] -> file))
      {
        //if threat is found, set that index to fileAfter
        fileAfter = currRank -> arr[k];
      }
    }

    for(int k = 0; k < currFile -> size; k++)
    {
      if(currFile -> arr[k] -> rank < rank && (!rankBefore || rankBefore -> rank < currFile -> arr[k] -> rank))
      {
        //if threat is found, set that index to rankBefore
        rankBefore=currFile->arr[k];
      }
      if(currFile -> arr[k] -> rank > rank && (!rankAfter || rankAfter -> rank > currFile -> arr[k]->rank))
      {
        //if threat is found, set that index to rankAfter
        rankAfter = currFile -> arr[k];
      }
    }

    //check after the loop to see if any of the NULL values changed
    //if they did, there was a threat detected
    int threat = 0;
    if(rankBefore != NULL)
    {
      threat++;
    }
    if(rankAfter != NULL)
    {
      threat++;
    }
    if(fileBefore != NULL)
    {
      threat++;
    }
    if(fileAfter != NULL)
    {
      threat++;
    }

    //print the threat count
    //similar to above, but printing/dereferencing 
    printf("%d ", threat);

    if(rankBefore != NULL)
    {
      printf("%d ", rankBefore->ind+1);
    }
    if(rankAfter != NULL)
    {
      printf("%d ", rankAfter->ind+1);
    }
    if(fileBefore != NULL)
    {
      printf("%d ", fileBefore->ind+1);
    }
    if(fileAfter != NULL)
    {
      printf("%d ", fileAfter->ind+1);
    }
    printf("\n");
  }

  //clean up memory
  destroyBoard(rankBoard);
  destroyBoard(fileBoard);
  free(ARRAY);
 
  return 0;
}

Piece * createPiece(int rank, int file, int i)
{
  //assigning values to the struct
  Piece * currPiece;

  //allocate memory for piece
  currPiece = (Piece *) calloc(1, sizeof(Piece));

  currPiece -> rank = rank;
  currPiece -> file = file;
  currPiece -> ind = i;

  return currPiece;
}

List * createRank(int identifier)
{
  List * currRank;
  //allocate memory for the rank
  currRank = (List *) malloc(sizeof(List));
  //assign value to identifier
  currRank -> identifier = identifier; 

  //since the rank starts out empty, the size is 0
  currRank -> size = 0;
  currRank -> cap = DEFAULT_CAP;

  //allocate memory for the pieces in the rank
  currRank-> arr = (Piece **) calloc(DEFAULT_CAP, sizeof(Piece *));

  return currRank;
}

Board * createBoard()
{
  Board * currBoard;
  //allocate memory for the board
  currBoard = (Board *) calloc(1, sizeof(Board));

  //since theres nothing in the board, the size is zero
  currBoard -> size = 0;
  currBoard -> cap = DEFAULT_CAP;
  //create an array in the currBoard
  currBoard-> arr = (List **) calloc(DEFAULT_CAP, sizeof(List *));

  return currBoard;
}

void destroyBoard(Board * someBoard)
{
  //iterate through the arr that's in someBoard
  //destroy each rank
  for(int i = 0; i < someBoard->size; i++)
  {
    List * currRank = someBoard -> arr[i];
    destroyRank(currRank);
  }
  //free the array
  free(someBoard->arr);
  //free the board
  free(someBoard);
}

void destroyRank(List * someList)
{
  //iterate through the array that's in someList
  //destroy each piece
  for(int i = 0; i< someList-> size; i++)
  {
    Piece * currPiece = someList -> arr[i];
    destroyPiece(currPiece);
  }
  //free the array
  free(someList->arr);
  //free the list
  free(someList);
}

void destroyPiece(Piece * somePiece)
{
  //freeing the memory for piece
  free(somePiece);
}

void addPieceToRank(List * rank, Piece * currPiece)
{
  //check to see if the size is bigger than the cap
  if(rank -> size == rank->cap)
  {
    //if the size is bigger than cap
    //increase the size of the rank
    expandRank(rank);
  }
  //add the rank to the array list in the size - 1 spot
  //(since we did size +1 in the first line of this function)
  rank -> arr[rank -> size] = currPiece; 
  //increase size of the list
  rank -> size++;
}

void addRankToBoard(Board * currBoard, List * rank)
{
  //check to see if the size is bigger than the cap
  if(currBoard->size == currBoard->cap)
  {
    //if the size is biggger than the cap
    //expand the board
    expandBoard(currBoard);
  }
  //add the rank to the array in the size-1 spot 
  //(since we did size + 1 in the first line of this function)
  currBoard -> arr[currBoard -> size] = rank;
  //increase the size of the baord
  currBoard-> size++;
}

void expandRank(List * rank)
{
  //doubling the size of the rank
  int newCap = rank -> cap * 2;
  //allocating more memory for the rank
  rank -> arr = (Piece **) realloc(rank -> arr, newCap * sizeof(Piece *));
  //changing the value of the cap
  rank -> cap = newCap;
}

void expandBoard(Board * currBoard)
{
  //doubling the size of the board
  int newCap = currBoard -> cap * 2;
  //allocating more memory for the board
  currBoard -> arr = (List **) realloc(currBoard -> arr, newCap * sizeof(List *));
  //changing the value of the cap
  currBoard -> cap = newCap;
}

List * findRank(Board * currBoard, int indentifier)
{
  //loop through board w indentifyer
  if(currBoard -> size != 0)
  {
    for(int i = 0; i < currBoard -> size; i++)
    {
      //if it finds identifier
      //return the list
      if(currBoard->arr[i]->identifier == indentifier)
      {
        return currBoard -> arr[i];
      }
    }
  }
  //if size=0 or it doesnt find the indentifier, create a new rank
  List * newRank = createRank(indentifier);

  //call addRankToBoard
  addRankToBoard(currBoard, newRank);
  return newRank;
}
