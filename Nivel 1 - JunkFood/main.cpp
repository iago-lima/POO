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

class Espiral{
  public:
    string nome;
    int qtd;
    float valor;

    Espiral(string _nome = "", int _qtd = 0, float _valor = 0.0){
        this->nome = _nome;
        this->qtd = _qtd;
        this->valor = _valor;
    }

    void setNome(string _nome){
        this->nome = _nome;
    }
    void setQtd(int _qtd){
        this->qtd = _qtd;
    }
    void setValor(float _valor){
        this->valor = _valor;
    }

    string getNome(){
        return this->nome;
    }
    int getQtd(){
        return this->qtd;
    }
    float getValor(){
        return this->valor;
    }


};

class JunkFood{
  public:
    vector<Espiral> espirais;
    float saldo{0.0};
    float lucro{0.0};
    int qtdProd{0};

    JunkFood(int _qtd = 0, int _qtdProd = 0):
        espirais(_qtd)
    {
        this->qtdProd = _qtdProd;
    }

    /*///////////////////////////////////*/
    bool inserirDin(float _valor){
        if (_valor > 0){
            this->saldo += _valor;
            return true;
        }
        return false;
    }

    /*///////////////////////////////////*/
    float getSaldo(){
        return this->saldo;
    }

    /*///////////////////////////////////*/
    float getTroco(){
        float x = this->saldo;
        this->saldo = 0;
        return x;
    }
    /*///////////////////////////////////*/
    int alterarProd(int _id, string _nome, int _qtd, float _valor){
        if(((_id > (int)espirais.size() -1)) || (_nome == "") || (_qtd <= 0) || (_valor <= 0)){
            return -1;
        }else if(_qtd > this->qtdProd){
            return -2;
        }else{
            espirais[_id].setNome(_nome);
            espirais[_id].setQtd(_qtd);
            espirais[_id].setValor(_valor);
            return 1;
        }

    }
    /*///////////////////////////////////*/
    string comprar(int _id){
        stringstream ss;

        if((_id > (int) espirais.size()) || (espirais[_id].getQtd() <= 0)){
            ss << "-1";
            return ss.str();
        }
        if((this->saldo) < (espirais[_id].getValor())){
            ss << "-2";
            return ss.str();
        }
        this->saldo -= espirais[_id].getValor();
        this->lucro += espirais[_id].getValor();
        espirais[_id].setQtd((espirais[_id].getQtd() - 1));
        ss << espirais[_id].nome;
        return ss.str();

    }
    /*//////////////////////////////////*/
    string statusMaq(){

        stringstream ss;
        ss << "Saldo: " << this->saldo << endl
           << "Lucro: " << this->lucro << endl
           << "Quantidade max. por espiral: " << this->qtdProd << endl;
        int aux = 0;
        for(auto sel : espirais){
            ss << "ind: " << aux << " "
               << "nome: " << sel.nome << " "
               << "qtd: " << sel.qtd << " "
               << "valor: " << sel.valor << endl;
            aux += 1;
        }
        return ss.str();
    }


};

void inicializar(JunkFood& maquina){
    maquina.inserirDin(10);
    maquina.alterarProd(0, "Toddy", 2, 2.5);
    maquina.alterarProd(1, "Pastel", 2, 3);
}


int intUsuario(JunkFood& maquina){
    string op;

    while (op != "fim") {

        cout << "Digite o Comando ou help: ";
        cin >> op;

        if(op == "help"){
            cout << "\nComandos:" << endl
                 << "iniciar $qtd $qtdProd" << endl
                 << "inserirDin $valor" << endl
                 << "saldo" << endl
                 << "troco" << endl
                 << "comprar $id" << endl
                 << "alterarProd $id $nome $qtd $valor" << endl
                 << "statusMaq" << endl
                 << "fim" << endl;
        }

        if(op == "iniciar"){
            int qtd, qtdProd;
            qtd = read<int>();
            qtdProd = read<int>();
            maquina = JunkFood(qtd, qtdProd);
            inicializar(maquina);
            cout << "Maquina criada!" << endl;
        }

        if(op == "inserirDin"){
            float x;
            cin >> x;
            if(maquina.inserirDin(x)){
                cout << "Suceso!"<< endl;
            }else{
                cout << "Erro!" << endl;
            }
        }

        if(op == "saldo"){
           cout << maquina.getSaldo() << " Reais." << endl;
        }

        if(op == "troco"){
            cout << "Você retirou " << maquina.getTroco() << " Reais." << endl;
        }

        if(op == "comprar"){
            int x = read<int>();
            string retorno = "";
            retorno = maquina.comprar(x);
            if(retorno == "-1"){
                cout << "ERRO: Produto não existe!" << endl;
            }else if(retorno == "-2"){
                cout << "ERRO: Saldo Insuficiente!" << endl;
            }else{
                cout << "Você comprou um " << retorno << endl;
            }
        }

        if(op == "alterarProd"){
            int id = read<int>();
            string nome = read<string>();
            int qtd = read<int>();
            float valor = read<float>();
            int res = maquina.alterarProd(id, nome, qtd, valor);
            if (res == 1){
                cout << "Produto Inserido!" << endl;
            }else if(res == -2){
                cout << "ERRO: Quantidade maxima de produto excedida!" << endl;
            }else if(res == -1){
                cout << "ERRO: Informações de produto invalida!" << endl;
            }

        }

        if(op == "statusMaq"){
            cout << "Status:\n" << maquina.statusMaq();
        }

    }


    return 0;
}
int main(){
    JunkFood maquina;
    intUsuario(maquina);
}
