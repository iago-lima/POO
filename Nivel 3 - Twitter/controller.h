#ifndef CONTROLLER
#define CONTROLLER
#include "Repository.h"
#include "split.h"
#include "Tweet.h"
#include "User.h"
#include <sstream>

string HELP = R"(
help
users
addUser    _nome
seguir     _nome _outro
seguidores _nome
seguidos   _nome
twittar    _nome _(mensagem com varias palavras)
timeline   _nome
like       _username _idTw
myTweets   _nome
unread     _nome
        )";

class Controller{
    Repository<User> r_user;
    Repository<Tweet> r_tw;
    int nextId{0};
public:
    Controller():
    r_user(), r_tw()
    {

    }

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];

        if(cmd == "help") return HELP;

        if(cmd == "addUser"){
            r_user.add(ui[1], User(ui[1]));
            return "Usuário Criado!\n";
        }

        if(cmd == "users"){
            vector<User> vUser = r_user.getValues();
            stringstream ss;
            ss << "[ ";
            for(auto ele : vUser){
                ss << ele.getUserName() << " ";
            }
            ss << " ]";

            return ss.str();
        }

        if(cmd == "seguir"){
            r_user.at(ui[1]).seguir(&r_user.at(ui[2]));

            return string("Voce seguiu " + ui[2] + "! \n");
        }

        if(cmd == "seguidores"){
            list<User*> seguidores = r_user.at(ui[1]).getSeguidores();
            stringstream ss;
            ss << "Seguidores: " << endl << "[ ";
            for(auto ele : seguidores){
                ss << ele->getUserName() << " ";
            }
            ss << " ]";
            return ss.str();
        }

        if(cmd == "seguidos"){
            list<User*> seguindo = r_user.at(ui[1]).getSeguidos();
            stringstream ss;
            ss << "Seguindo: " << endl << "[ ";
            for(auto ele : seguindo){
                ss << ele->getUserName() << " ";
            }
            ss << "]";
            return ss.str();
        }

        if(cmd == "twittar"){
            string txt;
            for(int i = 2; i < (int) ui.size() - 1; i++){
                txt += ui[i];
                txt += " ";
            }

            r_tw.add(to_string(nextId), Tweet(nextId, ui[1], txt));
            r_user.at(ui[1]).twittar(&(r_tw.at(to_string(nextId))));

            nextId++;
            return "Twitted!!\n";
        }

        if(cmd == "timeline"){
            list<Tweet*> timeline = r_user.at(ui[1]).getTimeLine();
            stringstream ss;
            ss << "Timeline: " << ui[1] << endl;
            for(auto ele : timeline){
                ss << ele->toString() << endl;
            }
            return ss.str();
        }

        if(cmd == "like"){
            r_tw.at(ui[2]).addLike(ui[1]);
            return "Voce deu like!\n";
        }

        if(cmd == "myTweets"){
            list<Tweet*> mys = r_user.at(ui[1]).getMyTweets();
            stringstream ss;
            ss << "Meus Twitters: \n";
            for(auto ele :  mys){
                ss << ele->toString() << endl;
            }
            return ss.str();
        }

        if(cmd == "unread"){
            int aux = r_user.at(ui[1]).getUnreadCount();
            int i = 0;
            list<Tweet*> naolidos = r_user.at(ui[1]).getTimeLine();
            stringstream ss;
            ss << "Nâo lidos: " << ui[1] << endl;
            for(auto ele : naolidos){
                if(i < aux){
                    ss << ele->toString() << endl;
                    i++;
                }
                else{
                    r_user.at(ui[1]).setUnreadCount(0);
                    return ss.str();
                }
            }
            r_user.at(ui[1]).setUnreadCount(0);
            return ss.str();
        }

        return "";
    }

    void commandLine() {
        string line = "";
        while(line != "fim"){
            cout << "(help): ";
            getline(cin, line);
            if(line == "")
                continue;
            cout << ">> " << line << endl;
            try {
                cout << process(line) << endl;
            } catch(const string& e) {
                cout << e << endl;
            }
        }
    }
};
#endif // CONTROLLER

