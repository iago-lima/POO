
### struct Ingrediente
- Armazena a identificação do produto e o seu valor.
```
    Ingrediente(string id = "", float _valor = 0.0)
    string getIdIngr()
    float getValor()
    void setValor(float newValor)
    string toStringIngr()
```

### class Produto
- Armazena a identificação dos produtos quais igredientes o compõem  e seu valor.
```
    Produto(string id = "", float _valor = 0.0)
    void setIngredientes(Ingrediente *ingre)
    float getValor()
    void setValor(float newValor)
    string getIdProd()
    string toStringProd()
```
### class Venda
- Guarda o produto vendido e por quantas pessoas o produto foi dividido
```
    Venda(Produto * _prod, float _div)
    Produto *getProdVen()
    float getDivd()
```

### class UserConta
- Conta do Cliente
  - Armazena um Cliente
  - Armazena todas as vendas feitas para esse cliente

```
    UserConta(Cliente * cli)
    vector<Venda> getVendas()
    void setVendas(Venda value)
    string userIdCli();
```

### class Mesa
- Cada mesa tem um identificador
- A quantidade de clientes na mesa e de cadeiras
- O valor a pagar
- E uma lista de UserContas

```
    Mesa(string id = "", int _qtdCad = 0)
    int getClieNaMesa()
    string getIdMesa()
    void comprar(Produto * produto, vector<Cliente*> clis)
    bool addCli(Cliente * cli)
    float valordoCliente(Cliente * cli);
    void setValorAPagar(float valor)
    string toStringMesa();
```

### class Cliente
- Identificador do clientes
- Lista de mesas

```
    Cliente(string id = "")
    string getIdCliente()
    void sentar(Mesa * _mesa)
    string pagarESair(Mesa * idMesa)
    string toStringCli()
```
