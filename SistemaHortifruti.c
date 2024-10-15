#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>


struct Produto {
    int id;
    char nome[50];
    float precoKG;
};

int CadastrarFruta(struct Produto informacoesProduto[], int *i) { // Chamei o vetor informacoesProduto, porém ele é definido no int main.
    char opcao;
    refaz:informacoesProduto[*i].id = *i + 1; // Em C o ponteiro não é utilizado automaticamente para mudar a variavel original e pegar o seu endereço de memoria,  utilizamos *, para usar o enderaço, utilizamos %p, pegar o valor (%d, %f, %lf)
    printf("ID: %d\n", informacoesProduto[*i].id); // Geralmente é utilizado ponteiro com struct, para garantir que a variavel original será modificada e não só a cópia
    printf("\nQual fruta você deseja cadastrar?");
    scanf("%s", informacoesProduto[*i].nome);
    printf("\nAdicione o preço Unitário por KG: \n");
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

void ExcluirFruta(struct Produto informacoesProduto[], int *i)
{
    int fruta;
    int idExcluir;
    int posicao = 0;
    int novaQuantidade = 0;
    char R = 'S';
    struct Produto informacoesProduto_Aux[10];

    printf("*Caso não queira apagar um id, digite um ID que não esteja cadastrado\n\n");
    printf("Digite ID a ser excluído: \n");
    scanf("%d", &idExcluir);


    if (*i <= 0) {
        printf("\nNENHUMA FRUTA CADASTRADA!\n");
        printf("\nAperte qualquer tecla para voltar ao Menu do Estoque...\n");
        getch();
        return;
    }
    printf("\nExcluindo a fruta %s...\n", informacoesProduto[idExcluir - 1].nome);
    sleep(2);

    for (fruta = 0; fruta < *i; fruta++) { // Estamos percorrendo pelo vetor, caso o id seja igual ao id digitado, o vetor não será escrito no vetor auxiliar.
        if(informacoesProduto[fruta].id != idExcluir) {
            informacoesProduto_Aux[posicao].id = informacoesProduto[fruta].id;
            strcpy(informacoesProduto_Aux[posicao].nome, informacoesProduto[fruta].nome); // Não é possivel guardar string, em outro vetor, para isso utilizamos strcpy
            informacoesProduto_Aux[posicao].precoKG = informacoesProduto[fruta].precoKG;
            posicao++;
        } else {
        novaQuantidade++; // Se o ID não for diferente, incrementa um valor
        }
    }

    if (novaQuantidade > 0) { //Caso seja incrementado um valor, atualizar o tamanho do vetor.
        *i = posicao;
    }

    for (fruta = 0; fruta < *i; fruta++) { //Estamos guardando novamente as informações em informacoesProduto, porém sem a posicao do vetor que foi "pulada"
        informacoesProduto[fruta].id = fruta + 1;
        strcpy(informacoesProduto[fruta].nome, informacoesProduto_Aux[fruta].nome);
        informacoesProduto[fruta].precoKG = informacoesProduto_Aux[fruta].precoKG;
    }
    system("cls");
    printf("\nFruta excluida!\n");
    printf("\nAperte qualquer tecla para voltar ao Menu do Estoque...\n");
    getch();
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
    //LC_ALL, "Portuguese" não está rodando corretamente, então estou utilizando estes 2 codigos
    system("chcp 65001 > NULL"); // Troca a pagina para UTF-8 (Aceita qualquer acentuação), coloquei > NULL para não aparecer no console
    setlocale(LC_ALL, "pt-br"); // Adicionei a localidade de pt-br

    struct Produto informacoesProduto[10];
    int prod = 0, idProd = 0, i = 0;
    float pesoProd = 0, totalCompra = 0, totalProd = 0;
    int op = 0;

    do {
        op = Menu();
        switch (op)
        {
        case 1:
            system("cls");
            printf("Abrindo o sistema de PDV...");
            sleep(1);
            system("cls");
            printf("\nSistema de vendas:");
            linha();
            printf("Quantos produtos? ");
            scanf("%d", &prod);
            system("cls");
            idProduto:
            printf("Sistema de vendas:");
            linha();
            laco:
                pesoProd = 0;
                printf("ID produto: ");
                scanf("%d", &idProd);
                if(idProd < 0 || idProd != informacoesProduto[idProd - 1].id)
                {
                    printf("ID inválido! Coloque o ID correto!\n");
                    printf("\nPressiona qualquer tecla para continuar a digitar os IDs...\n");
                    getch();
                    system("cls");
                    printf("*Não se preocupe se houver algum ID anterior foi salvo\n\n");
                    goto idProduto;
                    break;
                }
                printf("Peso(KG): ");
                scanf("%f", &pesoProd);
                totalProd = informacoesProduto[idProd - 1].precoKG * pesoProd;
                totalCompra = totalCompra + totalProd;
                prod--;
                if (prod > 0)
                {
                    goto laco;
                }
                linha();
                printf("\nTotal da compra = R$%.2f\n", totalCompra);
                break;
        case 2:
            system("cls");
            printf("Abrindo o sistema de Estoque...");
            sleep(1);
            menu_estoq:system("cls"); //goto para voltar no menu de estoque depois de cadastrar e de listar.
            linha();
            printf("       Sistema de Estoque:");
            linha();
            printf("\n");
            printf("1 - Cadastrar Produtos\n");
            printf("2 - Listar Produtos\n");
            printf("3 - Excluir Produtos\n");
            printf("4 - Voltar ao menu PDV\n");
            linha();
            int opCadastro;
            printf("\nOpção desejada?\n");
            scanf("%d", &opCadastro);
            switch (opCadastro) {
                case 1:
                    system("cls");
                    CadastrarFruta(informacoesProduto, &i); //Estou chamando a função criada e adicionando as variaveis necessárias para o seu funcionamento, sendo uma delas o endereço de memoria de i.
                    goto menu_estoq;
                    break;
                case 2:
                    system("cls");
                    printf("--------------------------------------\n");
                    printf("|  ID:  |  Fruta:      |  Preço KG:  |\n");
                    printf("--------------------------------------\n");
                    for (int fru = 0; fru < i; fru++) { //variavel fru, vai repetir o código enquanto for menor que i, no qual é incrementado quando adicionado um novo produto
                        printf("| %-5d | %-12s |  R$%6.2f   |\n", // Eu defini tamanhos fixos para cada variavel, 5 caracteres para ID e 12 para string, para ficar aninhado
                               informacoesProduto[fru].id,
                               informacoesProduto[fru].nome,
                               informacoesProduto[fru].precoKG);
                        printf("--------------------------------------\n");
                    }
                    system("pause");
                    goto menu_estoq;

                    break;
                case 3:
                    system("cls");
                    ExcluirFruta(informacoesProduto, &i);
                    goto menu_estoq;

                case 4:
                    printf("\n");
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
    } while (op != 3); // Vai repetir enquanto a resposta for diferente de 3, se for 3,é a opção sair, então irá parar de repetir

    return 0;
}
