#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include "gerenciador.h"



//========== cadastro ==========//
void cadastroCliente(struct Cliente *cliente) {
    FILE *registros_cliente;
    registros_cliente = fopen("registros_cliente.csv", "a");
    if (registros_cliente == NULL) {
        printf("Erro para abrir o arquivo.");
        return;
    }

    fprintf(registros_cliente, "%s,%s,%s\n", cliente->nome, cliente->email, cliente->senha);
    fclose(registros_cliente);
}

void cadastroEmpresa(struct Empresa *empresa) {
    FILE *registros_empresa;
    registros_empresa = fopen("registros_empresa.csv", "a");
    if (registros_empresa == NULL) {
        printf("Erro para abrir o arquivo.");
        return;
    }

    fprintf(registros_empresa, "%s,%s,%s,%s,%s,%d\n", empresa->cnpj, empresa->nome, empresa->senha, empresa->endereco, empresa->categoria,empresa->tempoEntrega);
    fclose(registros_empresa);
}

//========== login ==========//
int verificarLoginCliente(char *arquivo, char *email, char *senha, struct Cliente *cliente) {
    FILE *registros_cliente = fopen(arquivo, "r");
    if (registros_cliente == NULL) {
        return -1; //erro
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), registros_cliente) != NULL) {
        char email2[30];
        char senha2[30];

        if (sscanf(linha, "%99[^,],%99[^,],%99s", cliente->nome, email2, senha2) == 3) {
            if (strcmp(email, email2) == 0 && strcmp(senha, senha2) == 0) {
                fclose(registros_cliente);
                return 0;
            }
        }
    }

    fclose(registros_cliente);
    return -1;
}

int loginEmpresa(struct ListaEmpresa *lista, char *CNPJ, char *senha, struct Empresa *empresa) {
    struct Empresa *atual = lista->inicio;

    while (atual != NULL) {
        if (strcmp(atual->cnpj, CNPJ) == 0) {
            if (strcmp(atual->senha, senha) == 0) {
                strcpy(empresa->cnpj, atual->cnpj);
                strcpy(empresa->nome, atual->nome);
                strcpy(empresa->senha, atual->senha);
                strcpy(empresa->endereco, atual->endereco);
                strcpy(empresa->categoria, atual->categoria);
                empresa->tempoEntrega = atual->tempoEntrega;

                return 1;
            }
        }
        atual = atual->proxima;
    }

    return 0; // Falha no login
}



//========== Lista - EMPRESA ==========//
struct ListaEmpresa* criar() {
    struct ListaEmpresa* lista = (struct ListaEmpresa*)malloc(sizeof(struct ListaEmpresa));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

int inserirEmpresa(struct ListaEmpresa *lista, struct Empresa *novaEmpresa) {
    struct Empresa *novoNo;
    if ((novoNo = (struct Empresa *)malloc(sizeof(struct Empresa))) == NULL) {
        return -1;
    }

    strcpy(novoNo->nome, novaEmpresa->nome);
    strcpy(novoNo->cnpj, novaEmpresa->cnpj);
    strcpy(novoNo->senha, novaEmpresa->senha);
    strcpy(novoNo->endereco, novaEmpresa->endereco);
    strcpy(novoNo->categoria, novaEmpresa->categoria);
    novoNo->tempoEntrega = novaEmpresa->tempoEntrega;

    if (lista->inicio == NULL) {
        novoNo->proxima = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proxima = novoNo;
        lista->fim = novoNo;
        novoNo->proxima = NULL;
    }
    return 0;

    lista->tamanho++;
}


void liberarListaEmpresas(struct ListaEmpresa *lista) {
    struct Empresa *atual = lista->inicio;
    while (atual != NULL) {
        struct Empresa *proxima = atual->proxima;
        free(atual);
        atual = proxima;
    }
    lista->inicio = NULL;

}

void carregarEmpresas(const char *arquivo, struct ListaEmpresa *lista) {
    FILE *arquivoEmpresas = fopen(arquivo, "r");
    if (arquivoEmpresas == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        return;
    }
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivoEmpresas) != NULL) {
        struct Empresa novaEmpresa;
        int tempoEntrega;

        if (sscanf(linha, "%14[^,],%99[^,],%10[^,],%199[^,],%49[^,],%d",
                   novaEmpresa.cnpj, novaEmpresa.nome, novaEmpresa.senha,
                   novaEmpresa.endereco, novaEmpresa.categoria, &tempoEntrega) == 6) {
            novaEmpresa.proxima = NULL;
            novaEmpresa.tempoEntrega = tempoEntrega;
            inserirEmpresa(lista, &novaEmpresa);
        } else {
            printf("Erro %s\n", linha);
        }
    }

    fclose(arquivoEmpresas);
}



