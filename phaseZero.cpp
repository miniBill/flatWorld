#include <curses.h>

#include "config.h"

#include "phaseZero.h"
#include "slowriter.h"

void phaseZero(){
#ifndef FAST
  char dimension0[] = "Dimension : 0";//"Dimensione : 0";
  slowtitle(dimension0);
  napms(2000);
  
  attron(A_BOLD|COLOR_PAIR(2));
  mvaddch(LINES/4,COLS/2,PLAYER_CHAR);
  attroff(A_BOLD|COLOR_PAIR(2));
  attron(COLOR_PAIR(1));
  refresh();
  
  napms(5000);
  
  char dim0msg1[]="Q: Where am I?";//"Y: Dove mi trovo?";
  char dim0msg2[]="Q: What a strange place is this...";//"Y: Che strano posto e' mai questo?";
  char dim0msg3[]="Q: I feel blocked!";//Y: Mi sento bloccato!";
  slowmessage(dim0msg1,3000);
  napms(500);
  slowmessage(dim0msg2,3000);
  napms(500);
  slowmessage(dim0msg3,3000);
  
  napms(3000);
  
  mvaddch(LINES/4,COLS/2,' ');
  refresh();
#endif
}

