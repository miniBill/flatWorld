#include <ncurses.h>
#include <string.h>
#include "slowriter.h"
#include "phaseZero.h"
#include "phaseOne.h"
#include "phaseTwo.h"

#include "config.h"

int z,t;

void input2d(int in);

int main(int argc, char **argv){
  initscr();
  start_color();
  noecho();
  keypad(stdscr,1);
  
  init_pair(1,COLOR_WHITE,COLOR_BLUE); //couple 1 set to White on Blue
  init_pair(2,COLOR_BLACK,COLOR_BLUE); //couple 2 set to Black on Blue

  curs_set(0); //makes cursor invisible
  
  bkgd(COLOR_PAIR(1)); // use couple 1 for background
  refresh();
  
  //attron(COLOR_PAIR(1)); //use couple 1 for the following text
  
#ifndef FAST
  char greet1[] = "Welcome to flatWorld...";//"Benvenuto a flatWorld...";
  char greet2[] = "...your adventure starts here...";//"...qui comincia la tua avventura...";
  slowmessage(greet1);
  napms(500);
  slowmessage(greet2);
  napms(500);
#endif
  
  phaseZero();
  phaseOne();
  phaseTwo();

  endwin();
  return 0;
}