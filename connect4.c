//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include"connect4.h"
#include <stdio.h>
struct position{
  struct position* up;
  struct position* down;
  struct position* left;
  struct position* right;
  char content;
};

struct board_structure {
/*Put something suitable here*/
    struct position *topLeft;
    int rows;
    int cols;
};

board setup_board(){
//You may put code here
  struct board_structure *newBoard = malloc (sizeof (struct board_structure));
  if(newBoard == NULL){
    error(1);
  }
  else{
    return newBoard;
  }
}

void cleanup_board(board u){
//You may put code here
}

void read_in_file(FILE *infile, board u){
//You may put code here
  char str1;
  static int height,width;
  width = 0;
  height = 0;
  struct position *current = malloc(sizeof(struct position));
  if(current == NULL){
    error(1);
  }
  struct position *above = malloc(sizeof(struct position));
  if(above == NULL){
    error(1);
  }
  struct position *rowStart = malloc(sizeof(struct position));
  if(rowStart == NULL){
    error(1);
  }

  int newLine = 0;
  int firstLine = 1;
  while(fscanf(infile,"%c",&str1) != EOF){
    struct position *newPos = malloc(sizeof(struct position));
    if(newPos == NULL){
      error(1);
    }
    else{
      if(u -> topLeft == NULL){
        u -> topLeft = newPos;
        current = newPos;
        above = u -> topLeft;
        rowStart = u -> topLeft;
      }
      if(newLine == 1){
        above = rowStart;
        //printf("beep");
        rowStart = newPos;
      }
      if(str1 == '\n'){
        newLine = 1;
        firstLine = 0;
        ++height;
      }
      if(str1 != '\n'){
        ++width;
        newLine = 0;
        newPos -> content = str1;
        current -> right = newPos;
        newPos -> left = current;
        if(firstLine != 1){
          newPos -> up = above;
          above -> down = newPos;

          above = above -> right;
        }
      }
      current = newPos;
      printf("%c",str1);
    }

  }
  u -> rows = height;
  u -> cols = width/height;
  printf("%s","test1");
  //printf("%d\n",u -> rows);
  //printf("%d\n",u -> cols);
  //printf("%c\n",u->topLeft->right->down->down->down->content);

}
int main(){
  board tBoard = setup_board();
  FILE *test;
  test = fopen("initial_board.txt", "r");
  read_in_file(test,tBoard);
  printf("%d",1);
  write_out_file(test,tBoard);

}
void write_out_file(FILE *outfile, board u){
//You may put code here
  struct position *current = malloc(sizeof(struct position));
  if(current == NULL){
    error(1);
  }
  struct position *lineStart = malloc(sizeof(struct position));
  if(lineStart == NULL){
    error(1);
  }

  lineStart = u -> topLeft;

  int found4 = 0;
  int x = 0,y = 0;
  while(lineStart != NULL){
    ++y;
    current = lineStart;
    while(current != NULL){
      ++x;
      printf("%c",current->content);
      if(current->content != '-' &&found4 == 0){
        if(x+4 <= u->cols && u->cols +4 current->content == current->right->content == current->right->right->content == current->right->right->right->content){
          found4 = 1;
          current->content == toupper(current->content);
          current->right->content == toupper(current->content);
          current->right->right->content == toupper(current->content);
          current->right->right->right->content == toupper(current->content);
        }
        else if(current->content == current->right->down->content == current->right->down->right->down->content == current->right->down->right->down->right->down->content){
          found4 = 1;
          current->content == toupper(current->content);
          current->right->down->content == toupper(current->content);
          current->right->down->right->down->content == toupper(current->content);
          current->right->down->right->down->right->down->content == toupper(current->content);
        }
        else if(current->content == current->left->down->content == current->left->down->left->down->content == current->left->down->left->down->left->down->content){
          found4 = 1;
          current->content == toupper(current->content);
          current->left->down->content == toupper(current->content);
          current->left->down->left->down->content == toupper(current->content);
          current->left->down->left->down->left->down->content == toupper(current->content);
        }
        else if(current->content == current->down->content == current->down->down->content == current->down->down->down->content){
          found4 = 1;
          current->content == toupper(current->content);
          current->down->content == toupper(current->content);
          current->down->down->content == toupper(current->content);
          current->down->down->down->content == toupper(current->content);
        }
        current = current -> right;
      }

    }
  }
}

char next_player(board u){
//You may put code here
}

char current_winner(board u){
//You may put code here
}

struct move read_in_move(board u){
//You may put code here
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
//You may put code here
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
//You may put code here
}

int is_valid_move(struct move m, board u){
//You may put code here
}

char is_winning_move(struct move m, board u){
//You may put code here
}

void play_move(struct move m, board u){
//You may put code here
}

//You may put additional functions here if you wish.
