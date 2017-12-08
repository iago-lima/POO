#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "poo_aux.h"
#include "iostream"
using namespace std;

class Controller{
public:
    bool debug {true};

    virtual string process(string line){
        return line;
    }

    void commandLine() {
        std::cout << "Digite help, cmd ou fim:" << std::endl;
        string line = "";
        while(line != "fim"){
            std::getline(std::cin, line);
            if(line == "" )
                continue;
            if(line.substr(0, 2) == "  "){
                if(this->debug)
                    std::cout << line << std::endl;
                continue;
            }

            std::cout << line << std::endl;
            if(line[0] == '#')
                continue;
            try {
                string resp = this->process(line);
                std::cout << poo::tab(resp, "..") << std::endl;
            } catch(const std::string& e) {
                std::cout << poo::tab(e, "..") << std::endl;
            }
        }
    }
};
#endif // CONTROLLER_H

