#ifndef USER_H
#define USER_H
#include "Repository.h"
#include "Tweett.h"
#include <iostream>
#include <sstream>

using namespace std;



class User{
    string username;
    Repository<User> seguidores;
    Repository<User> seguidos;
    Repository<Tweett> myTweets;
    vector<Tweett> timeLine;
    int unreadCount;
    int nextTwId;

public:
    User(string _username = ""){
        this->username = _username;
    }

    void seguir(User user){
        seguidos.add(user.getUserName(), user);

    }

//    void twittar(string msg){
//        myTweets.add();

//    }

    vector<Tweett> getUnread(){
        vector<Tweett> aux;

        for(int i = ((int)timeLine.size() - unreadCount); i < ((int)timeLine.size()); i++){
            aux.push_back(timeLine[i]);
        }
        return aux;
    }

    string getUserName(){
        return this->username;
    }

    Repository<User> getSeguidores(){
        return this->seguidores;
    }

    Repository<User> getSeguidos(){
        return this->seguidos;
    }

    Repository<Tweett> getMyTweets(){
        return this->myTweets;
    }

    vector<Tweett> getTimeLine(){
        return this->timeLine;
    }

    string toStringUser(){
        stringstream ss;
        ss << "Nome: " << getUserName() << endl;
        ss << "Seguidores: { ";
        vector<User> aux = seguidores.getValues();
        for(User elemento : aux){
            ss << elemento.getUserName() << ", ";
        }
        string username;
        Repository<User> seguidores;
        Repository<User> seguidos;
        Repository<Tweett> myTweets;
        vector<Tweett> timeLine;
        int unreadCount;
        int nextTwId;

    }
};

#endif // USER_H
