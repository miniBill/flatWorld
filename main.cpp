#include <ncurses.h>
#include <string.h>
#include "slowriter.h"

#define FAST

int x,y,z,t;

void input(int in);

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
  char greet2[] = "...here start your adventure...";//"...qui comincia la tua avventura...";
  slowmessage(greet1);
  napms(500);
  slowmessage(greet2);
  napms(500);
#endif
  
  char subj;

#ifndef FAST
  char dimension0[] = "Dimension : 0";//"Dimensione : 0";
  slowtitle(dimension0);
  subj='0';
  napms(2000);
  
  mvaddch(LINES/4,COLS/2,subj);
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
  
  char dimension1[] = "Dimension : 2";//"Dimensione : 2";
  slowtitle(dimension1);
#endif
  subj='2';
#ifndef FAST
  napms(2000);
  
  mvaddch(LINES/4,COLS/2,subj);
  refresh();
  
  napms(5000);
  
  char dim2msg1[]="Q: Ah! Much better!";// "Y: Ah! Decisamente meglio!";
  char dim2msg2[]="Q: I can move, at last...";//"Y: Ora riesco a muovermi...";
  char dim2msg3[]="Q: I guess I'll take a look around me";//"Y: Mi guardero' un po' in giro";
  slowmessage(dim2msg1,3000);
  napms(500);
  slowmessage(dim2msg2,3000);
  napms(500);
  slowmessage(dim2msg3,3000);
#endif
  
  y=LINES/4;
  x=COLS/2;
  
  int in=0;

  do{
    move(y,x);
    addch(' ');
    input(in);
    move(y,x);
    addch(subj);
    refresh();
  } while((in=getch())!='q' && in!=27);

  endwin();
  return 0;
}

void input(int in){
  if((in == KEY_DOWN || in == 's') && y<LINES-1){
    y++;
    return;
  }
  if((in == KEY_UP || in == 'w') && y>1){
    y--;
    return;
  }
  if((in == KEY_LEFT || in == 'a') && x>0){
    x--;
    return;
  }
  if((in == KEY_RIGHT || in == 'd') && x<COLS-1){
    x++;
    return;
  }
}