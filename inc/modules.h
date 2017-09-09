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

inline std::string getCurrentVersion() {
  std::ifstream src;
  std::string ret;
  src.open(PEACH_FOLDER+"sources/current",std::ios_base::in);
  src>>ret;
  src.close();
  return ret;
}

inline std::string getNewVersion() {
  std::ifstream src;
  std::string ret;
  src.open(PEACH_FOLDER+"sources/upgrade",std::ios_base::in);
  src>>ret;
  src.close();
  return ret;
}

inline void setCurrentVersion() {
  std::ofstream src_c;
  src_c.open(PEACH_FOLDER+"sources/current",std::ios_base::out);
  src_c<<getNewVersion()<<std::endl;
  src_c.close();
}

#endif
