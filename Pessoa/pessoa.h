#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>

using namespace std;

struct Telefone{
    string numero;
    string foneId;
public:
    Telefone(string _numero = "", string _foneId = ""){
        numero = _numero;
        foneId = _foneId;
    }
    string getNumero(){
        return numero;
    }
    string getFoneId(){
        return foneId;
    }

};

class Pessoa{
        string name;
        vector<Telefone> tels;
        string email;
public:
        Pessoa(string _name = ""){
            name = _name;
        }
        string getName(){
            return name;
        }
        string getTel(){
            return tel;
        }
        void setTel(string &value){
            tel = value;
        }
        string getEmail(){
            return email;
        }
        void setEmail(string value){
            email = value;
        }

        static bool validateTel(string numero) {
            string data = "1234567890()- ";
            for(auto c : numero)
                if(data.find(c) == string::npos)
                    return false;
            return true;
        }

        bool verfEmal(string _email){

        }
};

#endif // PESSOA_H
