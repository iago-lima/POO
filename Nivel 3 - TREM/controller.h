#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <iostream>
#include <sstream>
#include "trem.h"
#include "split.h"
#include "vagao.h"
#include "passageiro.h"
#include "registropassageiros.h"

using namespace std;

void inicializar(Trem &trem){
    trem = Trem(2);
    trem.addVagao(Vagao(0, 2));
    trem.addVagao(Vagao(1, 2));
    trem.embarcarTrem(new Passageiro("123"));
    trem.embarcarTrem(new Passageiro("321"));
    trem.embarcarTrem(new Passageiro("789"));
    trem.embarcarTrem(new Passageiro("987"));
}

class Controller{
    Trem trem;
    RegistroPassageiros registro;
    int id{0};
public:
    Controller(){}

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];

        if(cmd == "help"){
            return  "  # comandos                                 \n"
                    "  iniciarTrem _qtdVagoes                     \n"
                    "  addVagao _capacidade                       \n"
                    "  embarcar _passCpf                          \n"
                    "  desembarque _passCpf                       \n"
                    "  show                                       \n"
                    "  registro                                   \n"
                    "  getEspacoLivre                             \n"

                    "  # default                                  \n"
                    "  fim                                        \n"
                    "  help                                       \n";
        }
        if(cmd == "iniciarTrem"){
            int numVag = Int(ui[1]);
            trem = Trem(numVag);
            string resp = "Trem iniciado com " + ui[1] + " vagões.\n";
            return resp;
//            trem = Trem(2);
//            inicializar(trem);
        }
        if(cmd == "getEspacoLivre"){
            cout << "Espaço livre: " << trem.getCapacidade() - trem.getLotacao();
        }

        if("addVagao" == cmd){
            int capac = Int(ui[1]);
            Vagao vag = Vagao(id, capac);
            trem.addVagao(vag);
            id++;
            return "Vagao adicionado.\n";
        }
        if(cmd == "embarcar"){
            Passageiro* aux = new Passageiro(ui[1]);
                if(!trem.verifPassTrem(aux)){
                    throw string("CPF já embarcado.");
                }
            trem.embarcarTrem(aux);
            registro.addPass(*aux);
            return "Passageiro " + aux->getCPF() + " embarcado com sucesso.";
        }
        if(cmd == "desembarque"){
            Passageiro * pass = trem.desembarcarTrem(ui[1]);
            delete pass;
            return "Passageiro " + ui[1] + " desembarcado";
        }
        if(cmd == "show"){
            return trem.toStringTrem();
        }
        if(cmd == "registro"){
            return registro.toString();
        }
        return "";
    }


    void commandLine() {
        string line = "";
        while(line != "fim"){
            cout << "(help): ";
            getline(cin, line);
            if(line == "")
                continue;
            cout << ">> " << line << endl;
            try {
                cout << process(line) << endl;
            } catch(const string& erro) {
                cout << erro << endl;
            }
        }
    }
};

#endif // CONTROLLER_H
