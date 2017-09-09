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
      t=std::system("apt-get --assume-yes dist-upgrade");
    } else if(mode=="upgrade") {
      std::vector<std::string> in;
      std::string temp;
      std::ifstream src_in;
      std::ofstream src_out;
      src_in.open("/etc/apt/sources.list",std::ios_base::in);
      while(!src_in.eof()) {
        std::getline(src_in,temp);
        in.push_back(temp);
      }
      src_in.close();
      src_out.open("/etc/apt/sources.list");
      for(std::string t: in) {
        src_out<<std::regex_replace(t,std::regex(getCurrentVersion()),getNewVersion())<<std::endl;
      }
      src_out.close();
      t=std::system("apt-get --assume-yes update");
      t=std::system("apt-get --assume-yes dist-upgrade");
      setCurrentVersion();
    }
    setModule("upgrade-action",1);
  }
  return 0;
}
