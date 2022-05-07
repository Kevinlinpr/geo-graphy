#ifndef GEO_GRAPHY_ENCODE_H_
#define GEO_GRAPHY_ENCODE_H_

#include "libcode.h"
#include <string>

using namespace std;
extern "C"
{
    extern void FCTEM2TXT(char* fctem, char* txt);
    extern std::string Parse(const std::string& fctem);
}

#endif // GEO_GRAPHY_ENCODE_H_
