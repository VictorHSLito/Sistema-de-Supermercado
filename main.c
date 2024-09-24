#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Estruturas que serão utilizadas no sistema*/
typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto item;
    int quantidade;
} Carrinho;

/*Declaração implícita das funções que são utilizadas durante o programa*/
int menu(Produto *p[], Carrinho *c[], int *carrinhoIndex, int *contador);
int validaEntrada(char *string);
void cadastrarProduto(Produto *p[], int *index);
void listarProdutos(Produto *p[], int *index);
void comprarProdutos(Produto *p[], Carrinho *c[], int *carrinhoIndex,int *contador);
void visualizarCarrinho(Carrinho *c[], int *carrinhoIndex);
void finalizarPedido(Carrinho *c[], int *carrinhoIndex);
int verificaCarrinho (Produto *p[], Carrinho *c[], int *carrinhoIndex, int opc);
int verificaProduto(Produto *p[], int *index, int codigo);
void temNoCarrinho(Carrinho *c[], int *carrinhoIndex);

/*Programa Principal*/
int main() {
    Produto *p[50]; // Cria um array de 50 espaços da estrutura Produtos
    Carrinho *c[50]; // Cria um array de 50 espaços da estrutura Produtos
    int opc = 0; // Variável auxiliar que fará o controle do loop do programa
    int cont = 0; // Contador que irá operar sobre os index dos Produtos
    int carrinhoIndex = 0; //Contador que irá operar sobre os index do Carrinho

    do
    {
        opc = menu(p, c, &carrinhoIndex, &cont);
    } while (opc == 0);
    
    return 0;
}

int menu(Produto *p[], Carrinho *c[], int *carrinhoIndex, int *contador) {
    /*Aqui todas as variáveis foram passadas por referência
    pois o controle de valores delas serão todos feitos através das
    funções e não da função main*/
    char input[10]; // String que previnirá do usuário digitar uma opção fora do escopo
    int opc = 0; // Variável auxiliar que será usada para o switch-case
    do {   
        printf("\tBem vindo(a) ao menu! O que gostaria de fazer?\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Comprar Produtos\n");
        printf("4 - Visualizar Carrinho\n");
        printf("5 - Fechar Pedido\n");
        printf("6 - Sair\n");

        fgets(input, sizeof(input), stdin);
        if (validaEntrada(input) != 0) {
            printf("Numero digitado invalido!\n");
            continue;
        }
        opc = atoi(input);
        if (opc < 1 || opc > 6 ) {
            printf("Voce digitou uma opcao invalida! Tente novamente\n\n");
        }
        else {
            switch (opc)
            {
            case 1:
                cadastrarProduto(p, contador);
                break;
            case 2:
                listarProdutos(p, contador);
                break;
            case 3:
                comprarProdutos(p, c, carrinhoIndex, contador);
                break;
            case 4:
                visualizarCarrinho(c, carrinhoIndex);
                break;
            case 5:
                finalizarPedido(c, carrinhoIndex);
                break;    
            case 6:
                return -1; // Retorna -1 para que o loop do-while na função main pare de executar
                break;
            }
        }
    } while (opc < 1 || opc > 6);
    return 0; // Retorna 0 para que o loop do-while na função main continue executando
}

void cadastrarProduto(Produto *p[], int *index) {
    /*Aqui é passado a estrutura Produtos e o contador
    que irá atualizar quando um novo produto for adicionado*/
    int aux = 0;
    p[*index] = (Produto *) malloc(sizeof(Produto)); // Aloca memória para um ponteiro p do tipo Produto, que conterá as informações
    printf("Digite o codigo do produto: ");
    scanf("%d", &p[*index]->codigo);
    aux = verificaProduto(p, index, p[*index]->codigo);
    setbuf(stdin, NULL); // Função que limpa o buffer do teclado após os scanf`s
    if (aux == 0) {
        printf("Digite o nome do produto: ");
        fgets(p[*index]->nome, sizeof(p[*index]->nome), stdin);
        setbuf(stdin, NULL);
        do {
            printf("Digite o preco do produto: ");
            scanf("%f", &p[*index]->preco);
            setbuf(stdin, NULL);
        } while (p[*index]->preco <= 0);
        
        (*index)++; // Atualiza o contador de produtos sempre que um novo produto é cadastrado
        printf("PRODUTO CADASTRADO COM SUCESSO!\n");
    }    
}

