#ifndef REGISTROPASSAGEIROS_H
#define REGISTROPASSAGEIROS_H
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "passageiro.h"

using namespace std;

bool CompPass(Passageiro a, Passageiro b){
    return a.getCPF() < b.getCPF();
}

class RegistroPassageiros{
    vector<Passageiro> passageiros;

public:
    RegistroPassageiros(){}

    void addPass(Passageiro pass){
        passageiros.push_back(pass);
    }

    vector<Passageiro> getAllPass(){
        return passageiros;
    }

    string toString(){
        sort(passageiros.begin(), passageiros.end(), CompPass);
        stringstream ss;
        ss << "Registro de passageiros:" << endl;
        for(Passageiro pass : passageiros){
            ss << " --> " << pass.toStringPass() << endl;
        }
        return ss.str();
    }
};

#endif // REGISTROPASSAGEIROS_H