int listarEmpresa(struct ListaEmpresa *lista, char *categoriaDesejada){
    int opcao;
        struct Empresa *atual = lista->inicio;
        int encontrou = 0;

        printf("\n");
        while (atual != NULL) {
            if (strcmp(atual->categoria, categoriaDesejada) == 0) {
                printf("+---------------------------------+\n");
                definirCorTexto(6);
                printf("             %s                    \n", atual->nome);
                definirCorTexto(7);
                printf(" CNPJ: ");
                definirCorTexto(6);
                printf("%s\n", atual->cnpj);
                definirCorTexto(7);
                printf(" Endereco: %s\n", atual->endereco);
                printf(" Tempo de entrega: %d min\n", atual->tempoEntrega);
                printf("\n");

                encontrou = 1;
            }
            atual = atual->proxima;
        }

        if (encontrou == 0) {
            return -1;
        }


        else{
            definirCorTexto(3);
            printf(" Selecione um restaurante (CNPJ): ");
            definirCorTexto(7);
            scanf("%d", &opcao);
            system("cls");

        return opcao;

        }

}

int listarTodasEmpresa(struct ListaEmpresa *lista){
        int opcao;
        struct Empresa *atual = lista->inicio;
        int encontrou = 0;
        int empresaExistente = 0;

        if(lista->inicio == NULL) {
            return -1;
        }

        printf("\n");
        while(empresaExistente != 1) {
                atual = lista->inicio;
                while (atual != NULL) {
                        printf("+---------------------------------+\n");
                        definirCorTexto(6);
                        printf("             %s                    \n", atual->nome);
                        definirCorTexto(7);
                        printf(" CNPJ: ");
                        definirCorTexto(6);
                        printf("%s\n", atual->cnpj);
                        definirCorTexto(7);
                        printf(" Endereco: %s\n", atual->endereco);
                        printf("+---------------------------------+\n");
                        printf("\n");
                        atual = atual->proxima;
                }

                definirCorTexto(3);
                printf(" Selecione um restaurante (CNPJ): ");
                definirCorTexto(7);
                scanf("%d", &opcao);
                system("cls");

                struct Empresa *aux = lista->inicio;
                while (aux != NULL && empresaExistente != 1) {
                    if (atoi(aux->cnpj) == opcao) {
                        empresaExistente = 1;
                    }
                    else {
                        aux = aux->proxima;
                    }
                }
        }

        return opcao;
}

struct Empresa* selecionarRestaurante(struct ListaEmpresa *lista, int opcao) {
    struct Empresa *atual = lista->inicio;
    while (atual != NULL) {
        if (atoi(atual->cnpj) == opcao) {
            struct Empresa *novaEmpresa = (struct Empresa *)malloc(sizeof(struct Empresa));
            if (novaEmpresa != NULL) {
                strcpy(novaEmpresa->nome, atual->nome);
                strcpy(novaEmpresa->cnpj, atual->cnpj);
                strcpy(novaEmpresa->senha, atual->senha);
                strcpy(novaEmpresa->endereco, atual->endereco);
                strcpy(novaEmpresa->categoria, atual->categoria);
                novaEmpresa->tempoEntrega = atual->tempoEntrega;
                novaEmpresa->pratos = NULL;
                carregarPratos(novaEmpresa);
                return novaEmpresa;
            }
            else {
                return NULL;
            }
        }
        atual = atual->proxima;
    }
    return NULL;
}


//========== Lista - PRATOS ==========//

int adicionarPrato(struct Empresa *empresa, struct Prato *prato) {
    struct Prato *novoPrato = (struct Prato *)malloc(sizeof(struct Prato));
    if (novoPrato == NULL) {
        return -1;
    }
    strcpy(novoPrato->nome, prato->nome);
    novoPrato->preco =  prato->preco;
    novoPrato->proxima = NULL;

    if (empresa->pratos == NULL) {
        empresa->pratos = novoPrato;
    }
    else {
        struct Prato *atual = empresa->pratos;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = novoPrato;
    }
    empresa->numPratos++;
    return 0;
}

