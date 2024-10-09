#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Estrutura de um nodo da lista encadeada
struct Nodo
{
    string dado;   // Armazena a palavra
    Nodo* proximo; // Ponteiro para o pr�ximo nodo na lista
};

// Ponteiro para o in�cio da lista
Nodo* inicio = nullptr;

// Fun��o para inicializar a lista
void Lista_Construtor()
{
    inicio = nullptr;
}

// Fun��o para liberar a mem�ria ocupada pela lista
void Lista_Destrutor()
{
    while (inicio != nullptr)
    {
        Nodo* temp = inicio;
        inicio = inicio->proximo;
        delete temp;
    }
}

// Fun��o para inserir uma palavra ordenadamente e sem repeti��o
bool Lista_InserirOrdenado(const string &palavra)
{
    Nodo* novoNodo = new (nothrow) Nodo;
    if (!novoNodo) return false; // Falha na aloca��o de mem�ria

    novoNodo->dado = palavra;
    novoNodo->proximo = nullptr;

    // Se a lista estiver vazia ou se a nova palavra for menor que o primeiro elemento
    if (inicio == nullptr || inicio->dado > palavra)
    {
        novoNodo->proximo = inicio;
        inicio = novoNodo;
        return true;
    }

    // Percorrer a lista para encontrar a posi��o de inser��o ordenada
    Nodo* atual = inicio;
    while (atual->proximo != nullptr && atual->proximo->dado < palavra)
    {
        atual = atual->proximo;
    }

    // Verifica se a palavra j� existe para evitar duplicatas
    if (atual->dado == palavra || (atual->proximo != nullptr && atual->proximo->dado == palavra))
    {
        delete novoNodo; // Libera o nodo rec�m-criado, pois � uma duplicata
        return false;
    }

    novoNodo->proximo = atual->proximo;
    atual->proximo = novoNodo;
    return true;
}

// Fun��o para remover um elemento do in�cio da lista
bool Lista_Remover_Inicio(string &palavra)
{
    if (inicio == nullptr) return false; // Lista vazia

    Nodo* temp = inicio;
    palavra = inicio->dado;
    inicio = inicio->proximo;
    delete temp;
    return true;
}

// Fun��o para remover um elemento do fim da lista
bool Lista_Remover_Fim(string &palavra)
{
    if (inicio == nullptr) return false; // Lista vazia

    if (inicio->proximo == nullptr)   // Se houver apenas um elemento
    {
        palavra = inicio->dado;
        delete inicio;
        inicio = nullptr;
        return true;
    }

    // Percorre at� o pen�ltimo elemento
    Nodo* atual = inicio;
    while (atual->proximo->proximo != nullptr)
    {
        atual = atual->proximo;
    }

    palavra = atual->proximo->dado;
    delete atual->proximo;
    atual->proximo = nullptr;
    return true;
}

// Fun��o para buscar um elemento pela posi��o
bool Lista_BuscarPelaPosicao(string &palavra, int posicao)
{
    Nodo* atual = inicio;
    int contador = 0;

    while (atual != nullptr)
    {
        if (contador == posicao)
        {
            palavra = atual->dado;
            return true;
        }
        atual = atual->proximo;
        contador++;
    }
    return false; // Posi��o n�o encontrada
}

// Fun��o para obter o tamanho da lista
int Lista_Tamanho()
{
    int tamanho = 0;
    Nodo* atual = inicio;
    while (atual != nullptr)
    {
        tamanho++;
        atual = atual->proximo;
    }
    return tamanho;
}

// Fun��o para converter uma string para letras min�sculas (case-insensitive)
void toLowerCase(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Fun��o para limpar a tela
void limparTela()
{
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Unix/Linux
#endif
}

// Fun��o para exibir o cabe�alho do programa
void exibirCabecalho()
{
    cout << "========================================\n";
    cout << "Nome do aluno: Osvanir Jose Viana\n";
    cout << "Objetivo do programa: Implementar uma lista encadeada que armazene palavras, permitindo insercoes ordenadas e exclusoes.\n";
    cout << "Como deve ser feita a entrada de dados: O usuario deve inserir uma palavra por vez.\n";
    cout << "Resultado da execu��o do programa: O programa permite que o usuario manipule a lista encadeada, inserindo e removendo palavras de forma ordenada e sem repeticoes.\n";
    cout << "========================================\n\n";
    cout << "\nPrograma para uso da Lista Singularmente Encadeada\n\n";
}

// Fun��o principal para demonstrar o uso da Lista
int main()
{
    string word; // Vari�vel para receber a palavra digitada pelo usu�rio
    int opcao;   // Vari�vel utilizada no menu para testar a Lista
    int posicao; // Vari�vel para retornar a posi��o onde o elemento foi encontrado

    Lista_Construtor();  // Inicializar a Lista

    // Exibir o cabe�alho
    exibirCabecalho();

    do    // Menu com op��es para testar a implementa��o da Lista
    {
        cout << "Escolha uma das opcoes abaixo.\n\n";
        cout << "Menu:\n";
        cout << "1 - Inserir palavra ordenada\n";
        cout << "2 - Remover no inicio\n";
        cout << "3 - Remover no fim\n";
        cout << "4 - Exibir elementos da Lista\n";
        cout << "5 - Sair\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();  // Limpar o buffer de entrada

        // Limpa a tela antes de exibir os resultados
        limparTela();

        switch (opcao)
        {
        case 1:  // Inserir palavra ordenada
            cout << "\nDigite a palavra: ";
            getline(cin, word);
            toLowerCase(word);  // Converte para min�sculas para compara��o case-insensitive

            if (Lista_InserirOrdenado(word))
                cout << "Palavra inserida com sucesso.\n\n";
            else
                cout << "Erro. Palavra ja existe na lista ou falta de memoria.\n\n";
            break;

        case 2:  // Remover no inicio
            if (Lista_Remover_Inicio(word))
                cout << "\nPalavra " << word << " removida\n\n";
            else
                cout << "Erro. Lista vazia.\n\n";
            break;

        case 3:  // Remover no fim
            if (Lista_Remover_Fim(word))
                cout << "\nPalavra " << word << " removida\n\n";
            else
                cout << "Erro. Lista vazia.\n\n";
            break;

        case 4:  // Exibir elementos da Lista
            cout << "\nElementos na Lista:\n\n";
            posicao = 0;
            while (Lista_BuscarPelaPosicao(word, posicao))
            {
                cout << "Posicao " << posicao << ": " << word << endl;
                posicao++;
            }
            cout << "\n";
            break;

        case 5:  // Sair
            Lista_Destrutor();
            cout << "Saindo do programa...\n";
            break;

        default:
            cout << "\nOpcao invalida.\n\n";
            break;
        }

        // Pausa para o usu�rio ver a sa�da antes de limpar a tela novamente
        if (opcao != 5)
        {
            cout << "Pressione Enter para continuar...";
            cin.ignore();
        }

        // Limpa a tela ap�s a pausa
        limparTela();

    }
    while (opcao != 5);

    return 0;
}
