// Ordenar vetor de clientes
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int controle = 0;

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
    int num;
    float saldo{10};
    bool ativa{true};
    vector<Operacao> extrato;
public:
    Conta(int _num = 0){
        this->num = _num;
    }

    float getSaldo(){
        return this->saldo;
    }

    int getNumero(){
        return this->num;
    }

    void setNumero(int _num){
        this->num = _num;
    }
    bool setSaldo(float valor){
        this->saldo += valor;
        return true;
    }
    bool setExtrato(float valor, int op){
        op ? this->extrato.push_back(Operacao("Deposito +", valor)) : this->extrato.push_back(Operacao("Saque -", valor));
        return true;
    }

    void cliTransf(int _conta, float _valor, string dePara){
        stringstream ss;
        ss << "Transferencia " << dePara << _conta <<" no valor de ";
        this->extrato.push_back(Operacao(ss.str(), _valor));
    }

    string getExtrato(){
        stringstream ss;
        for(Operacao vetor : extrato){
            ss << vetor.descricao << vetor.valor << endl;
        }
        return ss.str();
    }

    string getExtratoN(int n){
        stringstream ss;
        int tam = (int)(extrato.size()) - n;
        for(; tam < (int)extrato.size(); tam++){
            ss << extrato[tam].descricao << extrato[tam].valor << endl;
        }
        return ss.str();
    }

    void setAtiva(){
        this->ativa = !this->ativa;
    }

    bool getAtiva(){
        return this->ativa;
    }
};

class Cliente{
    string cpf;
    vector<Conta> contas;
  public:
    Cliente(string _cpf = ""){
        this->cpf = _cpf;
    }

    string getCpf(){
        return this->cpf;
    }

    vector<Conta> &getConta(){
        return this->contas;
    }

    void setConta(int _num){
        contas.push_back(Conta(_num));
    }

    int endConta(int _numero){
        for(Conta& elemento : contas){
            if(elemento.getNumero() == _numero){
                if(elemento.getSaldo() > 0){
                   return -3; // Só pode encerrar com saldo zerado
                }if((elemento.getAtiva()) == (false)){
                    return -2;
                }
                elemento.setAtiva();
                return _numero;
            }
        }
        return -1;
    }
    bool sacar(int conta, float valor){
        for(Conta& elemento: contas){
                if((elemento.getNumero() == conta) && (elemento.getSaldo() >= valor) && (valor > 0)){
                    if(elemento.getAtiva()){
                        elemento.setSaldo(((-1)*valor));
                        elemento.setExtrato(valor,0);
                        return true;
                    }else{
                        return false;
                    }
                }
        }
        return false;
    }
    string getSaldo(int conta){
        stringstream ss;
        for(Conta elemento: contas){
                 if(elemento.getNumero() ==  conta){
                     if(elemento.getAtiva()){
                        ss <<"Saldo: " << elemento.getSaldo();
                        return ss.str();
                     }else{
                        return "Conta DESATIVADA.";
                     }
                }
        }
        ss << "Conta inválida";
        return ss.str();
    }
    bool depositar(int conta, float valor){
        for(Conta& elemento: contas){
                if((elemento.getNumero() == conta) && (valor > 0)){
                    if(elemento.getAtiva()){
                        elemento.setSaldo(valor);
                        elemento.setExtrato(valor,1);
                        return true;
                    }else{
                        return false;
                    }
                }
            }
        return false;
    }
    string extrato(int conta){
        stringstream ss;
        for(Conta elemento: contas){
            if(elemento.getNumero() == conta){
                if(elemento.getAtiva()){
                    ss << "Extrato:\n" << elemento.getExtrato() << endl;
                    return ss.str();
                }else{
                    return "Conta DESATIVADA.\n";
                }
            }
        }
        ss << "Conta não encontrada." << endl;
        return ss.str();
    }
    string extratoN(int conta, int n){
        stringstream ss;
        for(Conta elemento: contas){
            if(elemento.getNumero() == conta){
                if(elemento.getAtiva()){
                    ss << "ExtratoN:\n" << elemento.getExtratoN(n);
                    return ss.str();
                }
                else{
                    return "Conta DESATIVADA.\n";
                }
            }
        }
        ss << "Conta não encontrada." << endl;
        return ss.str();
    }

    vector<int> numeroContas(){
        vector<int> aux;
            for(Conta elemento : contas){
                aux.push_back(elemento.getNumero());
            }
        return aux;
    }
};

bool comparaCli(Cliente a, Cliente b){
    return a.getCpf() < b.getCpf();
}

class Agencia{
    vector<Cliente> clientes;
  public:
    Agencia(){}

