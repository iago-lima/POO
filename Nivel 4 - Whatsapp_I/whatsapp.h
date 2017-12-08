#ifndef WHATSAPP
#define WHATSAPP

#include <sstream>
#include <iostream>
#include "poo_aux.h"

using namespace std;
using namespace poo;

class Zap{
    string userId;
    string msg;
public:
    Zap(string _userId = "", string _msg = ""){
        userId = _userId;
        msg = _msg;
    }
    string getUserId(){
        return userId;
    }

    string toStringZap(){
        stringstream ss;
        ss << "[" << userId;
        ss << ": " << msg << "]" << endl;

        return ss.str();
    }
};

class Chat; //declaração que existe
class Registro;

class User{
    map<string, Chat*> lista_chat;
    string userId;
public:
    User(string _userId = ""){
        userId = _userId;
    }

    vector<string> getChats(){
        return poo::map_keys(lista_chat);
    }

    string getOverview();

    void assertChat(string _chatId){
        if(lista_chat.count(_chatId) == 0)
            throw "Usuário não faz parte do grupo " + _chatId;
    }

    void invite(string _chatId, User * _user);

    void leave(string _chatId);

    void sendZap(string _msg, string _chatId);

    string toStringUser(){
        return this->userId;
    }

    friend class Chat;
};

class Registro{
    User * user;
    int underCount{0};
public:
    Registro(User * _user = nullptr){
        user = _user;
    }
    void underCountPlus(int qtd){
        underCount += qtd;
    }
    int getUnderCount(){
        return this->underCount;
    }
    void setUnderCount(int valor){
        underCount = valor;
    }
};

class Chat{
    string chatId;
    vector<Zap> lista_zap;
    map<string, Registro> lista_reg;
    //string systemUserName{"System"};
public:
    Chat(string _chatId = ""){
        chatId = _chatId;
    }

    vector<string> getUsers(){
        vector<string> users;
        for(auto par : lista_reg)
            users.push_back(par.first);
        return users;
    }

    bool addFirstUser(User * _chatCreator){
        if(((int) lista_reg.size()) != 0)
            throw "Erro ao adicionar o primeiro Usuário.\n";

        lista_reg[_chatCreator->userId] = Registro(_chatCreator);
        _chatCreator->lista_chat[this->chatId] = this;
        return true;
    }

    void assertUser(string _user){
        if(!lista_reg.count(_user))
            throw _user + " não existe!";
    }

    void deliverZap(Zap _zap){
        if(_zap.getUserId() == "System"){
            lista_zap.push_back(_zap);
            for(auto user : lista_reg){
                user.second.underCountPlus(1);
            }
        }else{
            assertUser(_zap.getUserId());
            lista_zap.push_back(_zap);
            for(auto & user : lista_reg){
                if(user.first != _zap.getUserId()){
                    user.second.underCountPlus(1);
                }
            }
        }
    }

    int getUnreadCount(string _userId){
        assertUser(_userId);
        Registro aux = lista_reg[_userId];
        return aux.getUnderCount();
    }

    vector<Zap> getUnread(string _userId){
        assertUser(_userId);
        vector<Zap> retorno;
        int tmhVetZap = (int) lista_zap.size();
        int qtdNLidas = getUnreadCount(_userId);
        Registro &auxReg = lista_reg[_userId];

        if(!auxReg.getUnderCount()){
            retorno.push_back(Zap("System", "Não ha zaps!"));
            return retorno;
        }

        while(qtdNLidas > 0){
            Zap zapAux = lista_zap[tmhVetZap - 1];
            if(zapAux.getUserId() != _userId){
                retorno.push_back(zapAux);
                qtdNLidas -= 1;
                tmhVetZap -= 1;
            }else{
                retorno.push_back(zapAux);
                tmhVetZap -= 1;
            }
        }

        auxReg.setUnderCount(0);

        return retorno;
    }

    bool hasUser(string _userId){
        int x = lista_reg.count(_userId);
        if(x)
            return true;
        return false;
    }

    string toStringChat(){
        return this->chatId;
    }

    friend class User;
};

string User::getOverview(){
    stringstream ss;
    for(auto par : lista_chat){
        ss << "Chat: " << par.first;
        ss << "{" << par.second->getUnreadCount(userId) << "}" << endl;
    }
    return ss.str();
}

void User::invite(string _chatId, User *_user){
    assertChat(_chatId);
    Chat * aux = lista_chat[_chatId];
    bool t = aux->hasUser(_user->userId);
    if(t)
        return;

    aux->lista_reg[_user->userId] = Registro(_user);
    _user->lista_chat[_chatId] = aux;
}

void User::leave(string _chatId){
    assertChat(_chatId);
    Chat * aux = lista_chat[_chatId];
    aux->lista_reg.erase(this->userId);
    lista_chat.erase(aux->chatId);
}

void User::sendZap(string _msg, string _chatId){
    assertChat(_chatId);
    Chat * aux = lista_chat[_chatId];
    Zap msg = Zap(this->userId, _msg);
    aux->deliverZap(msg);
}

#endif // WHATSAPP