void listarProdutos(Produto *p[], int *index) {
    /*Lista todos os produtos cadastrados*/
    if (*index != 0) {
        for (int i = 0; i < *index; i++) {
            printf("\t-------------Produto #%d-------------\n", i);
            printf("Codigo do produto: %d\n", p[i]->codigo);
            printf("Nome do produto: %s", p[i]->nome);
            printf("Preco do produto: %.2f\n", p[i]->preco);
        }
    }
    else {
        printf("Nenhum produto foi cadastrado ainda!\n");
        printf("Tente cadastrar um produto primeiro...\n");
    }
}

void comprarProdutos(Produto *p[], Carrinho *c[], int *carrinhoIndex, int *index) {
    /*Aqui são passados 4 parâmetros, o da estrutura Produtos, Carrinho, contador do carrinho
    e o contador dos produtos*/
    c[*carrinhoIndex] = (Carrinho *) malloc(sizeof(Carrinho)); // Aloca memória para um ponteiro da estrutura Carrinho
    int opc = 0; // Variável que será usada para escolher o produto
    int quantidade = 0; // Variável que será usada para escolhe a quantidade

    if (*index != 0) {
        int aux = 0;
        printf("Qual produto gostaria de comprar? \n");
        listarProdutos(p, index); // Somente foi passado como parametro a estrutura Produto e o contador dos produtos para que chamasse a função
        do {
            char input[10];
            printf("Sua escolha: ");
            fgets(input, sizeof(input), stdin);

            if (validaEntrada(input) != 0) {
                printf("Digite apenas numeros!\n");
                continue;
            }
            opc = atoi(input);
            if (opc > *index - 1 || opc < 0) {
                printf("Voce tentou comprar um produto inexistente! Tente novamente!\n");
            }
        } while (opc > *index - 1 || opc < 0); // Impede o usuário de digitar uma opção fora do index    
        
        aux = verificaCarrinho(p, c, carrinhoIndex, opc);
        if (aux == 0) {
            c[*carrinhoIndex]->item = *p[opc]; // Aqui estarei dizendo que o ponteiro C apontará para o ponteiro da estrutura Produto de acordo com opção escolhida
            do {
                char input[10];
                printf("Qual a quantidade? ");
                fgets(input, sizeof(input), stdin);
                setbuf(stdin, NULL);
            
                if (validaEntrada(input) != 0) {
                    printf("Numero invalido!!!!!!!\n");
                }
                else {
                    quantidade = atoi(input);
                }
            } while (quantidade <= 0); // Impede o usuario de digitar uma quantidade negativa ou zero
            c[*carrinhoIndex]->quantidade = quantidade;
            (*carrinhoIndex)++; // Atualiza o contador do carrinho sempre que um novo produto é colocado no carrinho
            printf("PRODUTO ADICIONADO AO CARRINHO COM SUCESSO!\n");
        }
    }
    else {
        printf("Nao eh possivel comprar! Nenhum produto foi cadastrado ainda!\n");
        printf("Tente cadastrar um produto primeiro...\n");
    }
}

void visualizarCarrinho(Carrinho *c[], int *carrinhoIndex) {
    /*Função que mostrará todos os itens contidos no Carrinho*/
    if (*carrinhoIndex != 0) {
        printf("\t-------------Itens do Carrinho-------------\n");
        for (int i = 0; i < *carrinhoIndex; i++) {
        printf("\tItem: %s", c[i]->item.nome);
        printf("\tQuantidade do item: %d\n", c[i]->quantidade);
        }
    //temNoCarrinho(c, carrinhoIndex); // Está é uma função auxiliar para saber se já algum produto no carrinho, caso o seu carrinho esteja muito cheio
    }
    else {
        printf("Carrinho vazio!\n");
    }
}

