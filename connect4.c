//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include"connect4.h"
//Represents each individual position on the grid, with pointers to the surrounding positions and the content of the pos
struct position{
  struct position* up;
  struct position* down;
  struct position* left;
  struct position* right;
  char content;
};
int winFound(char val1, char val2, char val3, char val4);
char * getContents(board u);
void setContents(board u,char * contents);
//Represents each board
struct board_structure {
/*Put something suitable here*/
    struct position *topLeft;
    int rows;
    int cols;
};


board setup_board(){
//You may put code here
//Malloc a new board and check if it has worked
  struct board_structure *newBoard = malloc (sizeof (struct board_structure));
  if(newBoard == NULL){
    fprintf(stderr, "%s\n","Unable to reserve memory for new board" );
    exit(1);
  }
  else{
    newBoard ->topLeft = NULL;
    return newBoard;
  }
}

void cleanup_board(board u){
//You may put code here
//Go through the entire board, freeing each position at a time
  struct position *current = NULL;
  current = u->topLeft;
  struct position *lineBelow = current;
  while(lineBelow!= NULL){
    lineBelow = current->down;
    while(current != NULL){
      struct position *temp = current;
      current = current->right;
      free(temp);
    }
    current = lineBelow;
  }
  free(current);
  free(u);
}

void read_in_file(FILE *infile, board u){
//You may put code here
  if(infile == NULL){
    fprintf(stderr, "%s\n","Unable to find infile" );
    cleanup_board(u);
    exit(1);
  }
  char str1;
  static int height,width,prevWidth;
  prevWidth = 0;
  width = 0;
  height = 1;
  //Pointers to positions on the grid
  struct position *current = NULL;
  struct position *above  = NULL;
  struct position *rowStart  = NULL;

  //Represents if the current line is the first line or if its starting a new line
  int newLine = 0;
  int firstLine = 1;
  //While there is still a character to read in
  //fscanf(infile,"%c",&str1)
  while((str1=fgetc(infile))){
    if(str1 == EOF){
      break;
    }
    //Create a new positon, checking if the malloc has worked
    const char *valid_characters = ".ox\n";
    if (strchr(valid_characters, str1) == NULL)
      {
        fprintf(stderr, "%s%c\n","Invalid char in input file: ",str1 );
        cleanup_board(u);
        exit(1);
      }
    struct position *newPos = malloc(sizeof(struct position));
    if(newPos == NULL){
      fprintf(stderr, "%s\n","Unable to reserve memory for new position" );
      cleanup_board(u);
      exit(1);
    }
    else{
      //If we havent defined the top left position yet
      if(u -> topLeft == NULL){
        //Set topleft and current
        u -> topLeft = newPos;
        current = newPos;
        above = u -> topLeft;
        rowStart = u -> topLeft;
      }
      //If starting a new line, set above to the start of the row above and then update row start
      if(newLine == 1){
        height++;
        if(firstLine != 1){
          if(width < prevWidth){
            fprintf(stderr,"%s\n","Board doesn't have consistent width");
            free(newPos);
            cleanup_board(u);
            exit(1);
          }
        }
        width = 0;
        above = rowStart;
        rowStart = newPos;
      }
      //If we have found the newline character
      if(str1 == '\n'){
        newLine = 1;
        prevWidth = width;
        firstLine = 0;

        free(newPos);
      }
      //If not a newline
      if(str1 != '\n'){
        ++width;
        if(firstLine != 1){
          if(width > prevWidth){
            fprintf(stderr,"%s\n","Board doesn't have consistent width");
            cleanup_board(u);
            exit(1);
          }
        }
        newLine = 0;
        //Update the contents of the new position, and corresponding pointers
        newPos -> content = str1;
        current -> right = newPos;
        newPos -> left = current;
        //If not on the topline, update the corresponding pointers
        if(firstLine != 1){
          newPos -> up = above;
          above -> down = newPos;
          above = above -> right;
        }
      }
      current = newPos;
    }

  }
  //Set the rows and columns of the grid
  u -> rows = height;
  u -> cols = width;
}
void write_out_file(FILE *outfile, board u){
//You may put code here
  if(outfile == NULL){
    fprintf(stderr, "%s\n","Unable to find outfile" );
    cleanup_board(u);
    exit(1);
  }
  //Pointers to certain positions in the grid
  struct position *current  = NULL;
  struct position *lineStart  = NULL;
  //Starting at the topleft position
  lineStart = u -> topLeft;
  //Records the current x,y position
  int x = 0,y = 0;
  //While on a valid line
  while(lineStart != NULL){
    y++;
    x=0;
    //Starting at the first position in the line
    current = lineStart;
    while(current != NULL){
      ++x;
      //If current is either and x or o
      if((current->content == 'x' || current->content == 'o')){
        //Checks if there is a win in the grid, checking right, down right, down left and straight down
        //Right
        //If we are in a valid position to check and the characters are the same, make them upper case
        if(x+3 <= u->cols && y+3<=u->cols && winFound(current->content,current->right->content,current->right->right->content,current->right->right->right->content) == 1){
          current->content = toupper(current->content);
          current->right->content = toupper(current->content);
          current->right->right->content = toupper(current->content);
          current->right->right->right->content = toupper(current->content);

        }
        //Down right
        else if(x+3 <= u->cols && y+3<=u->rows && winFound(current->content,current->right->down->content,current->right->down->right->down->content,current->right->down->right->down->right->down->content) == 1){
          current->content = toupper(current->content);
          current->right->down->content = toupper(current->content);
          current->right->down->right->down->content = toupper(current->content);
          current->right->down->right->down->right->down->content = toupper(current->content);

        }
        //Down left
        else if(x-3 > 0 &&y+3<=u->rows && winFound(current->content,current->left->down->content,current->left->down->left->down->content,current->left->down->left->down->left->down->content)==1){
          current->content = toupper(current->content);
          current->left->down->content = toupper(current->content);
          current->left->down->left->down->content = toupper(current->content);
          current->left->down->left->down->left->down->content = toupper(current->content);

        }
        //down
        else if(y+3<=u->rows && winFound(current->content,current->down->content,current->down->down->content,current->down->down->down->content)==1){
          current->content = toupper(current->content);
          current->down->content = toupper(current->content);
          current->down->down->content = toupper(current->content);
          current->down->down->down->content = toupper(current->content);
        }
      }
      //Print to file and put the char back to lower
        fprintf(outfile,"%c",current->content);
        current->content = tolower(current->content);
        //Move accross the line
        current = current -> right;
    }
    //Move down the grid
    lineStart = lineStart -> down;
    fprintf(outfile,"\n");
  }
}

