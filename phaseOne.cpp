#include <curses.h>
#include <stdlib.h>

#include "phaseOne.h"
#include "slowriter.h"

#include "config.h"

static int x,y;

bool back=false;

static void input1d(int in){
  if((in == KEY_LEFT || in == 'a') && x>COLS/4){
    x--;
    back=true;
    
  }
  else if(in == KEY_RIGHT || in == 'd'){
    x++;
    back=false;
  }
}

void phaseOne(){
  char dimension1[] = "Dimension : 1";//"Dimensione : 2";
  slowtitle(dimension1);

  napms(2000);
  
  attron(A_BOLD);
  mvaddch(LINES/4,COLS/2,sub);
  attroff(A_BOLD);
  refresh();

#ifndef FAST
  napms(5000);

  char dim1msg1[]="Q: Uh! What has happened?";
  char dim1msg2[]="Q: Looks like I can move, now";
  char dim1msg3[]="Q: I wonder what can happen next";
  slowmessage(dim1msg1,3000);
  napms(500);
  slowmessage(dim1msg2,3000);
  napms(500);
  slowmessage(dim1msg3,3000);
#endif
  
  x=COLS/2;
  
#ifndef FAST
  for(y=LINES/4;y<LINES/2;){
    mvaddch(y,x,' ');
    attron(A_BOLD);
    mvaddch(++y,x,sub);
    attroff(A_BOLD);
    refresh();
    napms(250);
  }
  for(;x>COLS/4;){
    mvaddch(y,x,' ');
    attron(A_BOLD);
    mvaddch(y,--x,sub);
    attroff(A_BOLD);
    refresh();
    napms(250);
  }
#else
  y=LINES/2;
  x=COLS/4;
  mvaddch(LINES/4,COLS/2,' ');
  attron(A_BOLD);
  mvaddch(LINES/2,COLS/4,sub);
  attroff(A_BOLD);
#endif

  timeout(10);
  
  int in=ERR,lastin;
  
  attron(A_BOLD);
  mvaddch(y,COLS*3/4,'@');
  attroff(A_BOLD);
  
  while(x<COLS*3/4){
    do{
      lastin=in;
      in=getch();
    }while(in!=ERR);
    
    if(in=='q' || in==27)
      break;
    
    if(lastin!=ERR){
      move(y,x);
      input1d(lastin);
      addch(back?' ':'.');
      move(y,x);
      attron(A_BOLD);
      addch(sub);
      attroff(A_BOLD);
      refresh();
#ifndef FAST
      napms(250);
#endif
    }
  }
  
  timeout(-1);
  
  if(x!=COLS*3/4){
    endwin();
    exit(0);
  }
  
  for(x=COLS/4;x<=COLS*3/4;x++){
    mvaddch(y,x,' ');
    refresh();
    napms(60);
  }
  
  char moveOn[]="Q: Let's move on, now...";
  slowmessage(moveOn,3000);
}