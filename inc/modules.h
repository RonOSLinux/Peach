#ifndef _modules
#define _modules

#include <fstream>
#include <string>
#include "const.h"

inline void setModule(std::string name,int value) {
    std::ofstream mfile;
    mfile.open(PEACH_FOLDER+"opt/"+name+".mod",std::ios_base::out);
    mfile<<value;
    mfile.close();
}

inline int getModule(std::string name) {
    std::ifstream mfile;
    int ret;
    mfile.open(PEACH_FOLDER+"opt/"+name+".mod",std::ios_base::in);
    mfile>>ret;
    mfile.close();
    return ret;
}

inline void resetAllModules() {
  setModule("action",0);
  setModule("apps",0);
  setModule("panel",0);
  setModule("restart",0);
  setModule("shutdown",0);
  setModule("software",0);
  setModule("software-action",0);
  setModule("settings",0);
  setModule("upgrade",0);
}

#endif
