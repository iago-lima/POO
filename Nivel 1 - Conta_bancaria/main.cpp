#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

struct Operacao{
    string descricao;
    float valor;
    Operacao(string descricao = "", float valor = 0){
        this->descricao = descricao;
        this->valor = valor;
    }
};

class Conta{
private:
    int id;
    float saldo{0};
    vector<Operacao> extrato;
public:
    Conta(int id = 0){
        this->id = id;
    }

    float getSaldo(){
        return this->saldo;
    }

    int getId(){
        return this->id;
    }

    void setId(int id){
        this->id = id;
    }

    bool saque(float valor){
        if((this->saldo < valor) || (valor < 0)){
            return false;
        }
        this->saldo -= valor;
        this->extrato.push_back(Operacao("Saque: -", valor));

        return true;
    }

    bool deposito(float valor){
        if(valor < 1){
            return false;
        }
        this->saldo += valor;
        this->extrato.push_back(Operacao("Deposito: +", valor));
        return true;
    }
    string getExtrato(){
        stringstream ss;
        for (Operacao vetor : extrato){
            ss << vetor.descricao << " " << vetor.valor << endl;
        }
        return ss.str();
    }

    string getExtratoN(int n){
        stringstream ss;
        int tam = (int)(extrato.size()) - n;
        for(; tam < (int)extrato.size(); tam++){
            ss << extrato[tam].descricao << " " << extrato[tam].valor << endl;
        }
        return ss.str();
    }
};

void inicializar(Conta& conta){
    conta.deposito(400);
    conta.deposito(300);
    conta.deposito(200);
    conta.deposito(100);
    conta.saque(40);
    conta.saque(30);
    conta.saque(20);
    conta.deposito(100);
    conta.saque(300);
}

int main(){

    Conta conta;
    string op;
    cout << "digite help" << endl;

    while(op != "fim"){
        cin >> op;

        if(op == "help"){
            stringstream menu;
            menu << "iniciar _id" << endl
                 << "saldo" << endl
                 << "saque _valor" << endl
                 << "deposito _valor" << endl
                 << "extrato" << endl
                 << "extratoN _n" << endl
                 << "fim" << endl;

            cout << menu.str();
        }

        else if(op == "iniciar"){

            conta = Conta(read<int>());
            inicializar(conta);
            cout << "ok" << endl;
        }
        else if(op == "saldo"){
            cout << conta.getSaldo() << endl;
        }
        else if(op == "deposito"){
            cout << (conta.deposito(read<float>())? "ok" : "erro") << endl;
        }
        else if(op == "saque"){
            cout << (conta.saque(read<float>())? "ok" : "erro") << endl;
        }
        else if(op == "extrato"){
            cout << conta.getExtrato();
            cout << "Saldo Atual: " << conta.getSaldo() << endl;
        }
        else if(op == "extratoN"){
            cout << conta.getExtratoN(read<int>());
            cout << "Saldo Atual: " << conta.getSaldo() << endl;
        }
    }
}
