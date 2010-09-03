#include <ncurses.h>

#include "phaseTwo.h"
#include "slowriter.h"

#include "config.h"

int x,y;

void input2d(int in){
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

void phaseTwo(){  
#ifndef FAST
  char dimension2[] = "Dimension : 2";//"Dimensione : 2";
  slowtitle(dimension2);

  napms(2000);
  
  mvaddch(LINES/4,COLS/2,'2');
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
    input2d(in);
    move(y,x);
    addch('2');
    refresh();
  } while((in=getch())!='q' && in!=27);
}