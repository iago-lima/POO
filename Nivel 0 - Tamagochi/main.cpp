// Modificando conteudo do arquivo da aula 02
// Criação do Método Cura

#include <iostream>

using namespace std;

struct Comida{
    string nome;
    int vnut;
    Comida(string _nome, int _vnut){
        nome = _nome;
        vnut = _vnut;
    }
};

struct Cura{
    string nome;
    int vCura;
    Cura(string _nome, int _vCura){
        nome = _nome;
        vCura = _vCura;
    }
};


struct Tamagochi{
    int idade;
    string nome;
    int fome;
    bool vivo;
    int fomeMax {10};
    int vida;
    int saude;

    Tamagochi(string nome){
        this->nome = nome;
        idade = 0;
        fome = 0;
        vivo = true;
        saude = 10;
        vida = 10 + rand() % 5;
    }

    virtual void levarDano(int value){
        this->vida -= value;
        if(vida < 0)
            vivo = false;
    }


    void comer(Comida comida){
        if(!vivo){
            cout << "Morto nao come";
            return;
        }
        this->fome -= comida.vnut;
        if(fome < 0)
            fome = 0;
    }

    void curar(Cura cura){
        if(!vivo){
            cout << "Morto não pode ser curado!" << endl;
            return;
        }
        this->saude += cura.vCura;
        if(saude > 10){
            saude = 10;
        }
    }

    void passarTempo(){
        fome += 1;
        if(fome > fomeMax){
            fome = 10;
            this->saude -= 1;
        }
        if(saude < 0){
            cout << "Morreu :/" << endl;
            vivo = false;
            exit(0);
        }
    }

    void envelhecer(){
        if(!vivo){
            cout << "Morto nao envelhece" << endl;
            return;
        }
        idade += 1;
        if(idade > 5){
            vivo = false;
            cout << nome << "Morreeeeeeeeeu" << endl;
        }

    }

    void show(){
        cout << "Nome: " << this->nome
             << "\nFome: " << this->fome
             << "\nVida: " << this->vida
             << "\nIdade: " << this->idade
             << "\nSaúde: " << this->saude << endl;
    }
};


#include <cstdlib>
#include <ctime>
#include <unistd.h>


int main(){

    Comida comida1("Pastel", 3);
    Comida comida2("Macarronada", 5);
    Cura cura1("Pilula", 3);
    Cura cura2("Vacina", 7);

    srand(time(NULL));
    Tamagochi t1 = Tamagochi("Axuaxua");

    t1.show();
    sleep(1);

    cout <<"\nPassaram-se 5h!\n" << endl;
    for(int i = 0; i < 5; i++){
        t1.passarTempo();
    }
    t1.show();
    sleep(1);

    cout << "\nComeu: " << comida1.nome << "\nValor: " << comida1.vnut <<"\n" << endl;

    t1.comer(comida1);
    t1.show();
    sleep(1);

    cout <<"\nPassaram-se 11h!\n" << endl;
    for(int i = 0; i < 11; i++){
        t1.passarTempo();
    }
    t1.show();
    sleep(1);

    cout << "\nTomou Ramedio: " << cura1.nome << "\nValor: " << cura1.vCura <<"\n" << endl;
    cout << "Comeu: " << comida2.nome << "\nValor: " << comida2.vnut <<"\n" << endl;
    t1.comer(comida2);
    t1.curar(cura1);
    t1.envelhecer();

    t1.show();
    sleep(1);


    return 0;
}

