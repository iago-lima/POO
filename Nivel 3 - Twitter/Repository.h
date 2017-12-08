#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <iostream>
#include <map>

using namespace std;

template <class T>
class Repository {
    map<string, T> _mapa;
    string nomeTipo;
public:
    Repository(string nomeTipo = ""){
        this->nomeTipo = nomeTipo;
    }

    void add(string key, T t){
        if(_mapa.count(key) == 1)
            throw nomeTipo + " " + key + " ja existe";
        _mapa[key] = t;
    }

    bool exist(string key){
        return _mapa.count(key);
    }

    void rm(string key){
        if(!_mapa.erase(key))
            throw nomeTipo + " " + key + " nao existe";
    }

    T& at(string key){
        if(_mapa.count(key) == 0)
            throw nomeTipo + " " + key + " nao existe";
        return _mapa[key];
    }

    vector<T> getValues(){
        vector<T> vet;
        for(auto par : _mapa)
            vet.push_back(par.second);
        return vet;
    }
};

#endif // REPOSITORY_H
