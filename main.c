#include<stdio.h>
#include"connect4.h"
int main(){
  FILE *infile,*outfile,*infile2,*outfile2;

  board my_board=setup_board();
  infile=fopen("initial_board.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);

  write_out_file(stdout,my_board);

  board my_board2=setup_board();
  infile2=fopen("test_board.txt","r");
  read_in_file(infile,my_board2);
  fclose(infile2);

  write_out_file(stdout,my_board2);

  while(current_winner(my_board)=='.') {
    struct move next_move = read_in_move(my_board);
    if (is_valid_move(next_move,my_board)) {
      printf("%s%c\n","Winning Move: ",is_winning_move(next_move,my_board));
    play_move(next_move,my_board);
    write_out_file(stdout,my_board);
    }

    struct move next_move2 = read_in_move(my_board2);
    if (is_valid_move(next_move2,my_board2)) {
      printf("%s%c\n","Winning Move: ",is_winning_move(next_move2,my_board2));
    play_move(next_move2,my_board2);
    write_out_file(stdout,my_board2);
    }
  }

  outfile=fopen("final_board.txt","w");
  write_out_file(outfile,my_board);
  fclose(outfile);

  cleanup_board(my_board);
  return 0;
}
