#include <ncurses.h>
#include <stdlib.h>

#include "phaseTwo.h"
#include "slowriter.h"

#include "config.h"

#define width (80)
#define height (20)
#define size (width*height)

int terrain[size];

static void generateTerrain(){
  srand(0);
  for(int i = 0; i < size; i++)
    terrain[i]=rand()%16;
}

static int x,y;

static int lx(int gx){
  return (gx-x)*2;
}

static int ly(int gy){
  return (gy-y)*2+1;
}

static void smallerase(){
  move(1,0);
  for(int y=1;y<LINES;y++)
    for(int x=0;x<COLS;x++)
      mvaddch(y,x,' ');
}

static void drawTerrain(){
  int my=0,mx=0;
  smallerase();
  while(ly(my)<0)my++;
  while(lx(mx)<0)mx++;
  for(int gy=my; ly(gy)<LINES; gy++){
    for(int gx=mx; lx(gx)<COLS; gx++){
      mvaddch(ly(gy),lx(gx),'*');
    }
  }
}

static void presentTerrain(){
  
}

static void input2d(int in){
  mvprintw(0,0,"y:%d x:%d",y,x);
  if((in == KEY_DOWN || in == 's') && y<height){
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
  if((in == KEY_RIGHT || in == 'd') && x<width){
    x++;
    return;
  }
}

void phaseTwo(){  
  char dimension2[] = "Dimension : 2";//"Dimensione : 2";
  slowtitle(dimension2);

#ifndef FAST
  napms(2000);
  
  mvaddch(LINES/4,COLS/2,'2');
  refresh();
  
  napms(5000);
  
  char dim2msg1[]="Q: Ah! Much better!";// "Y: Ah! Decisamente meglio!";
  char dim2msg2[]="Q: I can move freely, at last...";//"Y: Ora riesco a muovermi...";
  char dim2msg3[]="Q: I guess I'll take a look around me";//"Y: Mi guardero' un po' in giro";
  slowmessage(dim2msg1,3000);
  napms(500);
  slowmessage(dim2msg2,3000);
  napms(500);
  slowmessage(dim2msg3,3000);
#endif

  generateTerrain();
  
  presentTerrain();
  
  x=COLS/2;

#ifndef FAST
  for(y=LINES/4;y<LINES/2;){
    mvaddch(y,x,' ');
    mvaddch(++y,x,'2');
    refresh();
    napms(250);
  }
#else
  mvaddch(y,x,' ');
  y=LINES/2;
  mvaddch(y,x,'2');
  refresh();
#endif
  
  x=width/2;
  y=height/2;
  
  timeout(10);
  
  int in=ERR,lastin;
  
  while(1){
    do{
      lastin=in;
      in=getch();
      if(in=='r'){
        x=width/2;
	y=height/2;
      }
    }while(in!=ERR);
    
    if(in=='q' || in==27)
      break;
    
    if(lastin!=ERR)
      input2d(lastin);
    drawTerrain();
    mvaddch(LINES/2,COLS/2,'2');
    refresh();
#ifndef FAST
    napms(250);
#endif
  }
  
  timeout(-1);
}