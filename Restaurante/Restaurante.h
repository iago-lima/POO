#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Ingrediente{
    string idIngr;
    float valor{0};
    Ingrediente(string id = "", float _valor = 0.0){
        idIngr = id;
        valor = _valor;
    }
    string getIdIngr(){
        return idIngr;
    }
    float getValor(){
        return valor;
    }
    void setValor(float newValor){
        valor = newValor;
    }

    string toStringIngr(){
        stringstream ss;
        ss << idIngr << ", Valor: " << valor << endl;

        return ss.str();
    }

};

class Produto{
protected:
    string idProd;
    vector<Ingrediente*> ingredientes;
    float valor{0};

public:
    Produto(string id = "", float _valor = 0.0){
        idProd = id;
        valor = _valor;
    }

    void setIngredientes(Ingrediente *ingre){
        ingredientes.push_back(ingre);
        valor += ingre->getValor();
    }

    float getValor(){
        return valor;
    }
    void setValor(float newValor){
        valor = newValor;
    }

    string getIdProd(){
        return idProd;
    }

    string toStringProd(){
        stringstream ss;
         ss << "Produto: " << idProd << " R$: " << valor << endl;
         ss << "Ingredientes: " << endl;
         for(auto elemento : ingredientes){
             ss << ".. " << elemento->getIdIngr() << endl;
         }
         return ss.str();
    }
};

class Venda{
    Produto * prodVen;
    float div;
public:
    Venda(Produto * _prod, float _div) {
        prodVen = _prod;
        div = _div;
    }

    Produto *getProdVen(){
        return prodVen;
    }
    float getDivd(){
        return div;
    }
};

class Cliente;
class UserConta{
    Cliente * cliente;
    vector<Venda> vendas;
public:
    UserConta(Cliente * cli){
        cliente = cli;
    }
    vector<Venda> getVendas(){
        return vendas;
    }
    void setVendas(Venda value){
        vendas.push_back(value);
    }
    string userIdCli();
};

class Mesa{
    string idMesa;
    int clientesNaMesa{0};
    int qtdCad{0};
    float valorAPagar{0};
    vector<UserConta> contas;

public:
    Mesa(string id = "", int _qtdCad = 0){
        idMesa = id;
        qtdCad = _qtdCad;
    }

    int getClieNaMesa(){
        return clientesNaMesa;
    }

    string getIdMesa(){
        return idMesa;
    }

    void comprar(Produto * produto, vector<Cliente*> clis);

    bool addCli(Cliente * cli){
        if(((int)contas.size()) == qtdCad)
            return false;
        contas.push_back(UserConta(cli));
        clientesNaMesa++;
        return true;
    }

    float valordoCliente(Cliente * cli);

    void setValorAPagar(float valor){
        valorAPagar -= valor;
        clientesNaMesa -= 1;
    }

    string toStringMesa();

    friend class Cliente;
};

class Cliente{
    string idCliente;
    vector<Mesa*> mesaCli;
public:
    Cliente(string id = ""){
        idCliente = id;
    }

    string getIdCliente(){
        return idCliente;
    }

    void sentar(Mesa * _mesa){
        for(Mesa * ele : mesaCli){
            if(ele->getIdMesa() == _mesa->getIdMesa())
                throw string("\nCliente já está nessa mesa!\n");
        }
        if(_mesa->addCli(this)){
            mesaCli.push_back(_mesa);
        }else{
            throw string("\nVagas indisponíveis para essa mesa!\n");
        }
    }

    string pagarESair(Mesa * idMesa){
        Mesa * mesa = nullptr;
        stringstream ss;
        float valorTotal = 0;
        for(Mesa * element: mesaCli){
            if(element->getIdMesa() == idMesa->getIdMesa()){
                mesa = element;
            }
        }
        if(mesa == nullptr)
            throw string("Cliente não está nessa mesa!\n");

        for(int i = 0; i < (int) mesa->contas.size(); i++){
            if(mesa->contas[i].userIdCli() == this->getIdCliente()){
                vector<Venda> vendasAux = mesa->contas[i].getVendas();
                ss << "Compras Realizadas:" << endl;
                if(((int) vendasAux.size()) != 0){
                    for(Venda ele : vendasAux){
                        float aPagar = (ele.getProdVen()->getValor()/ele.getDivd());
                        ss << "1/" << ele.getDivd() << " " << ele.getProdVen()->getIdProd() <<
                              " = " << aPagar << endl;
                        valorTotal += aPagar;
                        mesa->setValorAPagar(aPagar);
                    }
                }
                mesa->contas.erase(mesa->contas.begin() + i);
                ss << "Total: " << valorTotal;
                for(int j = 0; j < (int) mesaCli.size(); j++){
                    if(mesaCli[j]->getIdMesa() == mesa->getIdMesa()){
                        mesaCli.erase(mesaCli.begin() + j);
                        return ss.str();
                    }
                }
            }
        }
        return "";
    }

    string toStringCli(){
        stringstream ss;
        ss << "Cliente: " << idCliente;
        ss << "\nMesa: " << endl;
        for(Mesa* elemento: mesaCli)
            if(elemento != nullptr){
                ss << "[ ";
                ss << elemento->getIdMesa() << " Dev: ";
                ss << elemento->valordoCliente(this);
                ss << "]" << endl;
            }
        return ss.str();

    }
    friend class Mesa;
};

void Mesa::comprar(Produto *produto, vector<Cliente*> clis){
    int cont = 0, pessoa = -1;
    for(int i = 0; i < (int) clis.size(); i++)
        for(UserConta ele : contas){
            if(clis[i]->getIdCliente() == ele.userIdCli())
                cont++;
            else {
                pessoa = i;
            }

    }
    if(cont != (int) clis.size())
        throw "Cliente " + clis[pessoa]->getIdCliente() + " não está ná mesa!\n";


    for(UserConta &ele : contas){
        for(Cliente * ele2 : clis){
            if(ele.userIdCli() == ele2->getIdCliente()){
                ele.setVendas(Venda(produto, (int) clis.size()));
            }
        }
    }
    valorAPagar += produto->getValor();
}

float Mesa::valordoCliente(Cliente *cli){
    float valor = 0;
    for(UserConta ele : contas){
        if(ele.userIdCli() == cli->getIdCliente()){
            vector<Venda> vendAux = ele.getVendas();
            for(Venda ele2 : vendAux){
                valor += (ele2.getProdVen()->getValor() / ele2.getDivd());
            }
        }
    }
    return valor;
}

string Mesa::toStringMesa(){
    stringstream ss;
    ss << "Mesa:" << idMesa << " QtdCade: " << qtdCad;
    ss << "\nClientes na Mesa: " << endl;

    ss << "[ ";
    for(UserConta ele : contas){
        ss << ele.userIdCli() << " ";
    }
    ss << "]";
    ss << "\nValor total: R$ " << valorAPagar;
    return ss.str();
}

string UserConta::userIdCli(){
    return cliente->getIdCliente();
}

#endif // RESTAURANTE_H
