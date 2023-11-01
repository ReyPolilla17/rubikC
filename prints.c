#include "cube.h"
// used for the printing of the cube, I use # because it's easier to undestand
void color(int value)
{
  switch(value)
  {
    // red
    case 2:
    {
      printf("\x1b[31m#\x1b[0m");
      break;
    }
    // blue
    case 3:
    {
      printf("\x1b[1m\x1b[34m#\x1b[0m");
      break;
    }
    // magenta
    case 4:
    {
      printf("\x1b[1m\x1b[35m#\x1b[0m");
      break;
    }
    // Green
    case 5:
    {
      printf("\x1b[1m\x1b[32m#\x1b[0m");
      break;
    }
    // Yellow
    case 6:
    {
      printf("\x1b[1m\x1b[33m#\x1b[0m");
      break;
    }
    // white
    default:
    {
      printf("\x1b[1m#\x1b[0m");
      break;
    }
  }
  return;
}

// prints the cube in a specific order
void printC(int arr[][3][3])
{
  int i = 0;
  int j = 0;
  int k = 0;

  // first the upper face
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      color(arr[0][i][j]);
    }
    printf("\n");
  }

  // then the lateral faces
  for(i = 0; i < 3; i++)
  {
    for(j = 1; j < 5; j++)
    {
      for(k = 0; k < 3; k++)
      {
        color(arr[j][i][k]);
      }
      printf(" ");
    }
    printf("\n");
  }

  // and the bottom face
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      color(arr[5][i][j]);
    }
    printf("\n");
  }

    return;
}

// prints all the movements that have been made
void printM(int *size)
{
  // The size of the array is always the amount of movements made by 3, so the lenght of the file always fits on the array
  char moves[*size * 3];

  FILE *movesFile;

  if(*size == 0)
  {
    return;
  }

  movesFile = fopen("moves.txt", "r");
  fscanf(movesFile, "%[^\3]", moves);
  fclose(movesFile);

  printf("%s\n", moves);

  return;
}

// adds an instruction to the file
void addM(int *size, char a[])
{
  // moves is the rougth file and move is every instruction separated stored in arrays
  char moves[*size * 3];
  char move[*size][3];

  // counters
  int i = 0;
  int j = 0;
  int k = 0;

  // the file
  FILE *movesFile;

  movesFile = fopen("moves.txt", "a");
  fprintf(movesFile, "%s ", a);
  fclose(movesFile);

  // adds 1 to size
  *size += 1;

  // reads the file
  movesFile = fopen("moves.txt", "r");
  fscanf(movesFile, "%[^\3]", moves);
  fclose(movesFile);

  // splits the file by spaces 
  // move = moves.split(' ')
  for(i = 0; moves[i] != 0; i++)
  {
    // copies the char if it is not a space
    if(moves[i] != ' ')
    {
      move[j][k] = moves[i];
      k++;
    }
    // jumps to the next array when it detects a space
    else
    {
      move[j][k] = '\0';
      j++;
      k = 0;
    }
  }

  // if it exists more than one element
  if(*size - 2 >= 0)
  {
    // this compacts the instructions:
    // u u will become u2
    if(strcmp(move[*size - 1], move[*size - 2]) == 0)
    {
      move[*size - 2][0] = move[*size - 1][0];
      move[*size - 2][1] = '2';
      move[*size - 2][2] = '\0';
      move[*size - 1][0] = '\0';
      
      // since 2 instructions become 1, the amount of instructions decrease by 1
      *size -= 1;
    }
    else if(move[*size - 1][0] == move[*size - 2][0] && move[*size - 2][1] == '2')
    {
      // u2 u' becomes u
      if(move[*size - 1][1] == '\'')
      {
        move[*size - 2][0] = move[*size - 1][0];
        move[*size - 2][1] = '\0';
        move[*size - 1][0] = '\0';
      }
      // u2 u becomes u'
      else
      {
        move[*size - 2][0] = move[*size - 1][0];
        move[*size - 2][1] = '\'';
        move[*size - 1][0] = '\0';
      }
      
      *size -= 1;
    }
    // u u' will delete each other
    else if(move[*size - 1][0] == move[*size - 2][0] && ((move[*size - 2][1] == '\'' && move[*size - 1][1] == '\0') || (move[*size - 2][1] == '\0' && move[*size - 1][1] == '\'')))
    {
      move[*size - 2][0] = '\0';
      move[*size - 1][0] = '\0';
      
      // since 2 instructions are removes, the amount of instructions decrease by 2
      *size -= 2;
    }
  }

  // overwrites the file with the new set of instructions
  movesFile = fopen("moves.txt", "w");

  // all the strings in move
  for(i = 0; i < *size; i++)
  {
    // if the array length is not 0 (if the array contains an instruction)
    if(strlen(move[i]) != 0)
    {
      // prins the instruction in the file
      fprintf(movesFile, "%s ", move[i]);
    }
  }
  
  fclose(movesFile);

  return;
}