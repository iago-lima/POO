#ifndef TWEETT_H
#define TWEETT_H
#include <iostream>
#include <vector>
#include <sstream>
#include "User.h"

using namespace std;


class Tweett{
    int idTw;
    string userName;
    string msg;
    vector<User> likes;
public:
    Tweett(int _idTw, string _userName, string _msg){
        this->idTw = _idTw;
        this->userName = _userName;
        this->msg = _msg;
    }

    void addLike(User _user){

    }
    int getTwId(){
        return idTw;
    }
    string getUserName(){
        return userName;
    }
    string getMsg(){
        return msg;
    }
    string toString(){
        stringstream ss;
        ss << "Id: " << idTw << endl;
        ss << "User Name: " << userName << endl;
        ss << "Msg: " << msg << endl;
        ss << "{";
        for(auto elemento : likes){
            ss << elemento.toString() << ", ";
        }
        ss << "}";

        return ss.str();
    }
};

#endif // TWEETT_H
