#include <curses.h>
#include <stdlib.h>

#include "config.h"

#include "phaseTwo.h"
#include "slowriter.h"

#define width (40)
#define height (20)

#define size (width*height)

#define posy ((LINES/4)*2)
#define posx ((COLS/4)*2)+1

#define p(gy,gx) ((gy)*width + (gx))

uint terrain[size];

static uint x,y;

static uint xrand=0;
static uint c=13;

static unsigned long urand(){
  unsigned long long nxrand=(32718*xrand+c);
  xrand=(uint)nxrand;
  c=(uint)nxrand>>16;
  return xrand;
}

static void generateTerrain(){
#define r16 (urand()%16)
  for(int i = 0; i < size; i++)
    for(int h=0;h<8;h++)
      terrain[i]|=(r16 & r16 & r16 & r16);
}

static int lx(int gx){
  return (gx-x)*2-1+posx;
}

static int ly(int gy){
  return (gy-y)*2-1+posy;
}

static void smallerase(){
  for(int y=1;y<LINES;y++)
    for(int x=0;x<COLS;x++)
      mvaddch(y,x,' ');
}

static char up(int gy,int gx){
  if(gy==0){
    if(terrain[p(gy,gx)]&1)
      return '*';
    else
      return '*';
  }
  else{
    if(terrain[p(gy,gx)]&1){
      if(terrain[p(gy-1,gx)]&4)
	return '*';
      else
	return 'V';
    }
    else{
      if(terrain[p(gy-1,gx)]&4)
	return '^';
      else
	return ' ';
    }
  }
}

static char left(int gy,int gx){
  if(gx==0){
    if(terrain[p(gy,gx)]&8)
      return '*';
    else
      return '*';
  }
  else{
    if(terrain[p(gy,gx)]&8){
      if(terrain[p(gy,gx-1)]&2)
	return '*';
      else
	return '>';
    }
    else{
      if(terrain[p(gy,gx-1)]&2)
	return '<';
      else
	return ' ';
    }
  }
}

static void drawTerrain(){
  int my=0,mx=0;
  smallerase();
  mvprintw(0, COLS-15,"              ");
  mvprintw(0, COLS-15,"x: %d, y: %d",x,y);
  while(ly(my)<1)my++;
  while(lx(mx)<0)mx++;
  for(int gy=my; gy<=height && ly(gy)<LINES; gy++){
    for(int gx=mx; gx<=width && lx(gx)<COLS; gx++){
      //ul
      attron(COLOR_PAIR(4)|A_BOLD);
      mvaddch(ly(gy),lx(gx),'*');
      if(gy != height && gx != width){
	int Col=lx(gx)+1;
	bool hasCol=Col<COLS;
	
	int SCol=Col+1;
	bool hasSCol=SCol<COLS;
	
	int Line=ly(gy)+1;
	bool hasLine=Line<LINES;
	
	int SLine=Line+1;
	bool hasSLine=SLine<LINES;
	if(hasCol){
	  //up
	  char u=up(gy,gx);
	  if(u=='*')
	    attron(A_BOLD);
	  else
	    attroff(A_BOLD);
          mvaddch(ly(gy),Col,u);
	  
	  //mid
	  if(hasLine)
	    mvaddch(Line,Col,' ');
	  
	  //down
	  if(hasSLine && gy==height-1)
	      mvaddch(SLine,Col,'*');
	}
	if(hasLine){
	  //left
	  char l=left(gy,gx);
	  if(l=='*')
	    attron(A_BOLD);
	  else
	    attroff(A_BOLD);
	  mvaddch(Line,lx(gx),l);
	  
	  //right
	  if(hasSCol && gx==width-1)
	    mvaddch(Line,SCol,'*');
	}
      }
    }
  }
}

static void input2d(int in){
  if((in == KEY_DOWN || in == 's' || in == 'j') && y<height-1){
    if(y==height-2){
      if(!(terrain[p(y,x)]&4))
	y++;
    }
    else if(up(y+1,x)=='V' || up(y+1,x)==' ')
      y++;
    return;
  }
  if((in == KEY_UP || in == 'w' || in == 'k') && y>0){
    if(up(y,x) == '^' || up(y,x) == ' ')
      y--;
    return;
  }
  if((in == KEY_LEFT || in == 'a' || in == 'h') && x>0){
    if(left(y,x) == '<' || left(y,x) == ' ')
      x--;
    return;
  }
  if((in == KEY_RIGHT || in == 'd' || in == 'l') && x<width-1){
    if(x==width-2){
      if(!(terrain[p(y,x)]&2))
	x++;
    }
    else if(left(y,x+1) == '>' || left(y,x+1) == ' ')
      x++;
    return;
  }
}

void phaseTwo(){  
  char dimension2[] = "Dimension : 2";//"Dimensione : 2";
  slowtitle(dimension2);

  init_pair(4,COLOR_YELLOW,COLOR_BLUE);

#ifndef FAST
  napms(2000);
  
  x=posx;
  
  attron(A_BOLD|COLOR_PAIR(2));
  mvaddch(LINES/4,x,PLAYER_CHAR);
  attroff(A_BOLD|COLOR_PAIR(2));
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

#ifndef FAST
  attron(A_BOLD|COLOR_PAIR(2));
  for(y=LINES/4;y<posy;){
    mvaddch(y,x,' ');
    mvaddch(++y,x,PLAYER_CHAR);
    refresh();
    napms(250);
  }
  attroff(A_BOLD|COLOR_PAIR(2));
#else
  mvaddch(y,x,' ');
  attron(A_BOLD|COLOR_PAIR(2));
  mvaddch(posy,x,PLAYER_CHAR);
  attroff(A_BOLD|COLOR_PAIR(2));
  refresh();
#endif
  
  x=width-1;
  y=height-1;
  
  int in=ERR,lastin;
  
  mvprintw(0,0,"WASD/HJKL/Arrows to move, R to restart, Q to quit.");
  
  timeout(10);
  
  while(x!=0 || y!=0){
    do{
      lastin=in;
      in=getch();
      if(in=='r'){
        x=width-1;
	y=height-1;
      }
    }while(in!=ERR);
    
    if(lastin=='q' || lastin==27)
      break;
    
    if(lastin!=ERR)
      input2d(lastin);
    drawTerrain();
    attron(A_BOLD|COLOR_PAIR(2));
    mvaddch(posy,posx,PLAYER_CHAR);
    attroff(A_BOLD|COLOR_PAIR(2));
    int lxz=lx(0),lyz=ly(0);
    if(lxz+1>=0 && lyz+1>1){
      attron(A_BOLD|COLOR_PAIR(3));
      mvaddch(lyz+1,lxz+1,GOAL_CHAR);
      attroff(A_BOLD|COLOR_PAIR(3));
    }
    refresh();
#ifndef FAST
    napms(250);
#endif
  }
  
  if(x!=0 || y!=0){
    endwin();
    exit(0);
  }
  
  timeout(-1);

  smallerase();
//mvprintw(0,0,"WASD/HJKL/Arrows to move, R to restart, Q to quit.");
  mvprintw(0,0,"                                                  ");
  
  char final[]="Q: Uh, I got it. What now?";
  slowmessage(final);
}

