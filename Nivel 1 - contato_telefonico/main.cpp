#include <iostream>
#include <vector>

using namespace std;

struct Telefone{
    string descricao;
    string numero;
    Telefone(string descricao = "", string numero = ""){
        this->descricao = descricao;
        this->numero = numero;
    }
};

class Contato{
private:
    string nome;
    string email;
    vector<Telefone> fone;

public:
    Contato(string nome = ""){
        this->nome = nome;
    }

    void setNome(string nome){
        this->nome = nome;
    }


};

int main(){
    Contato contato;
    string op;
    while(op != "fim"){
        cin >> op;
        if(op == "iniciar"){
            string nome;
            cin >> nome;
            contato = Contato(nome);
            cout << "Contato criado" << endl;
        }
        else if(op == "setNome"){
            string nome;
            cin >> nome;
            contato.setNome(nome);
            cout << "Nome atualizado" << endl;
        }
        else if(op == "setMail"){

        }
    }

}


