char next_player(board u){
  //Pointers to positions in the grid
  struct position *current = NULL;
  struct position *lineStart = NULL;
  //Starting top left
  lineStart = u -> topLeft;
  //Count the amount of xs and os
  int xCount = 0,oCount = 0;
  //Traverse through the grid and update the counters as necessary
  while(lineStart != NULL){
    current = lineStart;
    while(current != NULL){
      switch (current->content) {
        case 'x':
          xCount++;
          break;
        case 'o':
          oCount++;
          break;
      }
      current = current->right;
    }
    lineStart = lineStart->down;
  }
  //Return the smaller of the 2 counters
  if(xCount > oCount){
    return 'o';
  }
  return 'x';
}
char current_winner(board u){
  //Pointers to positions in the grid
  struct position *current  = NULL;
  struct position *lineStart = NULL;
  lineStart = u -> topLeft;
  //Used as bools to say if we've found an x win or an o win
  int foundx = 0;
  int foundo = 0;
  int x = 0,y = 0;
  while(lineStart != NULL){
    y++;
    x=0;
    current = lineStart;
    while(current != NULL){
      ++x;
      //If we havent found an x & y + the character is valid
      if((current->content == 'x' || current->content == 'o')  && (foundx == 0 || foundo == 0)){
        //Right
        //Check if a win is there and update bools as needed, checks the same way as current_winner does
        if(x+3 <= u->cols && y+3<=u->cols && winFound(current->content,current->right->content,current->right->right->content,current->right->right->right->content) == 1){
          switch (current->content) {
            case 'o':
              foundo = 1;
              break;
            case 'x':
              foundx = 1;
              break;
          }
        }
        //Down right
        else if(x+3 <= u->cols && y+3<=u->rows && winFound(current->content,current->right->down->content,current->right->down->right->down->content,current->right->down->right->down->right->down->content) == 1){
          switch (current->content) {
            case 'o':
              foundo = 1;
              break;
            case 'x':
              foundx = 1;
              break;
          }
        }
        //Down left
        else if(x-3 > 0 && y+3<=u->rows && winFound(current->content,current->left->down->content,current->left->down->left->down->content,current->left->down->left->down->left->down->content)==1){
          switch (current->content) {
            case 'o':
              foundo = 1;
              break;
            case 'x':
              foundx = 1;
              break;
          }

        }
        //Down
        else if(y+3<=u->rows && winFound(current->content,current->down->content,current->down->down->content,current->down->down->down->content)==1){
          switch (current->content) {
            case 'o':
              foundo = 1;
              break;
            case 'x':
              foundx = 1;
              break;
          }

        }
      }
        current = current -> right;
    }
    lineStart = lineStart -> down;

  }
  //Depending on what has been found, return the correct value
  if(foundx == 1 && foundo==1){
    return 'd';
  }
  else if(foundx == 1){
    return 'x';
  }
  else if(foundo == 1){
    return 'o';
  }
  //Check top row
  current = u->topLeft;
  while(current!= NULL){
    // If there is a space then return '.'
    if(current->content == '.'){
      return '.';
    }
    current = current->right;
  }
  //Grid is full so its a draw
  return 'd';

}
struct move read_in_move(board u){
  //Asks the user for nums
  char colNum[256];
  char rowNum[256];
//You may put code here
  int valid = 0;
  while(valid == 0){
    valid = 1;
    printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
    scanf("%256s",colNum);
    int size = (int)(strlen(colNum));
    for(int i = 0; i<size;i++){
      if((i==0) &&(colNum[i] == '-')){
        continue;
      }
      if(isdigit(colNum[i]) == 0){
        valid = 0;
      }
    }
  }
  valid = 0;
  while(valid == 0){
    valid = 1;
    printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
    scanf("%256s",rowNum);
    int size = (int)(strlen(rowNum));
    for(int i = 0; i<size;i++){
      if((i==0) &&(rowNum[i] == '-')){
        continue;
      }
      if(isdigit(rowNum[i]) == 0){
        valid = 0;
      }
    }
  }
  //Returns the move
  struct move tempMove;
  tempMove.column = atoi(colNum);
  tempMove.row = atoi(rowNum);
  return tempMove;
}
int is_valid_move(struct move m, board u){
//You may put code here
//If the number of rows is too high
  int valid = 1;
  if(m.row > u->rows || m.row< (-1*u->rows)){
    return 0;
  }
  //If the number of columns is too high or too low
  if(m.column<=0 || m.column>u->cols){
    return 0;
  }
  //Pointer to a position in the grid
  struct position *current = NULL;
  current = u->topLeft;
  //Moves to corresponding column
  for(int i=1;i<m.column;i++){
    current = current->right;
  }
  //Not valid if column is full
  if(current->content!= '.'){
    valid = 0;
  }
  return valid;
}
char is_winning_move(struct move m, board u){
//You may put code here
//Get the contents of the grid currntly
  char *contents = getContents(u);
  //Play the move out
  play_move(m,u);
  //Check if there is a winner in the file
  char winner = current_winner(u);
  //Set the contents back to pre-move contents
  setContents(u,contents);
  //Free the allocated memory
  free(contents);
  //Return the char
  return winner;
}
void play_move(struct move m, board u){
//You may put code here
  //Moves to correct column and finds lowest available space
  char player = next_player(u);
  struct position *current = NULL;
  current = u->topLeft;
  //Moves as far down as possible
  while(current->down != NULL){
    current = current->down;
  }
  //Column number
  int x = 1;
  while(x!=m.column){
    current = current -> right;
    x++;
  }
  //Keep going up until we find an empty position
  while(current->content != '.'){
    current = current->up;
  }
  //Place the token here
  current->content  = player;
  struct position *lineStart;
  lineStart = u->topLeft;

  //IF rotating
  if(m.row!=0){
    int rowNum = abs(m.row);
    //Get to the current row number
    for(int j=u->rows;j>rowNum;j--){
        lineStart = lineStart->down;
      }
    //Rotating right
    if(m.row>0){
      current = lineStart;
      for(int i = 1;i<u->cols;i++){
        //printf("%c\n",current->content );
        current = current->right;
      }
      //printf("%c\n",current->content );
      //printf("\n");
      char temp = current->content;
      for(int i = u->rows;i>=0;i--){
        current->content = current->left->content;
        //printf("%c\n",current->content );
        current = current->left;
      }
      lineStart->content = temp;
    }
    //Rotating left
    else{
      current = lineStart;
      char temp = lineStart->content;
      for(int i = 1;i<u->cols;i++){
        current->content = current->right->content;
        current = current->right;
      }
      current->content = temp;
    }
  }
  //Updates board accounting for gravity
  int changed = 1;
  //While there was a change on the last loop
  while(changed==1){
    changed = 0;
    lineStart = u->topLeft;
    //Go through the rows
    while(lineStart != NULL){
      current = lineStart;
      //Go throug the columns
      while(current!= NULL){
        char temp = current->content;
        //If current is a counter
        if((current->content == 'x' || current->content == 'o')){
          //While there is space below move the counters
          while(current->down != NULL&& current->down->content == '.'){
            changed = 1;
            current->content = '.';
            current = current->down;
          }
          current ->content = temp;
        }
          current = current -> right;
      }
      lineStart = lineStart -> down;
    }
  }
}

//You may put additional functions here if you wish.
int winFound(char val1, char val2, char val3, char val4){
  if(val1==val2&&val1==val3&&val1 == val4){
    return 1;
  }
  return 0;
}
//Goes through the list, recording the contents into a char array
char * getContents(board u){
  char *contents = malloc(u->rows * u->cols * sizeof(char));
  if(contents == NULL) {
    fprintf(stderr, "%s\n","Unable to malloc contents array" );
    cleanup_board(u);
    exit(1);
  }
  int pos = 0;
  struct position *current  = NULL;
  struct position *lineStart = NULL;
  lineStart = u -> topLeft;
while(lineStart != NULL){
    current = lineStart;
    while(current != NULL){
      contents[pos] = current->content;
      pos++;
      current = current->right;
    }
    lineStart = lineStart->down;
  }
  return contents;
}
//Goes through the list and sets the contents according to the char array
void setContents(board u,char * contents){
  int pos = 0;
  struct position *current  = NULL;
  struct position *lineStart = NULL;
  lineStart = u -> topLeft;
while(lineStart != NULL){
    current = lineStart;
    while(current != NULL){
      current->content = contents[pos];
      pos++;
      current = current->right;
    }
    lineStart = lineStart->down;
  }
}
