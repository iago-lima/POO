#ifndef SPLIT
#define SPLIT
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(string line){
    vector<string> saida;
    stringstream ss(line);
    string palavra;
    while(ss >> palavra)
        saida.push_back(palavra);
    return saida;
}

template <class T>
T cast(string palavra){
    T value;
    stringstream(palavra) >> value;
    return value;
}

inline int Int(std::string word){
    return cast<int>(word);
}

inline int Float(std::string word){
    return cast<float>(word);
}

#endif // SPLIT

