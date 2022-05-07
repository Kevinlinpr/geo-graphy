#include "include/encode.h"
#include <vector>
#include "convert.h"
#include <stdio.h>
#include <string.h>

void FCTEM2TXT(char* fctem, char* txt) {
    std::string tmp(fctem);
    strcat(txt, Parse(tmp).c_str());
}

std::string Parse(const std::string& fctem) {
    int ReadNum = fctem.length();
    int SizeNum = ReadNum / 20;
    char* Call1 = new char[ReadNum + 1];
    double* Ball1 = new double[SizeNum];

    for (int i = 0; i < ReadNum; ++i) {
        Call1[i] = fctem[i];
    }
    Code2DataWrite(Call1, Ball1, SizeNum);
    std::vector<double> Data{};

    Data.clear();
    for (int i = 0; i < SizeNum; i++)
    {
        Data.push_back(Ball1[i]);
    }
    std::string result = std::move(cuda_next::Convert::FCTEM2TXT(Data));
    return result;
}