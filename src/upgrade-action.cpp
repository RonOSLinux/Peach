#include <cstdlib>
#include <string>
#include "../inc/const.h"
#include "../inc/modules.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>

int main(int argc,char const *argv[]) {
  int t;
  if(argc>1) {
    std::string mode;
    mode=argv[1];
    if(mode=="update") {
      t=std::system("gksudo \'apt-get --assume-yes dist-upgrade\'");
    } else if(mode=="upgrade") {
      t=std::system(("gksudo \'~/"+PEACH_FOLDER+"bin/update-sources "+getCurrentVersion()+" "+getNewVersion()+"\'").c_str());
      t=std::system("gksudo \'apt-get --assume-yes update\'");
      t=std::system("gksudo \'apt-get --assume-yes dist-upgrade\'");
    }
    setModule("upgrade-action",1);
  }
  return 0;
}