void finalizarPedido(Carrinho *c[], int *carrinhoIndex) {
    /*Essa função mostrará o total gerado pelas compras dos produtos*/
    visualizarCarrinho(c, carrinhoIndex);
    if (*carrinhoIndex != 0) {
        printf("\t-------------Total a Pagar-------------\n");
        float total = 0; 
        for (int i = 0; i < *carrinhoIndex; i++) { // Loop que irá interar por todos os itens do carrinho
            total += c[i]->quantidade*c[i]->item.preco; // Fará a multiplicação da quantidade dos itens pelo respectivo preço
        }

        printf("\tPreco Final: %.2f\n", total);
        printf("\tEsvaziando carrinho...\n");

        for (int i = 0 ; i < *carrinhoIndex; i++) {
            free(c[i]); // Esvazia a memória alocada para o carrinho
            c[i] = NULL; // Faz com que não haja ponteiros soltos no programa
        }
        (*carrinhoIndex) = 0; // Atualiza o index do carrinho para 0

        printf("\tCarrinho esvaziado com sucesso!\n");
    }
    else {
        printf("Nao ha como fechar pedido, pois o seu carrinho esta vazio!\n");
    }
}

void temNoCarrinho(Carrinho *c[], int *carrinhoIndex) {
    /*Função auxiliar para realizar busca de um Produto no Carrinho*/
    int aux = 0;
    if (*carrinhoIndex != 0) {
        printf("Digite o codigo do produto que queira verificar se esta no carrinho: ");
        scanf("%d", &aux);
        for (int i = 0; i < *carrinhoIndex; i++) {
            if (c[i]->item.codigo == aux) {
                printf("Produto está no carrinho!\n");
                break;
            }
            else {
            printf("Nao foi encontrado esse produto no carrinho!\n");
            }
        }   
    }
}

int verificaCarrinho (Produto *p[], Carrinho *c[], int *carrinhoIndex, int opc) {
    /*Adicionei essa função que irá verificar se o produto que o usuário está tentando
    comprar já está no carrinho, caso esteja, ele adicionará mais quantidades dele*/
    for (int i = 0; i < *carrinhoIndex; i++) { // Loop que percorrerar toda a estrutura do Carrinho
            if (c[i]->item.codigo == p[opc]->codigo) {
                int aux = 0;
                printf("Produto ja esta no carrinho!\n");
                do {
                    printf("Adicionar mais quantas unidades do produto no carrinho? ");
                    scanf("%d", &aux);
                    setbuf(stdin, NULL);
                } while (aux < 0);
                c[i]->quantidade += aux;
                return 1;
            }
        }
    return 0; // Caso o produto não se encontre no carrinho ainda, ele retornará 0 e será adicionado normalmente
}

int verificaProduto(Produto *p[], int *index, int codigo) {
    /*Semelhante à função verificaCarrinho, no caso verificará se o produto já está
    cadastrado com o código digitado, caso contrário retorna 0*/
    for (int i = 0; i < *index; i++) {
        if (p[i]->codigo == codigo) {
            printf("Opa! Ja existe um produto com esse codigo! Tente novamente\n");
            return 1;
        }
    }
    return 0;
}

int validaEntrada(char string[]) {
    // Remover o '\n' do final da string, se houver
    size_t len = strlen(string);
    if (string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }

    // Verificar se todos os caracteres são dígitos
    for (unsigned i = 0; i < strlen(string); i++) {
        if (!isdigit(string[i])) {
            return 1;  // Retorna 1 se não for um número
        }
    }

    return 0;  // Retorna 0 se a string for válida (somente números)
}