#ifndef TWEET_H
#define TWEET_H
#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include "User.h"

using namespace std;

class Tweet{
    int idTw;
    string userName;
    string msg;
    list<string> likes;

public:

    Tweet(int _idTw = 0, string _userName = "", string _msg = ""){
        this->idTw = _idTw;
        this->userName = _userName;
        this->msg = _msg;
    }

    void addLike(string _username){
        likes.push_back(_username);
    }

    int getTwId(){
        return this->idTw;
    }

    string getUserName(){
        return this->userName;
    }

    string getMsg(){
        return this->msg;
    }

    string toString(){
        stringstream ss;
        ss << "  " << this->idTw << " "
           << this->userName << ": "
           << this->msg;
        if((int) likes.size() > 0){
            ss << "{ ";
            for(auto elemento : this->likes){
                ss << elemento << " ";
            }
            ss << "}";
        }

        return ss.str();
    }
};

#endif // TWEET_H
