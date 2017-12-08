#include <iostream>
#include "pessoa.h"

using namespace std;


int main()
{
    Pessoa p = Pessoa("Felipe");
    string tel = "9766";
    p.setTel(tel);
    cout << p.verifTel(tel) << endl;
    cout << "Nome: " << p.getName() << ", Email: " << p.getEmail() << ", Tel: " << p.getTel() << endl;

}

