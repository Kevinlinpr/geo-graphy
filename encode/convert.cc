#include "convert.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace cuda_next
{

std::string Convert::FCTEM2TXT(const std::vector<double>& source) {
    std::vector<double> data{};
    for (auto item : source) {
        data.push_back(item);
    }
    auto L = (data[14]);; 
    auto A = data.size();
    auto N = A / (2 * L + 30);

    if (!Convert::IsInteger(N)) {
        return "ERROR_CONVERT";
    }

    Convert::FCTEMObjectDouble fctem;
    std::vector<std::vector<double>> headerTmp(static_cast<int>(N), std::vector<double>(static_cast<int>(L)));
    std::vector<std::vector<double>> dataTmp(static_cast<int>(N), std::vector<double>(static_cast<int>(L)));
    std::vector<std::vector<double>> windowTmp(static_cast<int>(N), std::vector<double>(static_cast<int>(L)));

    for (int i = 0, k = 0; k < static_cast<int>(N); i += (30 + (static_cast<int>(L) * 2)), ++k) {

        for (int j = 0, index = 0; j < 30; ++j, ++index) {
            headerTmp[k][index] = { data[i + j] };
        }

        for (int j = 30, index = 0; j < 30 + static_cast<int>(L); ++j, ++index) {
            dataTmp[k][index] = { data[i + j] };
        }

        for (int j = 30 + static_cast<int>(L), index = 0; j < 30 + (2 * static_cast<int>(L)); ++j, ++index) {
            windowTmp[k][index] = { data[i + j] };
        }
    }
    fctem.header = std::move(headerTmp);
    fctem.data = std::move(dataTmp);
    fctem.window = std::move(windowTmp);

    std::stringstream outSs;
    outSs << std::scientific;
    outSs.precision(7);

    const char* SPACE = "   ";

    outSs << N << SPACE << data[14];

    for (double item : fctem.window[0]) {
        outSs << SPACE << item;
    }
    outSs << std::endl;

    for (int i = 0; i < N; ++i) {

        outSs << fctem.header[i][1] << SPACE << fctem.header[i][3];
        for (double item : fctem.data[i]) {
            outSs << SPACE << item;
        }
        outSs << std::endl;
    }
    return outSs.str();
}

std::string Convert::FCTEM2TXT(const std::string& source) {
    std::fstream fs;
    fs.open(source);

    std::vector<std::string> data{};
    if (fs.bad()) {
        std::cout << "Bad for reading the file" << std::endl;

        return "ERROR_CONVERT";
    }
    while (!fs.eof()) {
        std::string line;
        std::getline(fs, line);
        if (line.empty()) { continue; }
        data.push_back(line);
    }
    fs.close();
    auto L = (atof(data[14].c_str()));; 
    auto A = data.size(); 
    auto N = A / (2 * L + 30);
    
    if (!Convert::IsInteger(N)) {
        
        std::cout << "�ļ�ʱ����ͳһ";
        return "ERROR_CONVERT";
    }

    Convert::FCTEMObject fctem;
    std::vector<std::vector<std::string>> headerTmp(static_cast<int>(N), std::vector<std::string>(static_cast<int>(L)));
    std::vector<std::vector<std::string>> dataTmp(static_cast<int>(N), std::vector<std::string>(static_cast<int>(L)));
    std::vector<std::vector<std::string>> windowTmp(static_cast<int>(N), std::vector<std::string>(static_cast<int>(L)));

    for (int i = 0, k = 0; k < static_cast<int>(N); i += (30 + (static_cast<int>(L) * 2)), ++k) {

        for (int j = 0, index = 0; j < 30; ++j, ++index) {
            headerTmp[k][index] = { data[i + j] };
        }

        for (int j = 30, index = 0; j < 30 + static_cast<int>(L); ++j, ++index) {
            dataTmp[k][index] = { data[i + j] };
        }

        for (int j = 30 + static_cast<int>(L), index = 0; j < 30 + (2 * static_cast<int>(L)); ++j, ++index) {
            windowTmp[k][index] = { data[i + j] };
        }
    }
    fctem.header = std::move(headerTmp);
    fctem.data = std::move(dataTmp);
    fctem.window = std::move(windowTmp);

    std::stringstream outSs;
    outSs << std::scientific;
    outSs.precision(7);

    const char* SPACE = "   ";

    outSs << N << SPACE << Scientific2double(data[14]);

    for (const std::string& item : fctem.window[0]) {
        outSs << SPACE << Scientific2double(item);
    }
    outSs << std::endl;

    for (int i = 0; i < N; ++i) {

        outSs << Scientific2double(fctem.header[i][1]) << SPACE << Scientific2double(fctem.header[i][3]);
        for (const std::string& item : fctem.data[i]) {
            outSs << SPACE << Scientific2double(item);
        }
        outSs << std::endl;
    }

    return outSs.str();
}


bool Convert::IsInteger(double number) {
    if (number - int(number) == 0) {
        return true;
    }
    return false;
}

double Convert::Scientific2double(const std::string& scientific) {
    return (atof(scientific.c_str()));
}


} // namespace cuda_next
