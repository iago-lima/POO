#include <iostream>
#include "whatsapp.h"
#include "poo_aux.h"
#include "poo_repository.h"
#include "poo_controller.h"

using namespace std;
using namespace poo;

string HELP = R"(help
addUser     _nome _nome...
showUsers
newChat     _user _chat
invite      _user _invited ... _invited _chat
chats       _user
users       _chat
leave       _user _chat
zap         _user _chat _my_msg
ler         _user _chat
)";

class Whatsapp : public Controller{
    Repository<Chat> r_chat;
    Repository<User> r_user;

public:
    Whatsapp():
        r_chat("chat"),
        r_user("user")
    {
    }

    string process(string line){
        auto ui = poo::split(line, ' ');
        auto cmd = ui[0];

        if(cmd == "help")
            return HELP;
        else if(cmd == "addUser"){//_user
            for(int i = 1; i < (int) ui.size(); i++){
                r_user.add(ui[i],User(ui[i]));
            }
        }
        else if(cmd == "showUsers"){
            return "" + r_user.keys();
        }
        else if(cmd == "newChat"){//_user _chat
            if(r_chat.add(ui[2], Chat(ui[2]))->addFirstUser(r_user.get(ui[1])))
                return "Chat criado!\n";
        }
        else if(cmd == "chats"){//_user
            return r_user.get(ui[1])->getOverview();
        }
        else if(cmd == "invite"){//_user _invited ... _invited _chat
            int size = ui.size();
            for(int i = 2; i < (size - 1); i++)
                r_user.get(ui[1])->invite(ui[size - 1], r_user.get(ui[i]));
        }
        else if(cmd == "users"){//_chat
            return "" + r_chat.get(ui[1])->getUsers();
        }
        else if(cmd == "leave"){//_user _chat
            r_user.get(ui[1])->leave(ui[2]);
        }
        else if(cmd == "zap"){//_user _chat _my_msg
            r_user.get(ui[1])->sendZap(join(poo::slice(ui, 3), " "), ui[2]);
        }
        else if(cmd == "ler"){//_user _chat
            vector<Zap> nLidos = r_chat.get(ui[2])->getUnread(ui[1]);
            stringstream ss;
            for(int i = (int) nLidos.size() -1; i >= 0; i--){
                Zap aux = nLidos[i];
                ss << aux.toStringZap();
            }
            return ss.str();
        }
        else if(cmd == "fim")
            return "";
        else
            return string("") + "comando invalido " + "[" + cmd + "]";
        return "done";
    }
};


int main(){
    Whatsapp c;
    c.commandLine();
    return 0;
}
