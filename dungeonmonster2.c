#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Para getch e kbhit
#include <windows.h> // Para Sleep

#define ALTURA 20
#define LARGURA 20
#define MONSTRO_DELAY 950 // Tempo de espera entre os movimentos do monstro em milissegundos

void imprimirMapa(char mapa[][LARGURA], int jogadorX, int jogadorY, int monstroX, int monstroY) {
    system("cls"); // Limpar tela (Windows)

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == jogadorY && j == jogadorX) {
                printf("&");
            } else if (i == monstroY && j == monstroX) {
                printf("N");
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

void moverMonstro(char mapa[][LARGURA], int *monstroX, int *monstroY, int jogadorX, int jogadorY, int delay) {
    // Lógica de movimento mais lenta
    // Calcular a diferença entre as coordenadas do monstro e do jogador
    int difX = jogadorX - *monstroX;
    int difY = jogadorY - *monstroY;

    // Movimento do monstro na horizontal
    if (abs(difX) >= abs(difY)) {
        // Tentar mover na direção X sem colidir com paredes
        if (difX > 0 && podeMover(mapa, *monstroX + 1, *monstroY)) {
            *monstroX += 1;
        } else if (difX < 0 && podeMover(mapa, *monstroX - 1, *monstroY)) {
            *monstroX -= 1;
        }
        // Se houver uma parede na frente, tentar desviar na direção Y
        else {
            if (difY > 0 && podeMover(mapa, *monstroX, *monstroY + 1)) {
                *monstroY += 1;
            } else if (difY < 0 && podeMover(mapa, *monstroX, *monstroY - 1)) {
                *monstroY -= 1;
            }
        }
    }
    // Movimento do monstro na vertical
    else {
        // Tentar mover na direção Y sem colidir com paredes
        if (difY > 0 && podeMover(mapa, *monstroX, *monstroY + 1)) {
            *monstroY += 1;
        } else if (difY < 0 && podeMover(mapa, *monstroX, *monstroY - 1)) {
            *monstroY -= 1;
        }
        // Se houver uma parede na frente, tentar desviar na direção X
        else {
            if (difX > 0 && podeMover(mapa, *monstroX + 1, *monstroY)) {
                *monstroX += 1;
            } else if (difX < 0 && podeMover(mapa, *monstroX - 1, *monstroY)) {
                *monstroX -= 1;
            }
        }
    }

    // Aguardar um pouco antes de permitir o próximo movimento
    Sleep(delay);
}

int main() {
    char mapa[ALTURA][LARGURA] = {
        "********************",
        "*    *    *        *",
        "*    *    *        *",
        "*    * ** *        *",
        "*                  *",
        "*                  *",
        "*    ******        *",
        "*         *        *",
        "*    *    *        *",
        "********************"
    };
    int jogadorX = 1, jogadorY = 1; // Posição inicial do jogador
    int monstroX = 8, monstroY = 8; // Posição inicial do monstro
    char movimento;

    // Loop principal do jogo
    while (true) {
        imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);
        // Verificar se o jogador pressionou uma tecla para se mover
        if (kbhit()) {
            movimento = getch();
            moverJogador(movimento, &jogadorX, &jogadorY, mapa);
            imprimirMapa(mapa, jogadorX, jogadorY, monstroX, monstroY);
        }

        // Movimentar monstro
        moverMonstro(mapa, &monstroX, &monstroY, jogadorX, jogadorY, MONSTRO_DELAY);
        
        // Verificar se o jogador foi pego pelo monstro
        if (jogadorX == monstroX && jogadorY == monstroY) {
            printf("\nVoce foi pego pelo monstro! Pressione qualquer tecla para reiniciar...\n");
            getch(); // Aguardar entrada do jogador
            jogadorX = 1;
            jogadorY = 1;
            monstroX = 8;
            monstroY = 8;
        }
    }

    return 0;
}