int listarPratos(struct Empresa *empresa) {

        printf("+---------------------------------+\n");
        definirCorTexto(6);
        printf("             %s\n",        empresa->nome);
        definirCorTexto(7);
        printf("Taxa de entrega: Gratis            \n");
        printf("Tempo de entrega: %d min\n", empresa->tempoEntrega);
        printf("+---------------------------------+\n");


        struct Prato *atual = empresa->pratos;

        if (atual == NULL) {
            definirCorTexto(4);
            printf("O restaurante nao possui pratos.\n");
            definirCorTexto(7);
            return -1;
        }
        definirCorTexto(6);
        printf("\n== Cardapio ==\n");
        definirCorTexto(7);
        while (atual != NULL) {
            printf("Prato: %s\n", atual->nome);
            printf("Valor: R$ %.2f\n", atual->preco);
            printf("\n");
            atual = atual->proxima;
        }

    return 0;


}

void liberarListaPratos(struct Empresa *empresa) {
    struct Prato *atual = empresa->pratos;
    while (atual != NULL) {
        struct Prato *proxima = atual->proxima;
        free(atual);
        atual = proxima;
    }
    empresa->pratos = NULL;
    empresa->numPratos = 0;
}

void salvarPratos(struct Empresa *empresa) {
    FILE *arquivoPratos;
    char nomeArquivo[50];
    sprintf(nomeArquivo, "pratos_%s.txt", empresa->cnpj);

    arquivoPratos = fopen(nomeArquivo, "w");
    if (arquivoPratos == NULL) {
        printf("Erro ao abrir o arquivo de pratos.\n");
        return;
    }

    struct Prato *atual = empresa->pratos;
    while (atual != NULL) {
        fprintf(arquivoPratos, "%s,%.2lf\n", atual->nome, atual->preco);
        atual = atual->proxima;
    }

    fclose(arquivoPratos);
}

void carregarPratos(struct Empresa *empresa) {
    FILE *arquivoPratos;
    char nomeArquivo[50];

    sprintf(nomeArquivo, "pratos_%s.txt", empresa->cnpj);

    arquivoPratos = fopen(nomeArquivo, "r");
    if (arquivoPratos == NULL) {
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivoPratos) != NULL) {
        struct Prato novoPrato;

        if (sscanf(linha, "%49[^,],%f", novoPrato.nome, &novoPrato.preco) == 2) {
            novoPrato.proxima = NULL;
            adicionarPrato(empresa, &novoPrato);
        } else {
            printf("Erro ao ler a linha de prato: %s", linha);
        }
    }

    fclose(arquivoPratos);
}

int removerPrato(struct Empresa *empresa, char *nomePrato) {
    if (empresa->numPratos == 0) {
        printf("Nao possui pratos\n");
        return -1;
    }

    struct Prato *anterior = NULL;
    struct Prato *atual = empresa->pratos;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomePrato) == 0) {
            if (anterior == NULL) {
                empresa->pratos = atual->proxima;
            }
            else {
                anterior->proxima = atual->proxima;
            }

            free(atual);
            empresa->numPratos--;

            definirCorTexto(6);
            printf("Prato '%s' removido com sucesso.\n", nomePrato);
            definirCorTexto(7);
            return 0;
        }
        anterior = atual;
        atual = atual->proxima;
    }

    definirCorTexto(4);
    printf("Nao possui prato '%s' para remover.\n", nomePrato);
    definirCorTexto(7);




}

//========== Lista - CARRINHO ==========//

int adicionarCarrinho(struct Carrinho *carrinho, struct Prato *prato, int quantidade) {
    if (carrinho == NULL || quantidade <= 0) {
        return -1;
    }

    struct CarrinhoItem *novoCarrinho = (struct CarrinhoItem *)malloc(sizeof(struct CarrinhoItem));
    if (novoCarrinho == NULL) {
        return -2;
    }

    strcpy(novoCarrinho->nome, prato->nome);
    novoCarrinho->preco = prato->preco;
    novoCarrinho->quantidade = quantidade;
    novoCarrinho->proxima = NULL;

    if (carrinho->inicio == NULL) {
        carrinho->inicio = novoCarrinho;
        carrinho->fim = novoCarrinho;
    }
    else {
        carrinho->fim->proxima = novoCarrinho;
        carrinho->fim = novoCarrinho;
    }

    int valorM = quantidade * novoCarrinho->preco;
    carrinho->valorTotal += valorM;
    carrinho->tamanho++;

    definirCorTexto(2);
    printf("\nItem adicionado ao carrinho com sucesso!\n");
    definirCorTexto(7);

    return 0;
}

