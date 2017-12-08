#ifndef VAGAO_H
#define VAGAO_H
#include <vector>
#include <iostream>
#include <sstream>
#include "passageiro.h"

using namespace std;

class Vagao{
    int id;
    int capacidade;
    vector<Passageiro*> cadeiras;

public:
    Vagao(int _id = 0, int _capacidade = 0):
        cadeiras(_capacidade, nullptr)
    {
        capacidade = _capacidade;
        id = _id;
    }

    int getLotacao(){
        int cont = 0;
        for(Passageiro * pass : cadeiras){
            if(pass){
                cont++;
            }
        }
        return cont;
    }

    int getCapacidade(){
        return capacidade;
    }

    bool embarcarVagao(Passageiro* _passageiro){
        for(auto &pass : cadeiras){
            if(pass == nullptr){
                pass = _passageiro;
                return true;
            }
        }
        return false;
    }
    Passageiro* desembarcarVagao(string _cpf){
        for(int i = 0; i < capacidade; i++){
            if((cadeiras[i] != nullptr) && (cadeiras[i]->getCPF() == _cpf)){
                Passageiro* j = cadeiras[i];
                cadeiras[i] = nullptr;
                return j;
            }
        }
        return nullptr;
    }

    string toStringVagao(){
        stringstream ss;
        ss << "Vagão: " << id << endl;
        ss << "Capacidade: " << capacidade << endl;
        ss << "[";
        for(auto pass : cadeiras){
            (pass != nullptr) ? ss << " " << pass->toStringPass() : ss << " - ";
            }
        ss << "]";
        return ss.str();
    }

    bool verfPassVagao(Passageiro* _passageiro){
        for(auto pass : cadeiras){
            if((pass != nullptr) && (pass->getCPF() == _passageiro->getCPF())){
                return false;
            }
        }
        return true;
    }


};

#endif // VAGAO_H
