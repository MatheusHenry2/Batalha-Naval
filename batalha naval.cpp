#include <iostream>
#include <iomanip>
using namespace std;

char startGame(char mapa[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            mapa[i][j] = '_';
    }
}

char printGame(char mapa[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        cout << endl;
        for (int j = 0; j < 8; j++)
            cout << setw(4) << mapa[i][j];
    }
}

char insertGame(char mapa[8][8], int posicaoLinhaJogada, int posicaoColunaJogada)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (posicaoLinhaJogada == i && posicaoColunaJogada == j)
                mapa[i][j] = 'N';
        }
    }
}

char camuflaMapa(char mapa[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            mapa[i][j] = 'A';
    }
}

int isEncontrouNavio(int naviosLinhas[5], int naviosColunas[5], int linha, int coluna)
{
    for (int i = 0; i < 5; i++)
    {
        if (naviosLinhas[i] == linha && naviosColunas[i] == coluna)
        {
            naviosLinhas[i] = 999;
            naviosColunas[i] = 999;
            return true;
        }
    }
    return false;
}

char isValidPosicaoDistance(char mapa[8][8], int posicaoLinhaTentativa, int posicaoColunaTentativa)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (posicaoLinhaTentativa == i && posicaoColunaTentativa == j)
            {
                if (mapa[posicaoLinhaTentativa][posicaoColunaTentativa] == 'N')
                    return false;

                if (mapa[i - 1][j] == 'N')
                    return false;

                if (mapa[i + 1][j] == 'N')
                    return false;

                if (mapa[i][j - 1] == 'N')
                    return false;

                if (mapa[i][j + 1] == 'N')
                    return false;
            }
        }
    }
    return true;
}

int main()
{
    char mapa[8][8];
    int navios = 0, posicaoLinha, posicaoColuna, naviosLinhas[5], naviosColunas[5], jogadas = 10, acertos = 0, interacao = 0;

    cout << "\n  ---- Jogo de batalha naval ----" << endl;

    startGame(mapa);
    printGame(mapa);

    do
    {
        cout << "\n\n        Jogador 1 posicone o " << navios + 1 << endl;
        do
        {
            cout << "\n Informe a linha para o navio (0 a 7):";
            cin >> posicaoLinha;
            cout << "\n Informe a coluna para o navio (0 a 7):";
            cin >> posicaoColuna;
        } while (posicaoLinha > 7 || posicaoColuna > 7 || posicaoLinha < 0 || posicaoColuna < 0);
        if (isValidPosicaoDistance(mapa, posicaoLinha, posicaoColuna))
        {
            naviosLinhas[interacao] = posicaoLinha;
            naviosColunas[interacao] = posicaoColuna;
            insertGame(mapa, posicaoLinha, posicaoColuna);
            navios = navios + 1;
            interacao = interacao + 1;
        }
        else
            cout << "\n Respeite a distancia das celulas!" << endl;
        system("clear");
        printGame(mapa);

    } while (navios < 5);

    cout << "\nCamuflando mapa para jogador 2" << endl;
    camuflaMapa(mapa);
    system("clear");
    cout << "\n --- Bem vindo jogador 2 Tente encontrar os navios ---" << endl;

    do
    {
        printGame(mapa);
        cout << "\n Jogador 2 restam " << jogadas << " Tentativas " << endl;
        do
        {
            cout << "\n Informe a linha para encontrar o barco: ";
            cin >> posicaoLinha;
            cout << "\n Informe a coluna para tentar encontrar o navio:";
            cin >> posicaoColuna;
        } while (posicaoLinha > 7 || posicaoColuna > 7 || posicaoLinha < 0 || posicaoLinha < 0);

        if (isEncontrouNavio(naviosLinhas, naviosLinhas, posicaoLinha, posicaoColuna))
        {
            insertGame(mapa, posicaoLinha, posicaoColuna);
            cout << "\n 1 Navio encontrando parabens!" << endl;
            jogadas = jogadas + 1;
            acertos = acertos + 1;
        }
        if (acertos == 5)
            break;
        else
            jogadas = jogadas - 1;
        cout << "\n TOtal de acertos do jogo : " << acertos << endl;

    } while (jogadas > 0);

    if (acertos == 5)
        cout << "\n Você ganhou o jogo parabens" << endl;

    else
        cout << "\n Voce perdeu sorry ruim, encontrou apenas" << acertos << "navios" << endl;
}