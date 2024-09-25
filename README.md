# Sistema de Mercado em C
Este repositório é um sistema desenvolvido em C que simula o funcionamento de um mercado. Este sistema permite o cadastro de produtos, adição de itens ao carrinho, visualização dos produtos no carrinho e a finalização de compras.

## Estruturação do Código
O sistema possui duas estruturas básicas que irão compor todo o código, a primeira delas é a estrutura **Produtos** composta por um código identificador, o nome do produto e o seu respectivo preço, a outra estrutura representa o **Carrinho** de compras do usuário, composta por um ponteiro do tipo _Produto_ que apontará para tal estrutura e a quantidade dos produtos armazenados no carrinho. Grande parte do código está comentado para maior compreensão das funcionalidades do programa.

### Função Main ()
> O código possui uma função principal onde operará um loop em torno dela até que o usuário opte por sair.

### Função Menu ()
> Essa é função que apresentará as opções que o usuário poderá fazer durante a execução do programa

### Funções Auxiliares
> O código é composto por várias funções auxiliares que ajudarão nos tratamentos de possíveis erros e controle do programa

## Como Executar?
Compile o código com um compilador para linguagem C/C++ e depois execute-o.
Caso queira testar online, segue um link onde é só executar o código: https://onlinegdb.com/qEmtsu-_M

## Sugestões
Estarei aberto a qualquer tipo de sugestão acerca do código, caso queira contribuir com o projeto, solicite um _Pull Request_.

## Recomendações
Para melhor entendimento do funcionamento do código, recomendo que estude sobre **_Ponteiros_** e **_Structs_** pois é como 90% do programa funciona.

## Melhorias futuras
- Adicionar persistência de dados (salvar e carregar produtos/carrinho de um arquivo).
- Implementar mais funcionalidades, como remoção de produtos do carrinho.