struct Prato* buscarPrato(struct Empresa *empresa, const char *nomePrato) {
    struct Prato *atual = empresa->pratos;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomePrato) == 0) {
            return atual;
        }
        atual = atual->proxima;
    }

    return NULL;
}

struct Carrinho* criarCarrinho() {
    struct Carrinho* carrinho = (struct Carrinho*)malloc(sizeof(struct Carrinho));
    if (carrinho != NULL) {
        carrinho->inicio = NULL;
        carrinho->fim = NULL;
        carrinho->tamanho = 0;
        carrinho->valorTotal = 0.0;
    }
    return carrinho;
}

int listarCarrinho(struct Carrinho *carrinho){
        struct CarrinhoItem *atual = carrinho->inicio;
         if (atual == NULL) {
            return -1;
        }
        printf("+----------------------+---------------+------------+\n");
        printf("| Prato                |   Valor       | Quantidade |\n");
        printf("+----------------------+---------------+------------+\n");
        while (atual != NULL) {
        printf("| %-20s | R$ %-10.2f | %-10d |\n", atual->nome, atual->preco, atual->quantidade);
            atual = atual->proxima;
        }
        printf("+----------------------+---------------+------------+\n");
        printf("| Valor total: R$ %-10.2f           |\n", carrinho->valorTotal);
        printf("+--------------------------------------+\n");
        return 0;

}


int removerPratoDoCarrinho(struct Carrinho *carrinho, const char *nomePrato) {
    if (carrinho->tamanho == 0) {
        return -1;
    }

    struct CarrinhoItem *anterior = NULL;
    struct CarrinhoItem *atual = carrinho->inicio;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomePrato) == 0) {
            if (anterior == NULL) {
                carrinho->inicio = atual->proxima;
            }
            else {
                anterior->proxima = atual->proxima;
            }

            carrinho->valorTotal -= (atual->preco * atual->quantidade);

            free(atual);
            carrinho->tamanho--;

            return 0;
        }
        anterior = atual;
        atual = atual->proxima;
    }
    return -1;
}



//EXTRAS

void definirCorTexto(int corTexto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, corTexto);
}


char *gerarPIX(){
    char *codigo = (char *)malloc(16 * sizeof(char));
    char caracteres[] = "0123456789abcdefghijklnmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int codigoAUX;
    srand(time(NULL));
    for(int i = 0; i < 15; i++){
        codigoAUX = rand() % (sizeof(caracteres) - 1);
        codigo[i] = caracteres[codigoAUX];
    }
    codigo[15] = '\0';

    return codigo;
}

int BarraCarregamento() {
    int total = 15;
    int progresso = 0;
    int tamanho = 25;

    while (progresso < total) {
        int largura = (int)((double)progresso / total * tamanho);

        printf("[");
        for (int i = 0; i < tamanho; i++) {
            if (i < largura) {
                printf("=");
            }
        }
        printf("] %d%%\r", (int)((double)progresso / total * 100));
        fflush(stdout);
        progresso += 2;
        sleep(1);
    }

    return 0;
}

int VerificarCNPJ(struct ListaEmpresa *lista, char *cnpj) {
    struct Empresa *atual = lista->inicio;
    int encontrou;

    while (atual != NULL) {
        if (strcmp(atual->cnpj, cnpj) == 0) {
            encontrou = 1;
        }
        atual = atual->proxima;

    }
    if(encontrou == 1){
        return -1;
    }
    else{
        return 0;
    }

}


void TempoEntrega(struct Empresa *empresa) {
    srand((unsigned)time(NULL));
    empresa->tempoEntrega = (float)(10 + rand() % 51);
}

void ErroMensagem(){
    definirCorTexto(4);
    printf("Opcao invalida, tente novamente!");
    definirCorTexto(7);
    Sleep(1500);
    system("cls");
}
