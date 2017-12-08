#include <iostream>

using namespace std;

class Pessoa{
    string nome;
    int ano;
public:
    Pessoa(string nome = "", int ano = 0){
        this->nome = nome;
        this->ano = ano;
    }
    friend class stPessoa;
};


class stPessoa : public Pessoa{
    double dinheiro;
public:
    stPessoa(string _name){
        this->nome = _name;
    }
    string getName(){
        return this->nome;
    }
};


int main()
{
    stPessoa x = stPessoa("Rau");

    cout << x.getName() << endl;
    return 0;
}

