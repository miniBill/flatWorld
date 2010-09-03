#include <ncurses.h>
#include <string.h>
#include "slowriter.h"

#define subj 164

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
  
  char greet1[] = "Benvenuto in flatworld...";
  char greet2[] = "...qui comincia il tuo viaggio...";
  slowmessage(greet1);
  napms(500);
  slowmessage(greet2);
  napms(500);
  
  char dimension0[] = "Dimensione : 0";
  slowtitle(dimension0);
  
  mvaddch(LINES/4,COLS/2,subj);
  
  char dim0msg1[]="Y: Dove mi trovo?";
  char dim0msg2[]="Y: Che strano posto è mai questo...";
  char dim0msg2[]="Y: Mi sento bloccato!";
  slowmessage(dim0msg1,3000);
  napms(500);
  slowmessage(dim0msg2,3000);
  napms(500);
  slowmessage(dim0msg3,3000);
  
  napms(3000);
  
  mvaddch(LINES/4,COLS/2,' ');
  
  char dimension1[] = "Dimensione : 2";
  slowtitle(dimension1);
  
  char dim2msg1[]="Y: Decisamente meglio!";
  char dim2msg2[]="Y: Ora riesco a muovermi...";
  char dim2msg3[]="Y: Mi guarderò un po' in giro";
  slowmessage(dim2msg1,3000);
  napms(500);
  slowmessage(dim2msg2,3000);
  napms(500);
  slowmessage(dim2msg3,3000);
  
  y=LINES/2;
  x=COLS/2;
  input(0);
  
  int in=0;

  while((in=getch())!='q' && in!=27){
    move(y,x);
    addch(' ');
    input(in);
    move(y,x);
    addch(subj);
    refresh();
  }

  endwin();
  return 0;
}

void input(int in){
  if((in == KEY_DOWN || in == 's') && y<LINES-1){
    y++;
    return;
  }
  if((in == KEY_UP || in == 'w') && y>0){
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