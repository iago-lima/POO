#ifndef SPLIT_H
#define SPLIT_H
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

template <class T>
T cast(std::string palavra){
    T value;
    std::stringstream(palavra) >> value;
    return value;
}

inline int Int(std::string word){
    return cast<int>(word);
}

inline int Float(std::string word){
    return cast<float>(word);
}

std::vector<std::string> split(const std::string& line){
    std::vector<std::string> saida;
    std::istringstream ss(line);
    std::string palavra;
    while(ss){
        ss >> palavra;
        saida.push_back(palavra);
    }
    return saida;
}

template<class T>
std::string vet2str(std::string prefix, std::vector<T> vet, std::string separ){
    std::stringstream ss;
    ss << prefix;
    for(auto elem : vet)
        ss << elem.toString() << separ;
    return ss.str();
}

template<class T>
std::string join(std::vector<T> vet, std::string separ){
    std::stringstream ss;
    for(unsigned int i = 0; i < vet.size() - 1 ; i++)
        ss << vet[i] << separ;
    if(vet.size() > 0)
        ss  << vet.back();
    return ss.str();

}

template<class T>
std::string join(std::list<T> _list, std::string separ){
    return join(std::vector<T>(_list.begin(), _list.end()), separ);

}



#endif // SPLIT_H
