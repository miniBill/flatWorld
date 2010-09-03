#include <ncurses.h>

#include "phaseOne.h"
#include "slowriter.h"

#include "config.h"

void phaseOne(){
#ifdef FAST 
  char dimension1[] = "Dimension : 1";//"Dimensione : 2";
  slowtitle(dimension1);

  napms(2000);
  
  mvaddch(LINES/4,COLS/2,'1');
  refresh();
  
  napms(5000);
  
  mvaddch(LINES/4,COLS/2,' ');
  refresh();
  
#endif
}