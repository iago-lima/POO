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

struct Transacao{
    int id;
    string nome;
    float valor;
    Transacao(int _id = 0, string _nome = "", float _valor = 0){
        id = _id;
        nome = _nome;
        valor = _valor;
    }
};

class Sistema{
    int nextId{0};
    vector<Transacao> transacoes;
    float balanco{0.0f};
  public:
    Sistema(float _balanco = 0){
        balanco = _balanco;
    }

    bool addTran(string _nome, float _valor){
        if(_valor < 0){
            if(((-1) * _valor) > balanco){
                return false;
            }
            transacoes.push_back(Transacao(nextId, _nome, _valor));
            balanco += _valor;
            nextId += 1;
            return true;
        }else{
            transacoes.push_back(Transacao(nextId, _nome, _valor));
            balanco += _valor;
            nextId += 1;
            return true;
        }
    }

    bool rmTran(int _id){
        for(int i = 0; i < (int) transacoes.size(); i++){
            if(transacoes[i].id == _id){
                balanco -= transacoes[i].valor;
                transacoes.erase(transacoes.begin() + i);
                return true;
            }
        }
        return false;

    }

    string showTran(){
        stringstream ss;
        ss << "Lista de Transações:" << endl;
        for(Transacao elemento : transacoes){
            ss << elemento.id << " " << elemento.nome << " " << elemento.valor << endl;
        }
        return ss.str();

    }

    string showCliente(string _nome){
        stringstream ss;
        float saldo = 0;
        ss << "Lista de transações de " << _nome << endl;
        for(Transacao elemento : transacoes){
            if(elemento.nome == _nome){
                ss << elemento.id << " " << elemento.nome << " " << elemento.valor << endl;
                saldo += elemento.valor;
            }
        }
        ss << "Saldo: " << saldo << endl;
        return ss.str();
    }

    int contarClientes(){
        vector<string> aux;
       int i = -1;
        int x = 0;

        for(Transacao elemento : transacoes){
            if(i == -1){
                aux.push_back(elemento.nome);
            }
            x = 0;
            for(i = 0; i < (int) aux.size(); i++){
                if(elemento.nome == aux[i]){
                    x += 1;
                }
            }

            if(x == 0){
                aux.push_back(elemento.nome);
            }
        }
        return (int) aux.size();
    }

    float fazerBalanco(){
        return balanco;
    }

};

void inicializar(Sistema& sistema){
    sistema.addTran("Felipe", 1000);
    sistema.addTran("Felipe", -2000);
    sistema.addTran("Felipe", 500);
    sistema.addTran("Iago", -100);
    sistema.addTran("Iury", -500);
}

int main(){
    Sistema sistema;
    string op = "";

    cout << "Digite o comando ou help: ";
    while(op != "fim"){
        cin >> op;
        if(op == "help"){
            cout << "iniciar $valor" << endl
                 << "addTran $nome $valor" << endl
                 << "rmTran $id" << endl
                 << "showTran" << endl
                 << "showCli $nome" << endl
                 << "contarCli" << endl
                 << "balanco" << endl << endl;
        }

        if(op == "iniciar"){
            float x = read<float>();
            sistema = Sistema(x);
            inicializar(sistema);
            cout << "Sistema iniciado com " << x << " Reais." << endl;
        }
        if(op == "addTran"){
            string nome = read<string>();
            float valor = read<float>();
            cout << (sistema.addTran(nome, valor)? "OK" : "Não há dinheiro para a transação.") << endl;
        }
        if(op == "showTran"){
            cout << sistema.showTran() << endl;
        }
        if(op == "rmTran"){
            cout << (sistema.rmTran(read<int>())? "OK" : "Transação não encontrada") << endl;
        }
        if(op == "showCli"){
            cout << sistema.showCliente(read<string>()) << endl;
        }
        if(op == "balanco"){
            cout << "Balanço: " << sistema.fazerBalanco() << endl;
        }
        if(op == "contarCli"){
            cout << "Existem " << sistema.contarClientes() << " clientes diferentes no Sistema." << endl;
        }


    }

    return 0;
}
