#include <curses.h>
#ifdef CACA
#include <caca.h>
#endif
#include <string.h>
#include <stdlib.h>

#include "config.h"

#include "slowriter.h"

#include "phaseZero.h"
#include "phaseOne.h"
#include "phaseTwo.h"
#ifdef CACA
#include "phaseThree.h"
#endif

int main(int argc, char **argv){
  initscr();
  start_color();
  noecho();
  keypad(stdscr,1);
  cbreak();
  
  init_pair(1,COLOR_WHITE,COLOR_BLUE); //couple 1 set to White on Blue
  init_pair(2,COLOR_RED,COLOR_BLUE);   //couple 2 set to Red   on Blue
  init_pair(3,COLOR_GREEN,COLOR_BLUE); //couple 3 set to Green on Blue

  curs_set(0); //makes cursor invisible
  
  bkgd(COLOR_PAIR(1)); // use couple 1 for background (and implicitly, for the text)
  refresh();
  
  //attron(COLOR_PAIR(1)); //use couple 1 for the following text
  
#ifndef FAST
  char greet1[] = "Welcome to flatWorld...";//"Benvenuto a flatWorld...";
  char greet2[] = "...your adventure starts here...";//"...qui comincia la tua avventura...";
  slowmessage(greet1);
  napms(500);
  slowmessage(greet2);
  napms(500);
  
  phaseZero();
  phaseOne();
#endif
  phaseTwo();
  endwin();

#ifdef CACA  
  setenv("CACA_DRIVER","ncurses",1);
  
  caca_canvas_t * cv;
  caca_display_t * dp;
  caca_event_t ev;

  dp = caca_create_display(NULL);
  if(!dp) return 1;
  cv = caca_get_canvas(dp);
  caca_set_display_title(dp, "flatWorld: Dimension 3");
  caca_set_color_ansi(cv, CACA_WHITE, CACA_BLUE);
  caca_refresh_display(dp);

  phaseThree(dp,cv);

  caca_free_display(dp);
#endif

  return 0;
}

