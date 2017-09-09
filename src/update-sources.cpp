#include <fstream>
#include <regex>

int main(int argc,char* argv[]) {
  if(argc==3) {
    std::string regex_1;
    std::string regex_2;
    std::vector<std::string> in;
    std::string temp;
    std::ifstream src_in;
    std::ofstream src_out;

    regex_1=argv[1];
    regex_2=argv[2];

    src_in.open("/etc/apt/sources.list",std::ios_base::in);
    while(!src_in.eof()) {
      std::getline(src_in,temp);
      in.push_back(temp);
    }
    src_in.close();

    src_out.open("/etc/apt/sources.list",std::ios_base::out);
    for(std::string t: in) {
      src_out<<std::regex_replace(t,std::regex(regex_1),regex_2)<<std::endl;
    }
    src_out.close();
  }
  return 0;
}
