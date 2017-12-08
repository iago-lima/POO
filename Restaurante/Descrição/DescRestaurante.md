---
layout: post
title:  "Restaurante"
category: ''
introduction: ''
description:
image: ''
tags:
- nxn
- repositórios
---

- Os ingredientes podem ser adicionados ao sistema e devem ter id único.
    - Cada igrediente tem seu valor.
- O usuário pode querer saber quais igredientes estão cadastrados ou as informações de cada ingrediente.


```
addIngred Achocolatado 1.5
..done
addIngred CocoRalado 1
..done
addIngred LeiteCondensado 2
..done
addIngred Leite 2
..done
addIngred Leite 2
..ingrediente Leite ja existe

showIngred
  ..[Achocolatado CocoRalado Leite LeiteComdensado]
infoIngred Leite
  ..Leite, Valor: 2
infoIngred CocoRalado
..CocoRalado, Valor: 1
```
- Os produtos podem ser adicionados ao sistema e devem ter id único.
    - Os produtos são formados pela junção de ingredientes.
    - Cada produto tem preço de produção.
    - O valor final do produto é a soma do preço de produção com o valor de cada ingrediente.
- O usuário pode querer saber quais produtos estão cadastrado ou as informações de cada produto.

```
addProd Brigadeiro LeiteCondensado Achocolatado CocoRalado 3
..done
addProd Milkshake LeiteCondensado Leite Achocolatado 2
..done
addProd Milkshake LeiteCondensado Leite Achocolatado 2
..produto Milkshake ja existe

showProd
  ..[Brigadeiro Milkshake]

infoProd Brigadeiro
  ..Produto: Brigadeiro R$: 7.5
  ..Ingredientes:
  .... LeiteCondensado
  .... Achocolatado
  .... CocoRalado

infoProd Milkshake
  ..Produto: Milkshake R$: 7.5
  ..Ingredientes:
  .... LeiteCondensado
  .... Leite
  .... Achocolatado
```
- Os clientes podem ser adicionados ao sistema e devem ter id único.
- O usuário pode querer saber quais os clientes cadastrados

```
addCliente Felipe Iury Iago Barbara Marcia Vitoria
..done
showClientes
..[Barbara Felipe Iago Iury Marcia Vitoria]
addCliente Felipe
..clientes Felipe ja existe
```
- Mesas podem ser adicionadas as restaurante e devem ter id únicos.
  - Informe a quantidade de cadeiras da mesa.
  - O usuário pode querer saber as mesas que estão no restaurante
  - O usuário pode querer saber as informações de cada mesa que esta no restaurante
- A mesa guarda o valor total que os clientes estão devendo.

```
addMesa 01 3
..done
addMesa 02 4
..done
showMesas
..[01 02]
addMesa 01 4
..mesas 01 ja existe

infoMesa 01
..Mesa:01 QtdCade: 3
..Clientes na Mesa:
..[ ]
..Valor total: R$ 0

infoMesa 02
..Mesa:02 QtdCade: 4
..Clientes na Mesa:
..[ ]
..Valor total: R$ 0

```
- Os clientes podem sentar em uma mesa, ou mais de uma.

```
sentar 01 Felipe Marcia Iury
..done
sentar 01 Vitoria
..Vagas indisponíveis para essa mesa!
sentar 02 Vitoria Felipe Iago Barbara
..done
sentar 01 Felipe
..Cliente já está nessa mesa!

infoMesa 01
..Mesa:01 QtdCade: 3
..Clientes na Mesa:
..[ Felipe Marcia Iury ]
..Valor total: R$ 0

infoMesa 02
..Mesa:02 QtdCade: 4
..Clientes na Mesa:
..[ Vitoria Felipe Iago Barbara ]
..Valor total: R$ 0

```
- informações do cliente devem informar em qual ou quais mesas ele está e quanto ele deve em cada mesa.

```
infoCliente Barbara
..Cliente: Barbara
..Mesa:
..[ 02 Dev: 0]

infoCliente Felipe
..Cliente: Felipe
..Mesa:
..[ 01 Dev: 0]
..[ 02 Dev: 0]

```
- Os clientes podem comprar algum produto que esteja cadastrado no sistema.
  - Os clientes podem dividir esse produto com qualquer colega.
  - Para efetuar a compra todos os participantes da compra devem estar na mesma mesa.

```
comprar 01 Brigadeiro Marcia Felipe
..done
comprar 01 Brigadeiro Felipe Vitoria
..Cliente Vitoria não está nesta mesa!


infoCliente Felipe
..Cliente: Felipe
..Mesa:
..[ 01 Dev: 3.75]
..[ 02 Dev: 0]

infoCliente Marcia
..Cliente: Marcia
..Mesa:
..[ 01 Dev: 3.75]

infoMesa 01
..Mesa:01 QtdCade: 3
..Clientes na Mesa:
..[ Felipe Marcia Iury ]
..Valor total: R$ 7.5

comprar 02 Milkshake Vitoria Barbara
..done

infoMesa 02
..Mesa:02 QtdCade: 4
..Clientes na Mesa:
..[ Vitoria Felipe Iago Barbara ]
..Valor total: R$ 7.5

infoCliente Vitoria
..Cliente: Vitoria
..Mesa:
..[ 02 Dev: 3.75]

infoCliente Barbara
..Cliente: Barbara
..Mesa:
..[ 02 Dev: 3.75]

```

- Clientes podem pagar suas contas e saírem das mesas.
  - Mostrar o que foi comprado pelo cliente ao pagar.
  - Mostrar quanto o cliente pagou.
  - Diminuir do valor total da mesa.

```
pagar Felipe 01
..Compras Realizadas:
..1/2 Brigadeiro = 3.75
..Total: 3.75

infoCliente Felipe
..Cliente: Felipe
..Mesa:
..[ 02 Dev: 0]

infoMesa 01
..Mesa:01 QtdCade: 3
..Clientes na Mesa:
..[ Marcia Iury ]
..Valor total: R$ 3.75

```
- Clientes podem sentar nas mesas a qualquer momento, sem alterar o valor da mesa ou dos demais clientes nelas, a menos que faça uma compra.
- Você pode implementar um modo que os clientes vejam o que compraram  e quanto estão devendo antes de pagar.

[Controller](https://github.com/felipesilva543/POO_2017_2/blob/master/Restaurante/Descri%C3%A7%C3%A3o/ControllerDescRest.md).

[Guia](https://github.com/felipesilva543/POO_2017_2/blob/master/Restaurante/Descri%C3%A7%C3%A3o/GuiaDescRes.md).

## Diagrama de Classes

![](/assets/whatsapp_v2/diagrama.png)
