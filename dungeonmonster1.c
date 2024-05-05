#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Para getch e kbhit
#include <windows.h> // Para Sleep

#define ALTURA 10
#define LARGURA 10
#define MONSTRO_DELAY 300 // Tempo de espera entre os movimentos do monstro em milissegundos

void imprimirMapa(char mapa[][LARGURA], int jogadorX, int jogadorY, int monstroX, int monstroY) {
    system("cls"); // Limpar tela (Windows)

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == jogadorY && j == jogadorX) {
                printf("&");
            } else if (i == monstroY && j == monstroX) {
                printf("M");
            } else {
                printf("%c", mapa[i][j]);
            }
        }
        printf("\n");
    }
}

bool podeMover(char mapa[][LARGURA], int x, int y) {
    return mapa[y][x] != '*';
}

void moverJogador(char direcao, int *jogadorX, int *jogadorY, char mapa[][LARGURA]) {
    int novoX = *jogadorX, novoY = *jogadorY;
    switch (direcao) {
        case 'w':
            novoY = *jogadorY - 1;
            break;
        case 's':
            novoY = *jogadorY + 1;
            break;
        case 'a':
            novoX = *jogadorX - 1;
            break;
        case 'd':
            novoX = *jogadorX + 1;
            break;
    }

    if (podeMover(mapa, novoX, novoY)) {
        *jogadorX = novoX;
        *jogadorY = novoY;
    }
}

int main() {
    char mapa[ALTURA][LARGURA] = {
        "**********",
        "*        *",
        "*    *   *",
        "*    *   *",
        "*    *   *",
        "*    *   *",
        "*    *   *",
        "*    *   *",
        "*        *",
        "**********"
    };
    int jogadorX = 1, jogadorY = 1; // Posição inicial do jogador
    int monstroX = 8, monstroY = 8; // Posição inicial do monstro
    char movimento;
    bool jogadorMoveu = false;

    // Loop principal do jogo
    while (true) {
        imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);

        // Verificar se o jogador pressionou uma tecla para se mover
        if (kbhit()) {
            movimento = getch();
            moverJogador(movimento, &jogadorX, &jogadorY, mapa);
            jogadorMoveu = true;
        }

        // Movimentar o monstro apenas se o jogador se moveu
        if (jogadorMoveu) {
            // Movimentar o monstro em direção ao jogador
            if (jogadorX < monstroX && podeMover(mapa, monstroX - 1, monstroY)) {
                monstroX--;
            } else if (jogadorX > monstroX && podeMover(mapa, monstroX + 1, monstroY)) {
                monstroX++;
            }
            if (jogadorY < monstroY && podeMover(mapa, monstroX, monstroY - 1)) {
                monstroY--;
            } else if (jogadorY > monstroY && podeMover(mapa, monstroX, monstroY + 1)) {
                monstroY++;
            }

            jogadorMoveu = false; // Resetar a flag de movimento do jogador
        }

        // Verificar se o jogador foi pego pelo monstro
        if (jogadorX == monstroX && jogadorY == monstroY) {
            printf("\nVoce foi pego pelo monstro!\n");
            break; // Encerrar o jogo
        }

        // Aguardar um pouco antes de permitir o próximo ciclo do loop
        Sleep(MONSTRO_DELAY); // Ajuste o tempo conforme necessário para tornar o monstro mais lento
    }

    return 0;
}

