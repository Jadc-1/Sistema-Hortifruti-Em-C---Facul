#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


struct Produto {
    int id;
    char nome[50];
    float precoKG;
};

void CadastrarFruta(struct Produto informacoesProduto[], int *i) { // Chamei o vetor informacoesProduto, porém ele é definido no int main.

    char opcao;
    refaz:informacoesProduto[*i].id = *i + 1; // aqui estou utilizando ponteiro para o valor ser mais preciso, pegando o endereço da memoria da variavel.
    printf("ID: %d\n", informacoesProduto[*i].id);
    printf("\nQual fruta você deseja cadastrar?");
    scanf("%s", informacoesProduto[*i].nome);
    printf("\nAdicione o preço Unitário por KG: ");
    scanf(" %f", &informacoesProduto[*i].precoKG);
    (*i)++;
    printf("\nQuer cadastrar mais algum produto? S/N\n");
    fflush(stdin); // Limpa o buffer de entrada para que o %c não leia o \n
    scanf(" %c", &opcao);
    opcao = toupper(opcao); // Função toupper da biblioteca ctype, para deixar a resposta em maiusculo
    if (opcao != 'S' && opcao != 'N') {
        printf("Incorreto...\n");
        printf("Digite S ou N: ");
        scanf(" %c", &opcao);
    } else if (opcao == 'S') {
        system("cls");
        goto refaz; // goto para substituir os laços de repetição
    } else {
        system("cls");
    }

}

int Menu() { // Função do menu que retorna para o main a opção escolhida
    int op;
    linha();
    printf("            MENU PDV");
    linha();
    printf("\n1 - Sistema PDV\n");
    printf("2 - Sistema de Estoque\n");
    printf("3 - Sair\n");
    linha();
    printf("Digite sua opção: ");
    scanf("%d", &op);
    system("cls");
    return op;
}

void linha() { // função de linha para organizar meu codigo
    printf("\n---------------------------------\n");
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    struct Produto informacoesProduto[10];
    int i = 0;

    int op = 1;
    do {
        op = Menu();
        switch (op)
        {
        case 1:
            printf("Sistema de venda");
            break;
        case 2:
            system("cls");
            printf("Abrindo o sistema de Estoque...");
            sleep(1);
            system("cls");
            linha();
            printf("Sistema de Estoque:");
            linha();
            printf("1 - Cadastrar Produto\n");
            printf("2 - Listar Produtos\n");
            printf("3 - Voltar ao menu PDV\n");
            int opCadastro;
            printf("\nOpção desejada?\n");
            scanf("%d", &opCadastro);
            linha();
            switch (opCadastro) {
                case 1:
                    system("cls");
                    CadastrarFruta(informacoesProduto, &i); //Estou chamando a função criada e adicionando as variaveis necessárias para o seu funcionamento, sendo uma delas o endereço de memoria de i.
                    break;
                case 2:
                    system("cls");
                    printf("--------------------------------------\n");
                    printf("   ID:  |     Fruta:   |  Preço KG   |\n");
                    printf("--------------------------------------\n");
                    for (int fru = 0; fru < i; fru++) { //variavel fru, vai repetir o código enquanto for menor que i, no qual é incrementado quando adicionado um novo produto
                        printf("| %-5d | %-12s |   %8.2f  |\n", // Eu defini tamanhos fixos para cada variavel, 5 caracteres para ID e 12 para string, para ficar aninhado
                               informacoesProduto[fru].id,
                               informacoesProduto[fru].nome,
                               informacoesProduto[fru].precoKG);
                        printf("--------------------------------------\n");
                    }
                    system("pause");
                    system("cls");

                    break;
                case 3:
                    printf("Voltando...");
                    usleep(500000);
                    system("cls");
                    break;
                default:
                    break;
            }
            break;
        case 3:
            printf("Saindo...");
            sleep(1);
            break;
        default:
            break;
        }
    } while (op != 3); // Vai repetir enquanto a resposta for diferente de 3, se for 3, é a opção sair, então irá para de repetir


}
