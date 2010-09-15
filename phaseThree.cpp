#include <caca.h>

#include "config.h"

#include "phaseThree.h"
#include "slowriter.h"

struct point3{
  float x,y,z;
  point3(float nx,float ny,float nz) : x(nx), y(ny), z(nz) {}
};

struct point2{
  float x,y;
  point2(float nx,float ny) : x(nx), y(ny) {}
};

struct line3{
  point3 a,b;
  line3(point3 na,point3 nb) : a(na), b(nb) {}
};

class cube{
  private:
    point3 ulf, urf, ulb, urb, dlf, drf, dlb, drb;
  public:
    line3 lines[12];
    cube(point3 center,int size) : 
      ulf(center.x-size,center.y+size,center.z-size),
      urf(center.x+size,center.y+size,center.z-size),
      ulb(center.x-size,center.y+size,center.z+size),
      urb(center.x+size,center.y+size,center.z+size),
      dlf(center.x-size,center.y-size,center.z-size),
      drf(center.x+size,center.y-size,center.z-size),
      dlb(center.x-size,center.y-size,center.z+size),
      drb(center.x+size,center.y-size,center.z+size),
      lines((line3[12]){
        line3(ulf,urf),line3(urf,urb),line3(urb,ulb),line3(ulb,ulf),//top
        line3(dlf,drf),line3(drf,drb),line3(drb,dlb),line3(dlb,dlf),//bottom
        line3(ulf,dlf),line3(urf,drf),line3(urb,drb),line3(ulb,dlb)//rest
      }) { }
};

static int w,h;

#define DIST 4

point2 project(point3 & o){
  float dz=o.z+DIST;
  return point2(5*o.x*DIST/dz+w/2,h/2-5*o.y*DIST/dz);
}

void phaseThree(caca_display_t * dp, caca_canvas_t * cv){
  w = caca_get_canvas_width(cv);
  h = caca_get_canvas_height(cv);
  caca_set_color_ansi(cv, CACA_RED, CACA_BLACK);
  
  point3 center(0,0,0);
  
  while(1){
    //caca_set_attr(cv, CACA_BOLD);
    for(int x=0;x<w;x++)
      for(int y=0;y<h;y++)
	caca_put_char(cv, x, y, ' ');
    cube c(center,2);

    for(int i=0;i<12;i++){
      point2 a=project(c.lines[i].a);
      point2 b=project(c.lines[i].b);
      caca_draw_thin_line(cv,a.x,a.y,b.x,b.y);
    }

    caca_refresh_display(dp);

    caca_event_t ev;

    if(caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, -1) == 0)
      continue;

    switch(caca_get_event_key_ch(&ev)){
      case CACA_KEY_ESCAPE:
      case 'q':
	return;
      case CACA_KEY_RETURN:
	break;
      case CACA_KEY_HOME:
	break;
      case CACA_KEY_END:
	break;
      case CACA_KEY_LEFT:
	if(center.x>-2)
	  center.x-=0.2;
	break;
      case CACA_KEY_RIGHT:
	if(center.x<2)
	  center.x+=0.2;
	break;
      case CACA_KEY_UP:
	if(center.y<2)
	  center.y+=0.2;
	break;
      case CACA_KEY_DOWN:
	if(center.y>-2.4)
	  center.y-=0.2;
	break;
      case CACA_KEY_DELETE:
	break;
      case CACA_KEY_BACKSPACE:
	break;
      default:
	break;
    }
  }
}

