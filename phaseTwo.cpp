#include <curses.h>
#include <stdlib.h>

#include "phaseTwo.h"
#include "slowriter.h"

#include "config.h"

#ifndef FAST
#define width (200)
#define height (100)
#else
#define width (20)
#define height (10)
#endif
#define size (width*height)

#define posy ((LINES/4)*2)
#define posx ((COLS/4)*2)+1

#define p(gy,gx) ((gy)*width + (gx))

int terrain[size];

static void generateTerrain(){
  srand(0);
#define r16 (rand()%16)
  for(int i = 0; i < size; i++)
#ifndef FAST
    terrain[i]=(r16 & r16 & r16) | (r16 & r16 & r16);
#else
    terrain[i]=r16 & r16;
#endif
}

static int x,y;

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
      return '*';//HACK
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
      return '*';//HACK
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
  while(ly(my)<1)my++;
  while(lx(mx)<0)mx++;
  for(int gy=my; gy<=height && ly(gy)<LINES; gy++){
    for(int gx=mx; gx<=width && lx(gx)<COLS; gx++){
      //ul
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
	  mvaddch(ly(gy),Col,u);
	  
	  //mid
	  if(hasLine)
	    mvaddch(Line,Col,' ');
	  
	  //down
	  if(hasSLine && gy==height-1){
	    if(terrain[p(gy,gx)]&4)
	      mvaddch(SLine,Col,'*');
	    else
	      mvaddch(SLine,Col,'*');//HACK
	  }
	}
	if(hasLine){
	  //left
	  char l=left(gy,gx);
	  mvaddch(Line,lx(gx),l);
	  
	  //right
	  if(hasSCol && gx==width-1){
	    if(terrain[p(gy,gx)]&2)
	      mvaddch(Line,SCol,'*');
	    else
	      mvaddch(Line,SCol,'*');//HACK
	  }
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

#ifndef FAST
  napms(2000);
  
  x=posx;
  
  attron(A_BOLD);
  mvaddch(LINES/4,x,sub);
  attroff(A_BOLD);
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
  for(y=LINES/4;y<posy;){
    mvaddch(y,x,' ');
    attron(A_BOLD);
    mvaddch(++y,x,sub);
    attroff(A_BOLD);
    refresh();
    napms(250);
  }
#else
  mvaddch(y,x,' ');
  attron(A_BOLD);
  mvaddch(posy,x,sub);
  attroff(A_BOLD);
  refresh();
#endif
  
  x=width/2;
  y=height/2;
  
  int in=ERR,lastin;
  
  mvprintw(0,0,"WASD/HJKL/Arrows to move, R to restart, Q to quit.");
  
  timeout(10);
  
  while(x!=0 || y!=0){
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
    attron(A_BOLD);
    mvaddch(posy,posx,sub);
    attroff(A_BOLD);
    int lxz=lx(0),lyz=ly(0);
    if(lxz+1>=0 && lyz+1>1)
      mvaddch(lyz+1,lxz+1,'@');
    refresh();
#ifndef FAST
    napms(250);
#endif
  }
  
  timeout(-1);

  smallerase();
//mvprintw(0,0,"WASD/Arrows to move, R to restart, Q to quit.");
  mvprintw(0,0,"                                             ");
  
  char final[]="Q: Uh, I got it. What now?";
  slowmessage(final);
}