    int abrirConta(string _cpf){
        for(Cliente elemento : clientes){
            if(elemento.getCpf() == _cpf){
                if(elemento.getConta().size() >= 2){
                    int x = 0;
                    vector<Conta> contas = elemento.getConta();
                    for(Conta elemento2 : contas){
                        if(elemento2.getAtiva() == true){
                            x += 1;
                            if(x == 2){
                                return -2;
                            }
                        }
                    }
                }
            }
        }
        for(Cliente& elemento : clientes){
            if(elemento.getCpf() == _cpf){
                elemento.setConta(controle);
                int numeroConta = controle;
                controle += 1;
                return numeroConta;
            }
        }
        return -1;
    }


    bool addCliente(string _cpf){
        for(Cliente elemento : clientes){
            if(elemento.getCpf() == _cpf){
                return false;
            }
        }
        clientes.push_back(Cliente(_cpf));
        abrirConta(_cpf);
        return true;
    }

    string showAllCliente(){
        stringstream ss;
        int x = 1;
        vector<Conta> contas;
        std::sort(clientes.begin(), clientes.end(), comparaCli);
        for(Cliente elemento : clientes){
            contas = elemento.getConta();
            vector<int> contasAti;
            for(Conta elemento2 : contas){
                if(elemento2.getAtiva()){
                    contasAti.push_back(elemento2.getNumero());
                }
            }
            ss << x << " - " << "CPF: " << elemento.getCpf() << " | Contas:" << " [ ";
            for(int i = 0; i < (int)contasAti.size(); i++){
                ss << contasAti[i] << " ";
            }
            ss << "]" << endl;
            x += 1;
        }
        return ss.str();
    }

    Cliente * Login(string _cpf){
        for(Cliente& elemento : clientes){
            if(elemento.getCpf() == _cpf){
                return &elemento;
            }
        }
        return nullptr;
    }


    string show(string _cpf){
        stringstream ss;
        float saldoT = 0;
        ss << "Cliente: " << _cpf << endl;
        vector<Conta> contas;
        for(Cliente elemento : clientes){
            if(elemento.getCpf() == _cpf){
                contas = elemento.getConta();
                for(Conta elemento2 : contas){
                    saldoT += elemento2.getSaldo();
                    ss << "Conta: " << elemento2.getNumero() << ", "
                       << "Saldo: " << elemento2.getSaldo() << ", "
                       << "Status: " << elemento2.getAtiva() << endl;
                }
                ss << "Saldo Total: " << saldoT << endl;
                return ss.str();
                }

            }
        return "Error!";
        }

    bool tranferencia(int _minha, int _outra, float _valor){
        int cont = 0, cont2 = 0;
        //Pega todas as contas de todos os clientes - ESSE TA CERTO
        vector<Conta> contaAux;
        vector<int> nContas;
        for(Cliente elemento : clientes){
            contaAux = elemento.getConta();
            for(Conta elemento2 : contaAux){
                nContas.push_back(elemento2.getNumero());
            }
        }
        // Verificando se as contas existem - TA CERTO
        for(int i = 0; i < (int) nContas.size(); i++){
            if(nContas[i] == _minha){
                cont += 1;
            }
            if(nContas[i] == _outra){
                cont2 += 1;
            }
        }
        if((cont == 0) || (cont2 == 0)){
            return false;
        }
        //Pegando os clientes das determinadas contas - TA PRESTANDO
        vector<string> cpfs;
        for(Cliente elemento : clientes){
            vector<Conta> contas = elemento.getConta();
            for(Conta elemento2 : contas){
                if(elemento2.getNumero() == _minha){
                    if(!elemento2.getAtiva()){
                        return false;
                    }
                    cpfs.push_back(elemento.getCpf());
                }
                if(elemento2.getNumero() == _outra){
                    if(!elemento2.getAtiva()){
                        return false;
                    }
                    cpfs.push_back(elemento.getCpf());
                }
            }
        }
        // Fazendo a transferencia
        for(Cliente& elemento : clientes){
            if(elemento.getCpf() == cpfs[0]){
                for(Conta& elemento2 : elemento.getConta()){
                    if(elemento2.getNumero() == _minha){
                        if(_valor > elemento2.getSaldo()){
                            return false;
                        }
                        elemento2.setSaldo((-1)* _valor);
                        elemento2.cliTransf(_outra, _valor, "para ");
                    }
                }
            }
            if(elemento.getCpf() == cpfs[1]){
                for(Conta& elemento2 : elemento.getConta()){
                    if(elemento2.getNumero() == _outra){
                        elemento2.setSaldo(_valor);
                        elemento2.cliTransf(_minha, _valor, "de ");
                    }
                }

            }
        }
        return true;
    }
};

void inicializar(Agencia& agencia){
    agencia.addCliente("123");
    agencia.addCliente("321");
    agencia.addCliente("456");
    agencia.abrirConta("123");
}


