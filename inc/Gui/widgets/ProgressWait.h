#ifndef _ProgressWait
#define _ProgressWait

class ProgressWait: public Widget {
private:
  double pos;
  Uint32 timer;
  SDL_Color color;
  bool down=false;
  bool c_down=false;
  bool c_down2=false;
  bool c_down3=false;
public:
  ProgressWait(int x,int y,int w) {
    create(x,y,w,3);
    pos=0.0;
    color={0,185,0,205};
  }
  void display() {
    renderFillRect(getX(),getY()+1,getWidth(),1,normal_color);
    renderFillRect(getX()+getWidth()/2-((int)(getWidth()*pos)/2),getY(),(int)(getWidth()*pos),getHeight(),color);
    if(SDL_GetTicks()-timer>=20) {
      if(!down) {
        if(pos<1.0) {
          pos+=0.01;
        } else {
          down=true;
        }
      }
      if(down) {
        if(pos>0.0) {
          pos-=0.01;
        } else {
          down=false;
        }
      }
      if(!c_down) {
        if(color.b<255) {
          color.b+=15;
        } else if(color.b==255) {
          c_down=true;
        }
      } else {
        if(color.b>0) {
          color.b-=15;
        } else if(color.b==0) {
          c_down=false;
        }
      }
      if(!c_down2) {
        if(color.g<255) {
          color.g+=5;
        } else if(color.g==255) {
          c_down2=true;
        }
      } else {
        if(color.g>0) {
          color.g-=5;
        } else if(color.g==0) {
          c_down2=false;
        }
      }
      if(!c_down3) {
        if(color.r<255) {
          color.r+=1;
        } else if(color.r==255) {
          c_down3=true;
        }
      } else {
        if(color.r>0) {
          color.r-=1;
        } else if(color.r==0) {
          c_down3=false;
        }
      }
      timer=SDL_GetTicks();
    }
  }
};

#endif
