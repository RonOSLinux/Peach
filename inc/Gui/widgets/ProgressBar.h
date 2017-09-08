#ifndef _ProgressBar
#define _ProgressBar

class ProgressBar: Widget {
private:
  Uint32 loadTimer;
  double pos=0.0;
  bool first=true;
public:
  ProgressBar(int x,int y,int w) {
    create(x,y,w,3);
  }
  void display() {
    if(first) {
      loadTimer=SDL_GetTicks();
      first=false;
    }
    renderFillRect(getX(),getY()+1,getWidth(),1,normal_color);
    renderFillRect(getX(),getY(),(int)(getWidth()*pos),getHeight(),hover_color);
    if(SDL_GetTicks()-loadTimer>=1000) {
      if(pos<1.0) {
        pos+=0.01;
      }
      loadTimer=SDL_GetTicks();
    }
  }
  void setPos(double p) {
    pos=p;
  }
};

#endif