int main(){

    Agencia agen;
    Cliente * cliente = nullptr;
    string op = "";
    inicializar(agen);
    while(op != "fim"){
        cout << "Digite o comando ou help: ";
        cin >> op;
        if(op == "help"){
            cout << "Comandos:" << endl
                 << "login $cpf" << endl
                 << "logout" << endl
                 << "showAll" << endl
                 << "addCli $cpf" << endl
                 << "abrirConta $cpf" << endl
                 << "endConta $conta" << endl
                 << "sacar $conta $valor" << endl
                 << "depositar $conta $valor" << endl
                 << "saldo $conta" << endl
                 << "extrato $conta" << endl
                 << "extratoN $conta $n" << endl
                 << "show" << endl
                 << "transf $contaDe $contaPara $valor" << endl
                 << "fim" << endl <<endl;

        }

        if(op == "login"){
            string _cpf;
            cin >> _cpf;
            cliente = agen.Login(_cpf);
            if(cliente == nullptr){
                cout << "Erro de login" << endl;
            }else{
                cout << "Sucesso" << endl;
            }
        }
        if(op == "logout"){
            if(cliente != nullptr){
                cliente = nullptr;
                cout << "Logout efetuado" << endl;
            }else{
                cout << "Ninguem logado" << endl;
            }
        }

        if(op == "showAll"){
            cout << agen.showAllCliente() << endl;
        }
        if(op == "addCli"){
            if(agen.addCliente(read<string>())){
                cout << "Cliente Add!" << endl;
            }else
                cout << "Error ao adicionar cliente, CPF duplicado!" << endl;
        }
        if(op == "abrirConta"){
            int x;
            x = agen.abrirConta(read<string>());
            if(x >= 0){
                cout << "Conta " << x << " aberta." << endl;
            }else if(x == -1){
                cout << "CPF não existe!" << endl;
            }else if(x == -2){
                cout << "Limite de contas atingido!" << endl;
            }
        }

        if(op == "endConta"){
            if(cliente == nullptr){
                cout << "Ninguem logado!" << endl;
            }else {
                int x = cliente->endConta(read<int>());
                if(x >= 0){
                    cout << "Conta " << x << " encerrada!" << endl;
                }else if(x == -1){
                    cout << "Conta invalida." << endl;
                }else if(x == -2){
                    cout << "Conta ja esta incerrada." << endl;
                }else if(x == -3){
                    cout << "Saldo positivo." << endl;
                }
            }
        }
        if(op == "show"){
            if(cliente == nullptr){
                cout << "Ninguem logado!" << endl;
            }else {
                cout << agen.show(cliente->getCpf()) << endl;
            }
        }
        if(op == "sacar"){
            if(cliente != nullptr){
                bool aux = true;
                int aux1 = 0;
                float aux2 = 0;
                cin >> aux1;
                cin >> aux2;
                aux = cliente->sacar(aux1, aux2);
                if(aux == true){
                    cout << "Saque realizado com sucesso." << endl;
                }else if(aux == false){
                    cout << "Saque não realizado. Conta/Valor inválido ou Conta DESATIVADA." << endl;
                }
            }else{
                cout << "Erro Saque - Cliente não logado." << endl;
            }
        }
        if(op == "saldo"){
            if(cliente != nullptr){
               cout << cliente->getSaldo(read<int>()) << endl;

            }else{
                cout << "Erro Saldo - Cliente não logado." << endl;
            }
        }
        if(op == "depositar"){
            if(cliente != nullptr){
                bool aux = true;
                int aux1 = 0;
                float aux2 = 0;
                cin >> aux1;
                cin >> aux2;
                aux = cliente->depositar(aux1, aux2);
                if(aux == true){
                    cout << "Deposito realizado com sucesso." << endl;
                }else if(aux == false){
                    cout << "Deposito não realizado. Conta/Valor inválido ou Conta DESATIVADA." << endl;
                }
            }else{
                cout << "Erro deposito - Cliente não logado." << endl;
            }


        }
        if(op == "extrato"){
            if(cliente != nullptr){
                string ss;
                ss = cliente->extrato(read<int>());
                cout << ss;
            }else{
                cout << "Erro extrato - Cliente não logado." << endl;
            }
        }
        if(op == "extratoN"){
            if(cliente != nullptr){
                string ss;
                int conta;
                int n;
                cin >> conta >> n;
                ss = cliente->extratoN(conta,n);
                cout << ss;
            }else{
                cout << "Erro extratoN - Cliente não logado." << endl;
            }
        }
        if(op == "transf"){
            if(cliente == nullptr){
                cout << "Error ao transferir - Cliente não logado" << endl;
            }else{
                int _minha = read<int>();
                int _outra = read<int>();
                float _valor = read<float>();
                bool result = agen.tranferencia(_minha, _outra, _valor);
                if(!result){
                    cout << "ERRO - Contas invalidas/saldo insuficiente ou contas DESATIVADAS!" << endl;
                }else{
                    cout << "Transferencia efetuada." << endl;
                }
            }
        }

    }

}
