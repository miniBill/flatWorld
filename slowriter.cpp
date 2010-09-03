//#ifdef WIN32
//#include "curses.h"
//#else
#include <ncurses.h>
//#endif
#include <string.h>
#include "slowriter.h"

void slowrite(int y,int x,char * message){
  while(*message){
    attroff(A_BOLD);
    mvaddch(y,x,*(message));
    refresh();
    napms(50);
    attron(A_BOLD);
    mvaddch(y,x,*(message));
    x++;
    refresh();
    if(*(message++)==' ')
      napms(20);
    else
      napms(40);
  }
  attroff(A_BOLD);
}

void slowerase(int y,int x,char * message){
  move(y,x);
  attroff(A_BOLD);
  while(*message){
    mvaddch(y,x,*(message));
    refresh();
    napms(45);
    mvaddch(y,x,' ');
    x++;
    refresh();
    if(*(message++)==' ')
      napms(15);
    else
      napms(35);
  }
  attroff(A_BOLD);
}

void slowmessage(char * message){
  slowmessage(message,500);
}

void slowmessage(char * message,int delay){
  slowrite(LINES/2,(COLS-strlen(message))/2,message);
  napms(delay);
  slowerase(LINES/2,(COLS-strlen(message))/2,message);
}

void slowtitle(char * message){
  slowrite(0,(COLS-strlen(message))/2,message);
}
