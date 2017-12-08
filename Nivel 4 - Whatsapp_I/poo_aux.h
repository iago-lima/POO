#ifndef POO_AUX_H
#define POO_AUX_H
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <list>

#define TO_OSTREAM(class_name) \
    friend ostream& operator<<(ostream& os, class_name cn){\
        os << cn.toString();\
        return os;\
    }

using namespace std;

namespace poo{
//faz o cast de string para qualquer coisa
template <class T>
T cast(string palavra){
    T value;
    stringstream(palavra) >> value;
    return value;
}

inline int Int(string word){
    return cast<int>(word);
}

inline int Float(string word){
    return cast<float>(word);
}

//quebra o texto em um vetor de pedaços, utilizando o separador sep
//tal qual em python ou javascript
vector<string> split(const string& text, char sep = ' '){
    vector<string> saida;
    istringstream ss(text);
    string token;
    while(getline(ss, token, sep))
        saida.push_back(token);
    return saida;
}

//dá um tab no texto
//retorna o texto tabeado
//voce pode passar o tab em prefix ao inves do padrão de dois espacos
string tab(string data, string prefix = "  "){
    auto linhas = split(data, '\n');
    string saida = "";
    for(auto& line : linhas)
        saida += prefix + line + "\n";
    if(saida.size() > 0)
        saida.pop_back();//remove a ultima \n
    return saida;
}

//gera um novo vetor com as copias dos dados do vetor original
//para dentro do intervalo selecionado
//copia de _begin ate _end nao incluindo _end
template<class T>
vector<T> slice(vector<T>& vet, int vbegin = 0, int vend = -1){
    vector<T> new_vet;
    int size = vet.size();
    if(vend == -1)
        vend = size;
    for(int i = vbegin; i < vend; i++)
        new_vet.push_back(vet[i]);
    return new_vet;
}


//retorna os values de um map
template<class K, class T>
vector<T> map_values(map<K, T>& mapa){
    vector<T> vet;
    for(auto& par: mapa)
        vet.push_back(par.second);
    return vet;
}

//retorna as chaves de um map
template<class K, class T>
vector<K> map_keys(map<K, T>& mapa){
    vector<K> vet;
    for(auto& par: mapa)
        vet.push_back(par.first);
    return vet;
}

//Junta coisas passando os iteradores
template<class T>
string join(T it_begin, T it_end, string separ){
    if(it_begin == it_end)
        return "";
    stringstream ss;
    for(T it = it_begin; it != it_end; it++)
        ss << *it << separ;
    string saida = ss.str();
    return saida.substr(0, saida.size() - separ.size());
}

template<class T>
string join(T container, string separ){
    if(container.size() == 0)
        return "";
    stringstream ss;
    for(auto elem : container)
        ss << elem << separ;
    string saida = ss.str();
    return saida.substr(0, saida.size() - separ.size());
}

}//namespace poo

template <class T>
string to_string(const T& t){
    stringstream ss;
    ss << t;
    return ss.str();
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& vet){
    os << "[" << poo::join(vet.begin(), vet.end(), " ") << "]";
    return os;
}

template <class T>
ostream& operator<<(ostream& os, const list<T>& lista){
    os << "[" << poo::join(lista.begin(), lista.end(), " ") << "]";
    return os;
}

//converte de container de ponteiros para container de valores
template<class T>
vector<T> operator*(const vector<T*>& vet){
    vector<T> values;
    for(auto ptr : vet)
        values.push_back(*ptr);
    return values;
}

template<class T>
list<T> operator*(const list<T*>& lista){
    list<T> values;
    for(auto ptr : lista)
        values.push_back(*ptr);
    return values;
}

template <class T>
string operator+(const string& str, const vector<T>& vet){
    return str + to_string(vet);
}
template <class T>
string operator+(const string& str, const list<T>& lista){
    return str + to_string(lista);
}

#endif // POO_AUX_H
