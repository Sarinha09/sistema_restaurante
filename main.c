#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include "gerenciador.h"



int main() {
    int opcao;
    struct Cliente cliente;
    struct Empresa novaEmpresa;
    struct ListaEmpresa *Empresas = criar();
    carregarEmpresas("registros_empresa.csv", Empresas);

    int numEmpresas = 0, aux = 0;


        definirCorTexto(4);
        printf("  ______              _ _      \n");
        printf(" |  ____|            | (_)     \n");
        printf(" | |__ ___   ___   __| |_  ___ \n");
        printf(" |  __/ _ \\ / _ \\ / _` | |/ _ \\ \n");
        printf(" | | | (_) | (_) | (_| | |  __/ \n");
        printf(" |_|  \\___/ \\___/ \\__,_|_|\\___|\n\n\n");
        definirCorTexto(7);

        BarraCarregamento();
        sleep(1);

        printf("+-------------------------------------+\n");
        printf("|                                     |\n");
        printf("|      [1] Entrar como cliente        |\n");
        printf("|      [2] Entrar como empresa        |\n");
        printf("|      [3] Sobre                      |\n");
        printf("|      [0] Sair                       |\n");
        printf("|                                     |\n");
        printf("+-------------------------------------+\n");

    do {
        printf("             opcao: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 3);
    system("cls");

    switch (opcao) {
        case 1: // cliente

            printf("+-------------------------------------+\n");
            printf("|                                     |\n");
            printf("|          Area do cliente            |\n");
            printf("|                                     |\n");
            printf("|      [1] Login                      |\n");
            printf("|      [2] Novo cadastro              |\n");
            printf("|                                     |\n");
            printf("+-------------------------------------+\n");
            do {
                printf("             opcao: ");
                scanf("%d", &opcao);
                getchar();
            } while (opcao != 1 && opcao != 2);
            system("cls");

            if (opcao == 1) { // login
            int log;
                do{
                    printf("+-------------------------------------+\n");
                    printf("|            Login cliente            |\n");
                    printf("+-------------------------------------+\n");


                    printf("Email: ");
                    fgets(cliente.email, sizeof(cliente.email), stdin);
                    cliente.email[strcspn(cliente.email, "\n")] = '\0';

                    printf("Senha: ");
                    fgets(cliente.senha, sizeof(cliente.senha), stdin);

                    cliente.senha[strcspn(cliente.senha, "\n")] = '\0';
                    log = verificarLoginCliente("registros_cliente.csv", cliente.email, cliente.senha, &cliente);

                    if(log == -1){
                        definirCorTexto(4);
                        printf("Email ou senha incorreto, tente novamente!\n");
                        definirCorTexto(7);
                        Sleep(1500);
                        system("cls");
                    }
                }while(log != 0);

                definirCorTexto(2);
                printf("Login realizado com sucesso!");
                definirCorTexto(7);
                Sleep(1500);
                system("cls");
                aux = 1;


            }
            else if (opcao == 2) {

                printf("+-------------------------------------+\n");
                printf("|          Novo Cadastro              |\n");
                printf("+-------------------------------------+\n");
                // cadastro
                printf("Nome de usuario: ");
                fgets(cliente.nome, sizeof(cliente.nome), stdin);
                cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

                printf("Email: ");
                fgets(cliente.email, sizeof(cliente.email), stdin);
                cliente.email[strcspn(cliente.email, "\n")] = '\0';

                printf("Senha: ");
                fgets(cliente.senha, sizeof(cliente.senha), stdin);
                cliente.senha[strcspn(cliente.senha, "\n")] = '\0';

                cadastroCliente(&cliente);

                definirCorTexto(2);
                printf("Cadastro realizado!");
                Sleep(2000);
                definirCorTexto(7);
                system("cls");
            }
            aux = 1;
            break;

        case 2: // empresa

            printf("+-------------------------------------+\n");
            printf("|                                     |\n");
            printf("|          Area da empresa            |\n");
            printf("|                                     |\n");
            printf("|      [1] Login                      |\n");
            printf("|      [2] Novo cadastro              |\n");
            printf("|                                     |\n");
            printf("+-------------------------------------+\n");
            do {
                printf("             opcao: ");
                scanf("%d", &opcao);
                getchar();
            } while (opcao != 1 && opcao != 2);
            system("cls");

            if (opcao == 1) {
                int log;
                do {
                    printf("+-------------------------------------+\n");
                    printf("|            Login empresa            |\n");
                    printf("+-------------------------------------+\n");
                    printf("CNPJ: ");
                    fgets(novaEmpresa.cnpj, sizeof(novaEmpresa.cnpj), stdin);
                    novaEmpresa.cnpj[strcspn(novaEmpresa.cnpj, "\n")] = '\0';

                    printf("Senha: ");
                    fgets(novaEmpresa.senha, sizeof(novaEmpresa.senha), stdin);
                    novaEmpresa.senha[strcspn(novaEmpresa.senha, "\n")] = '\0';

                    log = loginEmpresa(Empresas, novaEmpresa.cnpj, novaEmpresa.senha, &novaEmpresa);


                    if (log == 0) {
                        definirCorTexto(4);
                        printf("CNPJ ou senha incorretos, tente novamente!\n");
                        definirCorTexto(7);
                        Sleep(1500);
                        system("cls");
                    }
                } while (log == 0);


                definirCorTexto(2);
                printf("Login realizado com sucesso!");
                definirCorTexto(7);
                Sleep(1500);
                system("cls");

                aux = 2;
                break;
            }

            else if (opcao == 2) { // cadastro
                    int log;
                    do{
                        printf("+-------------------------------------+\n");
                        printf("|          Novo Cadastro              |\n");
                        printf("+-------------------------------------+\n");

                        printf("CNPJ (apenas numeros): ");
                        fgets(novaEmpresa.cnpj, sizeof(novaEmpresa.cnpj), stdin);
                        novaEmpresa.cnpj[strcspn(novaEmpresa.cnpj, "\n")] = '\0';

                        printf("Verificando...\n");
                        Sleep(2500);
                        log = VerificarCNPJ(Empresas, novaEmpresa.cnpj);

                        if(log != 0){
                            definirCorTexto(4);
                            printf("\nExiste uma empresa com este CNJP registrado!\n");
                            definirCorTexto(7);
                            Sleep(2500);
                            system("cls");
                        }
                    }while(log == -1);

                    definirCorTexto(2);
                    printf("Tudo certo para continuar o seu cadastro!\n\n");
                     definirCorTexto(7);


                    printf("Qual vai ser o nome do seu restaurante: ");
                    fgets(novaEmpresa.nome, sizeof(novaEmpresa.nome), stdin);
                    novaEmpresa.nome[strcspn(novaEmpresa.nome, "\n")] = '\0';

                    printf("Senha: ");
                    fgets(novaEmpresa.senha, sizeof(novaEmpresa.senha), stdin);
                    novaEmpresa.senha[strcspn(novaEmpresa.senha, "\n")] = '\0';

                    printf("Endereco: ");
                    fgets(novaEmpresa.endereco, sizeof(novaEmpresa.endereco), stdin);
                    novaEmpresa.endereco[strcspn(novaEmpresa.endereco, "\n")] = '\0';

                    TempoEntrega(&novaEmpresa);

                    definirCorTexto(3);
                    printf("\nQual categoria do seu restaurante\n");
                    definirCorTexto(7);
                    printf("1. Lanches\n");
                    printf("2. Pizzas\n");
                    printf("3. Doces e Bolos\n");
                    printf("4. Japonesa\n");
                    printf("5. Marmitas\n");

                    int escolha;
                    do {
                        printf("opcao: ");
                        scanf("%d", &escolha);
                    } while (escolha < 1 || escolha > 5);

                    switch (escolha) {
                        case 1:
                            strcpy(novaEmpresa.categoria, "lanches");
                            break;
                        case 2:
                            strcpy(novaEmpresa.categoria, "pizzas");
                            break;
                        case 3:
                            strcpy(novaEmpresa.categoria, "doces");
                            break;
                        case 4:
                            strcpy(novaEmpresa.categoria, "japonesa");
                            break;
                        case 5:
                            strcpy(novaEmpresa.categoria, "marmita");
                            break;
                        default:
                            break;
                    }
                    inserirEmpresa(Empresas, &novaEmpresa);
                    cadastroEmpresa(&novaEmpresa);
                    numEmpresas++;

                    novaEmpresa.pratos = NULL;

                    definirCorTexto(2);
                    printf("\nCadastro finalizado com sucesso!\n");
                    definirCorTexto(7);
                    Sleep(2500);
            }
            aux = 2;
            system("cls");
            break;

        case 3:
            definirCorTexto(6);
            printf("\n\n==== Trabalho AED1 ====\n\n");
            printf("2 periodo - UFU\n\n");
            definirCorTexto(7);
            printf("Feito por: Sara Dutra, Ana Clara de Carvalho e Joao Vitor Feijo\n\n");

            printf("Neste programa usamos listas encadeadas para armazenar informacoes e funcoes para manipular esses dados,\n");
            printf("proporcionando uma experiencia de gerenciamento de pedidos de comida online. \n");
            printf("Alem disso, ele tem uma interface amigavel para clientes e restaurantes,\n");
            printf("Permitindo que eles interajam de forma eficaz no processo de pedidos de comida online.\n");
            printf("\n");

            Sleep(3000);
            break;

        case 4:
            liberarListaEmpresas(Empresas);
            free(Empresas);


            exit(0);
            break;

    }




    if(aux == 1){
        int carrinhoOpcao, voltarLista, sair, opcaoMenu, empresaOpcao ;
        struct Empresa *empresaSelecionada = NULL;

        do{ // while do menu princiapl
            sair = 0;
            opcaoMenu = 0;
            do{
                definirCorTexto(5);
                printf("Bem-vindo(a), %s.\n", cliente.nome);
                definirCorTexto(7);
                printf("+-------------------------------------+\n");
                printf("|                                     |\n");
                printf("|  [1] Ver restaurantes disponiveis   |\n");
                printf("|  [2] Pesquisar por categoria        |\n");
                printf("|  [3] Ver conta                      |\n");
                printf("|                                     |\n");
                printf("+-------------------------------------+\n");
                printf("             opcao: ");
                scanf("%d", &opcaoMenu);

                if(opcaoMenu < 1 || opcaoMenu > 3){
                    ErroMensagem();
                }

            }while(opcaoMenu < 1 || opcaoMenu > 3);
            system("cls");

            switch (opcaoMenu) { //inicio
                case 1:
                    do{
                        empresaOpcao = listarTodasEmpresa(Empresas);

                        if(empresaOpcao == -1){
                            definirCorTexto(4);
                            printf("Nenhum restaurante encontrado\n");
                            definirCorTexto(7);
                            sair = 2;
                            Sleep(2000);
                            system("cls");
                        }


                        else{
                            empresaSelecionada = selecionarRestaurante(Empresas, empresaOpcao);

                            if(empresaSelecionada == NULL){
                                ErroMensagem();
                                voltarLista = 2;
                            }

                            else{
                                do{
                                    listarPratos(empresaSelecionada);
                                    printf("\n");
                                    definirCorTexto(3);
                                    printf("Selecione uma opcao\n");
                                    definirCorTexto(7);
                                    printf("1. Carrinho\n");
                                    printf("2. Voltar\n");
                                    printf("opcao: ");
                                    scanf("%d", &voltarLista);

                                    if(voltarLista == 2){
                                        liberarListaPratos(empresaSelecionada);
                                    }
                                    if(voltarLista < 1 || voltarLista > 2){
                                        ErroMensagem();
                                    }

                                }while(voltarLista < 1 || voltarLista > 2);
                            }
                            system("cls");
                        }

                    }while(voltarLista == 2);

                    break;
                case 2:

                    do{ //while lista de empresa
                            definirCorTexto(3);
                            printf("Selecione uma categoria\n");
                            definirCorTexto(7);
                            printf("1. Lanches\n");
                            printf("2. Pizzas\n");
                            printf("3. Doces e Bolos\n");
                            printf("4. Japonesa\n");
                            printf("5. Marmitas\n");

                            int categoriaSelecionada;
                            char categoriaDesejada[20];

                            do {
                                printf("Opcao: ");
                                scanf("%d", &categoriaSelecionada);
                                getchar();
                                if(categoriaSelecionada < 1 || categoriaSelecionada > 5){
                                    ErroMensagem();
                                }
                            } while (categoriaSelecionada < 1 || categoriaSelecionada > 5);

                            system("cls");

                            switch (categoriaSelecionada) {
                                case 1:
                                    strcpy(categoriaDesejada, "lanches");
                                    break;
                                case 2:
                                    strcpy(categoriaDesejada, "pizzas");
                                    break;
                                case 3:
                                    strcpy(categoriaDesejada, "doces");
                                    break;
                                case 4:
                                    strcpy(categoriaDesejada, "japonesa");
                                    break;
                                case 5:
                                    strcpy(categoriaDesejada, "marmitas");
                                    break;
                            }

                            empresaOpcao = listarEmpresa(Empresas, categoriaDesejada);

                            if(empresaOpcao == -1){
                                definirCorTexto(4);
                                printf("Nenhum restaurante encontrado na categoria %s\n", categoriaDesejada);
                                definirCorTexto(7);
                                printf("Seleciona outra categoria!\n");
                                voltarLista = 2;
                                Sleep(2000);
                                system("cls");
                            }


                            else{
                                empresaSelecionada = selecionarRestaurante(Empresas, empresaOpcao);

                                if(empresaSelecionada == NULL){
                                    ErroMensagem();
                                    voltarLista = 2;
                                }


                                else{
                                    do{
                                        listarPratos(empresaSelecionada);
                                        printf("\n");
                                        definirCorTexto(3);
                                        printf("Selecione uma opcao\n");
                                        definirCorTexto(7);
                                        printf("1. Carrinho\n");
                                        printf("2. Voltar\n");
                                        printf("opcao: ");
                                        scanf("%d", &voltarLista);

                                        if(voltarLista < 1 || voltarLista > 2){
                                            ErroMensagem();
                                        }

                                    }while(voltarLista < 1 || voltarLista > 2);
                                    system("cls");
                                }
                            }

                        } while (voltarLista == 2); //while lista de empresa


                    break;

                case 3:

                    do{
                        printf("\n");
                        printf("+-------------------------------------+\n");
                        printf("                                     \n");
                        printf("  Nome: %s\n", cliente.nome);
                        printf("  Email: %s\n", cliente.email);
                        printf("  Senha: %s\n", cliente.senha);
                        printf("                                     \n");
                        printf("+-------------------------------------+\n");
                        printf("     Digite 1 para voltar: ");
                        scanf("%d", &sair);

                        if(sair != 1){
                            ErroMensagem();
                        }
                        getchar();
                        system("cls");
                    }while(sair != 1);
                    break;

            } // fim switch




            system("cls");
            if(empresaSelecionada != NULL){
                struct Carrinho *carrinho = criarCarrinho();

                do { //while carrinho

                    do{//while verificacao
                        listarPratos(empresaSelecionada);
                        printf("\n");
                        definirCorTexto(3);
                        printf("Selecione uma opcao\n");
                        definirCorTexto(7);
                        printf("1. Adicionar prato ao carrinho\n");
                        printf("2. Remover prato\n");
                        printf("3. Concluir pedido\n");
                        printf("Opcao: ");
                        scanf("%d", &carrinhoOpcao);
                        getchar();

                        if(carrinhoOpcao < 1 || carrinhoOpcao > 3){
                            ErroMensagem();
                        }

                    }while(carrinhoOpcao < 1 || carrinhoOpcao > 3); //while verificacao

                    if (carrinhoOpcao == 1) { //adicionar prato carrinho
                        struct Prato prato;
                        int quantidade;

                        printf("\nNome do prato: ");
                        fgets(prato.nome, sizeof(prato.nome), stdin);
                        prato.nome[strcspn(prato.nome, "\n")] = '\0';
                        printf("Quantidade: ");
                        scanf("%d", &quantidade);
                        getchar();

                        struct Prato *pratoEscolhido = buscarPrato(empresaSelecionada, prato.nome);

                        if (pratoEscolhido != NULL) {
                            adicionarCarrinho(carrinho, pratoEscolhido, quantidade);
                        }
                        else {
                            printf("Prato nao encontrado, tente novamente.\n");
                        }
                        Sleep(2000);

                        system("cls");

                    } //adicionar prato carrinho

                    else if(carrinhoOpcao == 2){ //remover item carrinho
                        struct Prato prato;
                        printf("\nNome do prato: ");
                        fgets(prato.nome, sizeof(prato.nome), stdin);
                        prato.nome[strcspn(prato.nome, "\n")] = '\0';

                        int log = removerPratoDoCarrinho(carrinho, prato.nome);

                        if(log == -1){
                            definirCorTexto(6);
                            printf("O carrinho esta vazio ou item invalido.\n");
                            definirCorTexto(7);
                            Sleep(1500);
                            system("cls");
                        }
                        if(log == 0){
                            definirCorTexto(6);
                            printf("Prato '%s' removido do carrinho com sucesso.\n", prato.nome);
                            definirCorTexto(7);
                            Sleep(2000);
                            system("cls");
                        }
                    } //remover item carrinho

                    else if(carrinhoOpcao == 3){ //cocluir pedido
                        system("cls");
                        if(carrinho != NULL){

                            int verificacao = listarCarrinho(carrinho);

                            if(verificacao == -1){
                                definirCorTexto(4);
                                printf("Seu carrinho esta vazio, porfavor adicione um item!");
                                definirCorTexto(7);
                                Sleep(2000);
                                system("cls");
                                carrinhoOpcao = 2;
                            }

                            else{
                                do{
                                    definirCorTexto(3);
                                    printf("\nSelecione uma opcao\n");
                                    definirCorTexto(7);
                                    printf("1. Prosseguir\n");
                                    printf("2. Voltar\n");
                                    scanf("%d", &carrinhoOpcao);

                                    if(carrinhoOpcao < 1 || carrinhoOpcao > 2){
                                        ErroMensagem();
                                        listarCarrinho(carrinho);
                                    }
                                }while(carrinhoOpcao < 1 || carrinhoOpcao > 2);
                                system("cls");


                                if(carrinhoOpcao == 1){ //Prosseguir
                                    int pagamento, confirmacao;

                                    do{
                                        listarCarrinho(carrinho);
                                        definirCorTexto(3);
                                        printf("\nAdicione metodo de pagamento\n");
                                        definirCorTexto(7);

                                        printf("1. Pix\n");
                                        printf("2. Cartao de credito\n");
                                        scanf("%d", &pagamento);

                                        if(pagamento < 1 || pagamento > 2){
                                            ErroMensagem();
                                        }
                                        }while(pagamento < 1 || pagamento > 2);

                                    system("cls");

                                    if(pagamento == 1){ //pix

                                        do{
                                            printf("+-----------------------------+\n");
                                            printf("|                             |\n");
                                            printf("|       Gerando codigo        |\n");
                                            printf("|        Aguarde...           |\n");
                                            printf("|                             |\n");
                                            printf("|                             |\n");
                                            printf("|                             |\n");
                                            printf("+-----------------------------+\n");
                                            Sleep(3000);
                                            system("cls");

                                            char *codigoPIX = gerarPIX();

                                            printf("+-----------------------------+\n");
                                            printf("|        Codigo gerado        |\n");
                                            printf("|       %s       |\n", codigoPIX);
                                            printf("|                             |\n");
                                            printf("|    Confirmar pagamento      |\n");
                                            printf("|    1. Sim                   |\n");
                                            printf("|    1. Nao                   |\n");
                                            printf("+-----------------------------+\n");
                                            printf("\n");
                                            scanf("%d", &confirmacao);

                                            if(confirmacao < 1 || confirmacao > 2){
                                                definirCorTexto(4);
                                                printf(" \nOpcao invalida, tente novamente!\n");
                                                definirCorTexto(7);
                                            }
                                            if(confirmacao == 2){
                                                definirCorTexto(6);
                                                printf("\n Codigo pix expirado, vamos gerar um novo codigo!\n");
                                                definirCorTexto(7);
                                                Sleep(1700);
                                                system("cls");
                                            }
                                        }while(confirmacao != 1);


                                    } //pix

                                    else if(pagamento == 2){ //cartao
                                        int  numeroCartao, codigoSeguranca;
                                        definirCorTexto(3);
                                        printf("\nAdicione metodo de pagamento\n");
                                        definirCorTexto(7);
                                        printf("Digite numero do cartao: ");
                                        scanf("%d", &numeroCartao);
                                        printf("Codigo de seguranca: ");
                                        scanf("%d", &codigoSeguranca);
                                        printf("\n");

                                        do{
                                            printf("+-----------------------------+\n");
                                            printf("|    Confirmar pagamento      |\n");
                                            printf("|    1. Sim                   |\n");
                                            printf("|    2. Nao                   |\n");
                                            printf("+-----------------------------+\n");
                                            scanf("%d", &confirmacao);

                                            if(confirmacao < 1 || confirmacao > 2){
                                                ErroMensagem();
                                            }
                                        }while(confirmacao != 1);
                                    } //cartao



                                    printf("Processando, aguarde...\n");
                                    Sleep(2000);
                                    system("cls");

                                    definirCorTexto(2);
                                    printf("\n+--------------------------------+\n");
                                    printf("|  Pedido efetuado com sucesso!  |\n");
                                    printf("+--------------------------------+\n");
                                    definirCorTexto(7);
                                    Sleep(3000);
                                    system("cls");

                                    definirCorTexto(6);
                                    printf("Resumo do seu pedido\n");
                                    definirCorTexto(7);

                                    listarCarrinho(carrinho);
                                    definirCorTexto(3);
                                    printf("\nStatus\n");
                                    definirCorTexto(7);
                                    printf("O restaurante comecou o seu preparo! Aguarde.\n");
                                    Sleep(3000);
                                    system("cls");


                                    do {
                                        definirCorTexto(6);
                                        printf("Resumo do seu pedido\n");
                                        definirCorTexto(7);
                                        listarCarrinho(carrinho);

                                        // Etapa 1: O entregador vai buscar o pedido
                                        definirCorTexto(3);
                                        printf("\nStatus\n");
                                        definirCorTexto(7);
                                        printf("O entregador foi buscar o seu pedido! Aguarde.\n");
                                        Sleep(3000);
                                        system("cls");

                                        // Etapa 2: Simular a entrega
                                        int tempo = empresaSelecionada->tempoEntrega;
                                        while (tempo > 0) {
                                            definirCorTexto(6);
                                            printf("Resumo do seu pedido\n");
                                            definirCorTexto(7);
                                            listarCarrinho(carrinho);

                                            definirCorTexto(3);
                                            printf("\nStatus\n");
                                            definirCorTexto(7);
                                            printf("Entregador saiu para entregar seu pedido!\n");
                                            printf("Previsao: %d min\n", tempo);
                                            Sleep(1000);
                                            tempo--;
                                            system("cls");
                                        }

                                        // Etapa 3: O entregador chegou
                                        definirCorTexto(6);
                                        printf("Resumo do seu pedido\n");
                                        definirCorTexto(7);
                                        listarCarrinho(carrinho);

                                        definirCorTexto(3);
                                        printf("\nStatus\n");
                                        definirCorTexto(2);
                                        printf("Entregador chegou com seu pedido!\n");
                                        Sleep(3000);

                                        // Etapa 4: Confirmar recebimento
                                        do {
                                            definirCorTexto(6);
                                            printf("\nConfirmar recebimento\n");
                                            definirCorTexto(7);
                                            printf("1. Sim\n");
                                            printf("2. Nao\n");
                                            scanf("%d", &confirmacao);

                                            if (confirmacao == 2) {
                                                printf("Houve um imprevisto, aguarde!\n");
                                                Sleep(2000);
                                                system("cls");
                                            }
                                            if (confirmacao < 1 || confirmacao > 2) {
                                                definirCorTexto(4);
                                                printf("Opcao invalida! Digite novamente\n");
                                                definirCorTexto(7);
                                            }
                                        } while (confirmacao < 1 || confirmacao > 2);
                                    } while (confirmacao != 1); // Confirmacao

                                    system("cls");
                                    printf("\n");
                                    printf("+-----------------------------+\n");
                                    printf("|    Agradecemos pela compra  |\n");
                                    printf("+-----------------------------+\n");


                                    int avaliacao;
                                    do{
                                        definirCorTexto(6);
                                        printf("Avalie o seu pedido ( 1 a 5): \n");
                                        definirCorTexto(7);
                                        scanf("%d", &avaliacao);
                                    }while(avaliacao < 1 || avaliacao > 5);

                                    system("cls");
                                    definirCorTexto(3);
                                    printf("Voltar para menu principal?\n");
                                    definirCorTexto(7);
                                    printf("1. Sim\n0. Sair\n");
                                    scanf("%d", &sair);
                                    system("cls");


                                    if(sair == 0){
                                        liberarListaEmpresas(Empresas);
                                        liberarListaPratos(empresaSelecionada);
                                        free(Empresas);
                                        free(empresaSelecionada);

                                        definirCorTexto(6);
                                        printf(" __      ______  _   _______ ______    _____ ______ __  __ _____  _____  ______ \n");
                                        printf(" \\ \\    / / __ \\| | |__   __|  ____|  / ____|  ____|  \\/  |  __ \\|  __ \\|  ____|\n");
                                        printf("  \\ \\  / / |  | | |    | |  | |__    | (___ | |__  | \\  / | |__) | |__) | |__   \n");
                                        printf("   \\ \\/ /| |  | | |    | |  |  __|    \\___ \\|  __| | |\\/| |  ___/|  _  /|  __|  \n");
                                        printf("    \\  / | |__| | |____| |  | |____   ____) | |____| |  | | |    | | \\ \\| |____ \n");
                                        printf("     \\/   \\____/|______|_|  |______| |_____/|______|_|  |_|_|    |_|  \\_\\______|\n");
                                        printf("                                                                                \n");
                                        printf("                                                                                \n");
                                        definirCorTexto(7);
                                        Sleep(4000);
                                        system("pause");

                                        exit(0);
                                    }

                                break;
                                    }
                                }
                            }
                    } //concluir pedido
                }while(carrinhoOpcao == 1 || carrinhoOpcao == 2 || carrinhoOpcao == 3); //while carrinho
            }

        }while(sair == 1); // while do menu princiapl


    }

    else if(aux == 2){
        int sair = 0;
        carregarPratos(&novaEmpresa); // Carrega pratos da empresa

        do{
            printf("\n");
            definirCorTexto(5);
            printf("Bem-vindo(a), %s.\n", novaEmpresa.nome);
            definirCorTexto(7);
            printf("+-------------------------------------+\n");
            printf("|                                     |\n");
            printf("|  [1] Cardapio                       |\n");
            printf("|  [2] Ver conta                      |\n");
            printf("|  [3] Sair                           |\n");
            printf("|                                     |\n");
            printf("+-------------------------------------+\n");
            printf("             opcao: ");
            scanf("%d", &opcao);
            system("cls");
            getchar();

            switch (opcao) {
                do{//while principal
                        case 1:
                            printf("\n");
                            int escolhaAdicionarPrato;
                            do {
                                printf("+-------------------------------------+\n");
                                printf("|                                     |\n");
                                printf("|  [1] Adicionar prato                |\n");
                                printf("|  [2] Remover prato                  |\n");
                                printf("|  [3] Ver lista de pratos            |\n");
                                printf("|  [4] Voltar                         |\n");
                                printf("|                                     |\n");
                                printf("+-------------------------------------+\n");
                                printf("             opcao: ");
                                scanf("%d", &escolhaAdicionarPrato);
                                getchar();

                                if (escolhaAdicionarPrato == 1) {
                                    struct Prato novoPrato;
                                    printf("\nNome do prato: ");
                                    fgets(novoPrato.nome, sizeof(novoPrato.nome), stdin);
                                    novoPrato.nome[strcspn(novoPrato.nome, "\n")] = '\0';

                                    printf("Valor do prato: ");
                                    scanf("%f", &novoPrato.preco);
                                    getchar();

                                    int log = adicionarPrato(&novaEmpresa, &novoPrato);
                                    salvarPratos(&novaEmpresa);

                                    if (log == -1) {
                                        printf("Erro ao adicionar o prato\n");
                                    }
                                    else {
                                        definirCorTexto(2);
                                        printf("Prato adicionado com sucesso!\n");
                                        definirCorTexto(7);
                                        Sleep(2500);
                                    }

                                    system("cls");
                                }

                                else if(escolhaAdicionarPrato == 2){
                                    struct Prato novoPrato;
                                    printf("\nNome do prato: ");
                                    fgets(novoPrato.nome, sizeof(novoPrato.nome), stdin);
                                    novoPrato.nome[strcspn(novoPrato.nome, "\n")] = '\0';

                                    removerPrato(&novaEmpresa, novoPrato.nome);
                                    Sleep(2500);
                                    system("cls");

                                }

                                else if(escolhaAdicionarPrato == 3){
                                    system("cls");
                                    listarPratos(&novaEmpresa);

                                    definirCorTexto(3);
                                    printf("\nSelecione uma opcao\n");
                                    definirCorTexto(7);
                                    printf("4. Voltar\n");
                                    scanf("%d", &escolhaAdicionarPrato);
                                    system("cls");

                                }

                            } while (escolhaAdicionarPrato == 1 || escolhaAdicionarPrato == 2 || escolhaAdicionarPrato == 3);

                        break;

                    case 2:
                        do{
                            printf("\n");
                            printf("+-------------------------------------+\n");
                            printf("                                     \n");
                            printf("  Nome: %s\n", novaEmpresa.nome);
                            printf("  Email: %s\n", novaEmpresa.cnpj);
                            printf("  Senha: %s\n", novaEmpresa.senha);
                            printf("                                     \n");
                            printf("+-------------------------------------+\n");
                            printf("     Digite 1 para voltar: ");
                            scanf("%d", &sair);

                            if(sair != 1){
                                ErroMensagem();
                            }
                            getchar();
                            system("cls");
                        }while(sair != 1);
                        break;


                }while(sair == 1);

            }


        }while(opcao != 3);

        if(opcao == 3){
            liberarListaEmpresas(Empresas);
            liberarListaPratos(&novaEmpresa);
            free(Empresas);

            exit(0);
        }

    }

return 0;
}
