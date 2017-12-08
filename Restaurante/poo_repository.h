#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <vector>
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

    //adiciona se a chave ainda nao existir
    T * add(string key, T t){
        if(_mapa.count(key) == 1)
            throw nomeTipo + " " + key + " ja existe";
        _mapa[key] = t;
        return &_mapa[key];
    }

    //retorna se o objeto está no repositório
    bool has(string key){
        return _mapa.count(key);
    }

    //retorna se conseguiu remover
    void rm(string key){
        if(!_mapa.erase(key))
            throw nomeTipo + " " + key + " nao existe";
    }

    //retorna o endereço do objeto
    T * get(string key){
        if(_mapa.count(key) == 0)
            throw nomeTipo + " " + key + " nao existe";
        return &_mapa[key];
    }

    //retorna o endereço do objeto
    T& at(string key){
        if(_mapa.count(key) == 0)
            throw nomeTipo + " " + key + " nao existe";
        return _mapa[key];
    }

    //retonar um vetor com a cópia dos elementos
    vector<T> values(){
        std::vector<T> vet;
        for(auto& par : _mapa)
            vet.push_back(par.second);
        return vet;
    }

    //retorna um vetor com a cópia das chaves
    vector<string> keys(){
        vector<string> vet;
        for(auto& par : _mapa)
            vet.push_back(par.first);
        return vet;
    }

};

#endif // REPOSITORY_H

