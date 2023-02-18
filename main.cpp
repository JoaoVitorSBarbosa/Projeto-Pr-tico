/* PROJETO PRATICO IALG
    Nomes: Ana Elis Naves / Beatriz Euzébio / Pedro Ernesto
    */

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
struct registro {
    int ID = 0;
    char  descritor[40];
    char certificado[10];
    float precoCompra = 0;
    float precoVenda = 0;
};

int binRecursivaID(registro vetor[], int inicio, int fim, int buscado);

int Converte() {                        // converte o arquivo em binario
    std::ifstream infile("base8.csv");  // Abrir o arquivo CSV
    std::ofstream outfile(
        "base08.bin",
        std::ios::out | std::ios::binary);  // Criar o arquivo binário

    std::string linha;
    while (std::getline(infile, linha)) {  // Ler cada linha do arquivo CSV
        int inteiro;
        std::string texto;
        std::stringstream ss(linha);
        std::getline(ss, texto, ',');  // Extrair o valor inteiro
        inteiro = std::stoi(texto);
        std::getline(ss, texto);  // Extrair a string
        outfile.write(
            reinterpret_cast<char*>(&inteiro),
            sizeof(int));  // Escrever o valor inteiro no arquivo binário
        outfile.write(texto.c_str(),
                      texto.size());  // Escrever a string no arquivo binário
    }

    infile.close();   // Fechar o arquivo CSV
    outfile.close();  // Fechar o arquivo binário
    return 0;
}

void swap(registro vetor[], int pos1, int pos2) {
    registro aux = vetor[pos1];
    vetor[pos1] = vetor[pos2];
    vetor[pos2] = aux;
}

int partID(registro vetor[], int p, int r) {  // Lomuto
    int pivo = vetor[r].ID;
    int j = p;
    int k;
    for (k = p; k < r; k++) {
        if (vetor[k].ID <= pivo) {
            swap(vetor, j, k);
            j++;
        }
    }
    swap(vetor, j, r);
    return j;
}

int partPV(registro vetor[], int p, int r) {  // Lomuto
    int pivo = vetor[r].precoVenda;
    int j = p;
    int k;
    for (k = p; k < r; k++) {
        if (vetor[k].precoVenda <= pivo) {
            swap(vetor, j, k);
            j++;
        }
    }
    swap(vetor, j, r);
    return j;
}

void quickSortID(registro vetor[], int pos_pivo, int fim) {
    int pos_novo_pivo;
    if (pos_pivo < fim) {
        pos_novo_pivo = partID(vetor, pos_pivo, fim);
        quickSortID(vetor, pos_pivo, pos_novo_pivo - 1);
        quickSortID(vetor, pos_novo_pivo + 1, fim);
    }
}

void quickSortprecoVenda(registro vetor[], int pospivo, int fim) {
    float posnovopivo;
    if (pospivo < fim) {
        posnovopivo = partPV(vetor, pospivo, fim);
        quickSortprecoVenda(vetor, pospivo, posnovopivo - 1);
        quickSortprecoVenda(vetor, posnovopivo + 1, fim);
    }
}

int menu() {  // Criado um menu onde o usuário escolhe uma opcao numerica.
    int opc;
    cout << "- - - - - - - -  MENU  - - - - - - - - -" << endl << endl;
    cout << " [ 1 ] -  Cadastrar " << endl;
    cout << " [ 2 ] -  Listar " << endl;
    cout << " [ 3 ] -  Pesquisar um item " << endl;
    cout << " [ 4 ] -  Excluir " << endl;
    cout << " [ 5 ] -  Sair " << endl << endl;
    cout << "Digite sua opcao: ";
    cin >> opc;
    return opc;
}

int binRecursivaID(registro vetor[], int inicio, int fim, int buscado) {
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (buscado > vetor[meio].ID)
            return binRecursivaID(vetor, meio + 1, fim, buscado);
        else if (buscado < vetor[meio].ID)
            return binRecursivaID(vetor, inicio, meio - 1, buscado);
        else
            return meio;
    }
    return -1;
}

int buscaDescritor(registro vetor[], string buscado) {
    while (false) { 
    }
}

void apaga(registro vetor[], int pos) {  // marca id negativo
    int aux = vetor[pos].ID;
    vetor[pos].ID = -1 * aux;
}

void imprime(registro vetor[], int pos,
             int n) {  // loop de couts a partir da posicao dada

    for (int i = pos; i < n; i++) {
        cout << vetor[i].ID << " " << vetor[i].descritor << " "
             << vetor[i].certificado << " " << vetor[i].precoCompra << " "
             << vetor[i].precoVenda << ";" << endl;
    }
}

void insere(registro novo) {}  // ordenado

int main() {
    uint8_t opcao = menu();
    registro vetor[50];


    switch (opcao) {
        case 1: insere (vetor, i);
            break;
        case 2: imprime (vetor, i);
            break;
        case 3:  buscaDescritor(vetor, i);
            break;
        case 4: apaga(vetor, i);
            break;
    }
}