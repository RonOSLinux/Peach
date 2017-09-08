#ifndef _Tooltip
#define _Tooltip

class Tooltip {
private:
  Widget* widget;
  Label* content;
  int x;
  int y;
  int w;
  int h;
  int pos_mode;
public:
  Tooltip(Widget* anchor,const char* text,int mode) {
    widget=anchor;
    pos_mode=mode;
    content=new Label(text,f_reg_sma,{215,215,215},0,0);
    w=content->getWidth()+10;
    h=content->getHeight()+10;
    if(pos_mode==0) {
      x=widget->getX();
      y=widget->getY()-40;
    } else {
      x=widget->getX()-w+widget->getWidth();
      y=widget->getY()-40;
    }
    content->setX(x+5);
    content->setY(y+5);
  }
  void update() {
    w=content->getWidth()+10;
    h=content->getHeight()+10;
    if(pos_mode==0) {
      x=widget->getX();
      y=widget->getY()-40;
    } else {
      x=widget->getX()-w+widget->getWidth();
      y=widget->getY()-40;
    }
    content->setX(x+5);
    content->setY(y+5);
  }
  void setPosMode(int mode) {
    pos_mode=mode;
  }
  void display() {
    if(widget->getEvent()!=0) {
      renderFillRect(x,y,w,h,{25,25,25,185});
      content->display();
    }
  }
};

#endif
