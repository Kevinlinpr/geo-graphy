#include <fstream>
#include <string>
#include <sstream>
#include "encode/include/encode.h"

int main(){
    std::string fctem_path = "../data/L10.FCTEM";
    std::string out_txt_path = "./L10.txt";
    std::ifstream ifs;
    ifs.open(fctem_path);
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    std::string result = Parse(ss.str());
    std::ofstream out;
    out.open(out_txt_path);
    out.write(result.c_str(),result.length());
    out.close();
    return 0;
}