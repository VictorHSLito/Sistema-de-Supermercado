#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct 
{
    Produto item;
    int quantidade;
} Carrinho;

void cadastrarProduto(Produto *p[], int *index);
void listarProdutos(Produto *p[], int *index);
void comprarProdutos(Produto *p[], Carrinho *c[], int *carrinhoIndex,int *contador);
int menu(Produto *p[], Carrinho *c[], int carrinhoIndex, int *contador);


int main() {
    Produto *p[50];
    Carrinho *c[50];
    int opc = 0;
    int cont = 0;
    int carrinhoIndex = 0;

    do
    {
        opc = menu(p, c, carrinhoIndex, &cont);
    } while (opc == 0);
    
    return 0;
}


void cadastrarProduto(Produto *p[], int *index) {
    p[*index] = (Produto *) malloc(sizeof(Produto));
    printf("Digite o codigo do produto: ");
    scanf("%d", &p[*index]->codigo);
    setbuf(stdin, NULL);
    printf("Digite o nome do produto: ");
    fgets(p[*index]->nome, sizeof(p[*index]->nome), stdin);
    setbuf(stdin, NULL);
    printf("Digite o preco do produto: ");
    scanf("%f", &p[*index]->preco);
    setbuf(stdin, NULL);
}

void listarProdutos(Produto *p[], int *index) {
    if (p[*index] != NULL) {
        for (int i = 0; i < *index; i++) {
            printf("\t-------------Produto #%d-------------\n", i+1);
            printf("Codigo do produto: %d\n", p[i]->codigo);
            printf("Nome do produto: %s", p[i]->nome);
            printf("Preco do produto: %f\n", p[i]->preco);
        }
    }
    else {
        printf("Nenhum produto foi cadastrado no index %d!", *index);
    }
}

void comprarProdutos(Produto *p[], Carrinho *c[], int *carrinhoIndex, int *index) {
    c[*carrinhoIndex] = (Carrinho *) malloc(sizeof(Carrinho));
    int opc = 0;
    int quantidade = 0;
    
        printf("Qual produto gostaria de comprar? \n");
        listarProdutos(p, index);
        printf("Sua escolha: ");
        scanf("%d", &opc);
        c[*carrinhoIndex]->item = *p[opc];
        printf("Qual a quantidade? ");
        scanf("%d", &quantidade);
        c[*carrinhoIndex]->quantidade = quantidade;
    
    (*carrinhoIndex)++;
}

int menu(Produto *p[], Carrinho *c[], int carrinhoIndex, int *contador) {
    int opc = 0;
    do
    {   
        printf("\tBem vindo(a) ao menu! O que gostaria de fazer?\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Comprar Produtos\n");
        printf("4 - Visualizar Carrinho\n");
        printf("5 - Fechar Pedido\n");
        printf("6 - Sair\n");
        scanf("%d", &opc);

        if (opc < 1 || opc > 6 ) {
            printf("Voce digitou uma opcao invalida! Tente novamente\n\n");
        }
        else {
            switch (opc)
            {
            case 1:
                cadastrarProduto(p, contador);
                (*contador)++;
                return 0;
                break;
            case 2:
                listarProdutos(p, contador);
                return 0;
                break;
            case 3:
                comprarProdutos(p, c, &carrinhoIndex, contador);
                break;
            case 4:
            
                break;
            case 5:
            
                break;    
            case 6:
                return -1;
                break;
            }
        }
    } while (opc < 1 || opc > 6);
    return 0;
}