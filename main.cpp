/* PROJETO PRATICO IALG
    Nomes: Ana Elis Naves / Beatriz Euzébio / Pedro Ernesto
    */

#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
struct registro {
    long ID = 0;
    string descritor = "";
    string certificado = "";
    float precoCompra = 0;
    float precoVenda = 0;
};

void clearScreen() {
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
}

unsigned int getNumRegistros() {
    string linha;
    ifstream infile("base8.csv");
    int numRegistros;
    while (getline(infile, linha)) {  // Ler cada linha do arquivo CSV
        numRegistros++;
    }
    infile.close();
    return numRegistros;
}

string leCelula(ifstream &arquivo) {
    string celula;
    char c;
    arquivo.read(&c, 1);
    if (c == '\"') {
        arquivo.read(&c, 1);  // elimina a aspas
        do {
            celula += c;
            arquivo.read(&c, 1);
        } while (c != '\"');
        arquivo.read(&c, 1);  // elimina o ";"
    } else {
        do {
            celula += c;
            arquivo.read(&c, 1);
        } while (c != ';' and c != '\n' and !arquivo.eof());
    }
    return celula;
}

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
            reinterpret_cast<char *>(&inteiro),
            sizeof(int));  // Escrever o valor inteiro no arquivo binário
        outfile.write(texto.c_str(),
                      texto.size());  // Escrever a string no arquivo binário
    }

    infile.close();   // Fechar o arquivo CSV
    outfile.close();  // Fechar o arquivo binário
    return 0;
}

void lerArquivo(registro produtos[]) {
    ifstream infile("base8.csv");  // Abrir o arquivo CSV
    int coluna = 0;
    int linha;
    while (!infile.eof()) {  // Ler cada linha do arquivo CSV
        // cout << linha << endl;
        string celula = leCelula(infile);
        switch (coluna) {
            case 0:
                produtos[linha].ID = stol(celula);
                break;
            case 1:
                produtos[linha].descritor = celula;
                break;
            case 2: {
                produtos[linha].certificado = celula;
                break;
            }
            case 3: {
                // cout << celula << endl;
                if (celula.find(',') < celula.length())
                    celula.replace(celula.find(','), 1, ".");
                produtos[linha].precoCompra = stof(celula);
                break;
            }
            case 4: {
                // cout << celula << endl;
                if (celula.find(',') < celula.length())
                    celula.replace(celula.find(','), 1, ".");
                produtos[linha].precoVenda = stof(celula);
                linha++;
                break;
            }
            default:
                break;
        }

        if (coluna == 4) {
            coluna = 0;
        } else {
            coluna++;
        }
    }

    infile.close();
}

void gravarArquivo() {  // ordenado
    registro novoRegistro;
    ofstream outfile("base08.bin", std::ios::out | std::ios::binary);

    cout << "Insira o ID" << endl;
    cin >> novoRegistro.ID;
    cout << "Insira o descritor" << endl;
    cin >> novoRegistro.descritor;
    cout << "Insira o certificado" << endl;
    cin >> novoRegistro.certificado;
    cout << "Insira o precoCompra" << endl;
    cin >> novoRegistro.precoCompra;
    cout << "Insira o precoVenda" << endl;
    cin >> novoRegistro.precoVenda;
    clearScreen();

    int posFinal = getNumRegistros() + 1;
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
    int i = 0;
    bool cond = false;
    while (i < getNumRegistros() && !cond) {
        if (vetor[i].descritor == buscado) {
            cond = true;
            return i;
        }
    }
    return -1;
}

void apaga(registro vetor[], int pos) {  // marca id negativo
    int aux = vetor[pos].ID;
    vetor[pos].ID = -1 * aux;
}

void imprimeEspacos(int qtdeEspacos) {
    for(int i = 0; i < qtdeEspacos; i++) {
        cout << " ";
    }
}
void imprime(registro vetor[], int pos,
             int n) {  // loop de couts a partir da posicao dada
    cout << "    ID \t \t| \t \t \t \t \t \t Descritor\t\t\t \t\t \t        | \t Certificado     | Preço Compra  |  Preço Venda  |"<<endl<<endl;
    for (int i = pos; i < n; i++) {
        if (vetor[i].ID > 0) {
            cout << vetor[i].ID << "  " << " |";
            cout << " " << vetor[i].descritor;
            imprimeEspacos(110 - strlen(vetor[i].descritor.c_str()));
            cout << "|";
            cout << "\t" << vetor[i].certificado << "\t" << " |";
            cout << "\t"<< vetor[i].precoCompra << "\t" << " |";
            cout << "\t"<< vetor[i].precoVenda << "\t" << " |";
            cout << "\n";
        }
    }
}

int main() {
    uint8_t opcao = menu();
    registro produtos[getNumRegistros()];

    lerArquivo(produtos);

    while (opcao != 5) {
        switch (opcao) {
            case 1:
                gravarArquivo();
                break;
            case 2:
                imprime(produtos, 0, getNumRegistros());
                break;
            case 3:
                buscaDescritor(produtos, "");
                break;
            case 4:
                apaga(produtos, 0);
                break;
        }
        opcao = menu();
    }
    //clearScreen();
    cout << "Obrigado pela preferência!";
}