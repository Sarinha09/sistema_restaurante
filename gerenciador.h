struct Prato {
    char nome[50];
    float preco;
    struct Prato *proxima;
};
struct Cliente{
    char nome[30];
    char email[30];
    char senha[30];
};

struct Empresa {
    char cnpj[15];
    char nome[30];
    char senha[10];
    char endereco[30];
    char categoria[15];
    int tempoEntrega;
    struct Prato *pratos;  // Lista de pratos
    int numPratos;
    struct Empresa *proxima;
};


struct ListaEmpresa { //controle de lista
    struct Empresa *inicio;
    struct Empresa *fim;
    int tamanho;
};

struct CarrinhoItem{
    char nome[50];
    float preco;
    int quantidade;
    struct CarrinhoItem* proxima;
};

struct Carrinho {
    struct CarrinhoItem* inicio;
    struct CarrinhoItem* fim;
    int tamanho;
    float valorTotal;
};

//cadastro
void cadastroCliente(struct Cliente *cliente); //salva no arquivo
void cadastroEmpresa(struct Empresa *empresa); //salva no arquivo
int verificarLoginCliente(char *arquivo, char *email, char *senha, struct Cliente *cliente);
int loginEmpresa(struct ListaEmpresa *lista, char *CNPJ, char *senha, struct Empresa *empresa);

//lista empresa
struct ListaEmpresa* criar();
int inserirEmpresa(struct ListaEmpresa *lista, struct Empresa *novaEmpresa); //insere empresa na lista
void liberarListaEmpresas(struct ListaEmpresa *lista); //libera lista
int listarEmpresa(struct ListaEmpresa *lista, char *categoriaDesejada); //mostra as empresas da categoria escolhida pelo usuario
int listarTodasEmpresa(struct ListaEmpresa *lista); // lista todas as empresas diponiveis
void carregarEmpresas(const char *arquivo, struct ListaEmpresa *lista); //carrega as empresas do arquivo e insere na lista

//lista prato
int adicionarPrato(struct Empresa *empresa, struct Prato *novoPrato); //adiciona prato na lista
int listarPratos(struct Empresa *empresa); //mostra os pratos de uma empresa escolhida pelo usuario
void salvarPratos(struct Empresa *empresa); //salva os pratos no arquivo
void carregarPratos(struct Empresa *empresa); //carrega os pratos do arquivo e insere na lista
void liberarListaPratos(struct Empresa *empresa); //libera pratos
int removerPrato(struct Empresa *empresa, char *nomePrato); // remover prato

//lista carrinho
struct Carrinho* criarCarrinho();
struct Empresa* selecionarRestaurante(struct ListaEmpresa *lista, int opcao); //faz uma busca por CNPJ, do restaurante escolhido pelo usuario (para vizualizar os pratos do restaurante)
struct Prato* buscarPrato(struct Empresa *empresa, const char *nomePrato); //faz uma busca do prato por nome, escolhido pelo usuario (para adicionar no carrinho)
int adicionarCarrinho(struct Carrinho *carrinho, struct Prato *prato, int quantidade); //inserir prato escolhido na lista carrinho
int listarCarrinho(struct Carrinho *carrinho);
int removerPratoDoCarrinho(struct Carrinho *carrinho, const char *nomePrato);



//EXTRAS
enum Cores {
    PRETO = 0,
    AZUL = 1,
    VERDE = 2,
    CIANO = 3,
    VERMELHO = 4,
    MAGENTA = 5,
    AMARELO = 6,
    BRANCO = 7
};

void definirCorTexto(int corTexto);

char *gerarPIX();
int BarraCarregamento();
int VerificarCNPJ(struct ListaEmpresa *lista, char *cnpj);
void TempoEntrega(struct Empresa *empresa);
void ErroMensagem();
