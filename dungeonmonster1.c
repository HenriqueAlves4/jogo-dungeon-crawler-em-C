#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Para getch e kbhit
#include <windows.h> // Para Sleep

#define ALTURA 10
#define LARGURA 10
#define MONSTRO_DELAY 100 // Tempo de espera entre os movimentos do monstro em milissegundos

void imprimirMapa(char mapa[][LARGURA], int jogadorX, int jogadorY, int monstroX, int monstroY) {
    system("cls"); // Limpar tela (Windows)

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == jogadorY && j == jogadorX) {
                printf("&");
            } else if (i == monstroY && j == monstroX) {
                printf("X"); // Caractere do monstro alterado para 'X'
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

void moverMonstroAleatorio(int *monstroX, int *monstroY, char mapa[][LARGURA]) {
    // Gera uma direção de movimento aleatória (cima, baixo, esquerda, direita)
    int direcao = rand() % 4;
    int novoX = *monstroX, novoY = *monstroY;

    switch (direcao) {
        case 0: // Cima
            novoY = *monstroY - 1;
            break;
        case 1: // Baixo
            novoY = *monstroY + 1;
            break;
        case 2: // Esquerda
            novoX = *monstroX - 1;
            break;
        case 3: // Direita
            novoX = *monstroX + 1;
            break;
    }

    if (podeMover(mapa, novoX, novoY)) {
        *monstroX = novoX;
        *monstroY = novoY;
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
        "*    *   *",
        "**********"
    };
    int jogadorX = 1, jogadorY = 1; // Posição inicial do jogador
    int monstroX = 8, monstroY = 8; // Posição inicial do monstro
    char movimento;
    bool jogadorMoveu = false;

    // Loop principal do jogo
    imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);

    while (true) {
        // Verificar se o jogador pressionou uma tecla para se mover
        if (kbhit()) {
            movimento = getch();
            moverJogador(movimento, &jogadorX, &jogadorY, mapa);
            jogadorMoveu = true;
            imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);
        }

        // Movimentar o monstro apenas se o jogador se moveu
        if (jogadorMoveu) {
            moverMonstroAleatorio(&monstroX, &monstroY, mapa);
            jogadorMoveu = false; // Resetar a flag de movimento do jogador
        }

        // Verificar se o jogador foi pego pelo monstro
        if (jogadorX == monstroX && jogadorY == monstroY) {
            printf("\nVoce foi pego pelo monstro! Pressione qualquer tecla para reiniciar...\n");
            getch(); // Aguardar entrada do jogador
            jogadorX = 1;
            jogadorY = 1;
            monstroX = 8;
            monstroY = 8;
            imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);
        }

        // Aguardar um pouco antes de permitir o próximo ciclo do loop
        Sleep(MONSTRO_DELAY); // Ajuste o tempo conforme necessário para tornar o monstro mais lento
    }

    return 0;
}
