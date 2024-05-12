#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Para getch e kbhit
#include <windows.h> // Para Sleep

#define MAPA_ALTURA 10
#define MAPA_LARGURA 20
#define SEGUNDO_MAPA_ALTURA 20
#define SEGUNDO_MAPA_LARGURA 40

// Função para imprimir o mapa
void printMap(char map[MAPA_ALTURA][MAPA_LARGURA], int playerX, int playerY) {
    system("cls");

    for (int i = 0; i < MAPA_ALTURA; i++) {
        for (int j = 0; j < MAPA_LARGURA; j++) {
            if (i == playerY && j == playerX) {
                printf("&");
            } else {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para imprimir o segundo mapa
void printSecondMap(char map[SEGUNDO_MAPA_ALTURA][SEGUNDO_MAPA_LARGURA], int playerX, int playerY) {
    system("cls");

    for (int i = 0; i < SEGUNDO_MAPA_ALTURA; i++) {
        for (int j = 0; j < SEGUNDO_MAPA_LARGURA; j++) {
            if (i == playerY && j == playerX) {
                printf("&");
            } else {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
}

bool canMove(char map[][SEGUNDO_MAPA_LARGURA], int x, int y) {
    return map[y][x] != '*';
}

int main(int argc, char *argv[]) {
    int numero;

    do {
        printf("\n\n\t\t\t\t\t\tDungeon Crawler\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t1 - Jogar\n\n\n\n\n");
        printf("\t\t\t\t\t\t2 - Tutorial\n\n\n\n\n");
        printf("\t\t\t\t\t\t3 - Sair\n\n\n\n\n");
        printf("\t\t\t\t\t\tEscolha a opcao desejada: ");
        scanf("%d", &numero);
        
        switch (numero) {
            case 1:
                system("cls");
                printf("\n\n\n\n\n\n\t\t\t\t\t\tIniciando jogo...\n\n\n\n\n\n");
                Sleep(500); 
                int x = 1, y = 1; // Iniciar o jogador na posição correta
                int chavePegou = 0; // Indica se o jogador pegou a chave
                int portaAberta = 0; // Indica se a porta está aberta
                
        char mapa[MAPA_ALTURA][MAPA_LARGURA] = {
                    "* * * * * * * * * *",
                    "* **              D",
                    "*  **** ******* ***",
                    "*   *   **      * *",
                    "*        * *** *  *",
                    "*   * ****   * *  *",
                    "*                 *",
                    "*  ************** *",
                    "* *@              *",
                    "* * * * * * * * * *"
                };

                while(1) {
                    system("cls");
                    printMap(mapa, x, y);
                    
                    char move = getch();
                    
                    switch(move) {
                        case 'w':
                            if(y > 1 && mapa[y-1][x] != '*' && mapa[y-1][x] != 'D') y--;
                            break;
                        case 's':
                            if(y < MAPA_ALTURA - 2 && mapa[y+1][x] != '*' && mapa[y+1][x] != 'D') y++;
                            break;
                        case 'a':
                            if(x > 1 && mapa[y][x-1] != '*' && mapa[y][x-1] != 'D') x--;
                            break;
                        case 'd':
                            if(x < MAPA_LARGURA - 2 && mapa[y][x+1] != '*' && mapa[y][x+1] != 'D') x++;
                            break;
                        case 'q':
                            return 0;
                        case 'i':
                            if (mapa[y][x] == '@') {
                                chavePegou = 1;
                                mapa[y][x] = ' ';
                            }
                            break;
                    }

                    // Se o jogador tem a chave e está em frente à porta, abre a porta
                    if (chavePegou) {
                        if (move == 'w' && mapa[y-1][x] == 'D') {
                            portaAberta = 1;
                            mapa[y-1][x] = '='; // Abre a porta
                        } else if (move == 's' && mapa[y+1][x] == 'D') {
                            portaAberta = 1;
                            mapa[y+1][x] = '='; // Abre a porta
                        } else if (move == 'a' && mapa[y][x-1] == 'D') {
                            portaAberta = 1;
                            mapa[y][x-1] = '='; // Abre a porta
                        } else if (move == 'd' && mapa[y][x+1] == 'D') {
                            portaAberta = 1;
                            mapa[y][x+1] = '='; // Abre a porta
                        }
                    }

                    // Se a porta estiver aberta, o jogador pode atravessar
                    if (portaAberta && mapa[y][x] == '=') {
                        printf("\nVoce concluiu a primeira fase!\n");
                        printf("Pressione qualquer tecla para continuar...\n");
                        getch();
                        system("cls");
                        break; // Encerra o loop do jogo
                    }
                }

                // Iniciar o segundo mapa após a conclusão do primeiro
                printf("\n\n\n\n\n\n\t\t\t\t\t\tIniciando segunda fase...\n\n\n\n\n\n");
                Sleep(500);
                x = 1, y = 1;
                chavePegou = 0;
                portaAberta = 0;

                char segundoMapa[SEGUNDO_MAPA_ALTURA][SEGUNDO_MAPA_LARGURA] = {
                    "* * * * * * * * * * * * * * * * * * * *",
                    "* #            #************      *   *",
                    "*  #                              *   *",
                    "*              #*************#    *   *",
                    "*## #********# *             *    *   *",
                    "* #  #    *  * *##**************# *   *",
                    "*###  #   D  * *                * *###*",
                    "*#### #   *  * *          X     *     *",
                    "*#### #   *  * *               * * ****",
                    "*####  #  *                    * * *  *",
                    "*##### #  ***#            #****    *  *",
                    "*##    #     #**********#        # *  *",
                    "*   ####      *         *  #** ***  * *",
                    "* ##   <-     *         *  *   *    * *",
                    "* # Boa sorte *   *******# *   *   *  *",
                    "* #           *            *   *  *   *",
                    "* ############# ############   *@**   *",
                    "* #   #   #     #              ****   *",
                    "*   #   #   # #O#                     *",
                    "* * * * * * * * * * * * * * * * * * * *"
                };

                int espinhosTocados = 0; // Contador de vezes que o jogador tocou nos espinhos

                while (1) {
                    system("cls");
                    printSecondMap(segundoMapa, x, y);
                    
                    char move = getch();
                    
                    switch(move) {
                        case 'w':
                            if(y > 1 && segundoMapa[y-1][x] != '*' && segundoMapa[y-1][x] != 'D') y--;
                            break;
                        case 's':
                            if(y < SEGUNDO_MAPA_ALTURA - 2 && segundoMapa[y+1][x] != '*' && segundoMapa[y+1][x] != 'D') y++;
                            break;
                        case 'a':
                            if(x > 1 && segundoMapa[y][x-1] != '*' && segundoMapa[y][x-1] != 'D') x--;
                            break;
                        case 'd':
                            if(x < SEGUNDO_MAPA_LARGURA - 2 && segundoMapa[y][x+1] != '*' && segundoMapa[y][x+1] != 'D') x++;
                            break;
                        case 'q':
                            return 0;
                        case 'i':
                            if (segundoMapa[y][x] == '@') {
                                chavePegou = 1;
                                segundoMapa[y][x] = ' ';
                            }
                            break;
                    }

                    // Se o jogador tem a chave e está em frente à porta, abre a porta
                    if (chavePegou) {
                        if (move == 'w' && segundoMapa[y-1][x] == 'D') {
                            portaAberta = 1;
                            segundoMapa[y-1][x] = '='; // Abre a porta
                        } else if (move == 's' && segundoMapa[y+1][x] == 'D') {
                            portaAberta = 1;
                            segundoMapa[y+1][x] = '='; // Abre a porta
                        } else if (move == 'a' && segundoMapa[y][x-1] == 'D') {
                            portaAberta = 1;
                            segundoMapa[y][x-1] = '='; // Abre a porta
                        } else if (move == 'd' && segundoMapa[y][x+1] == 'D') {
                            portaAberta = 1;
                            segundoMapa[y][x+1] = '='; // Abre a porta
                        }
                    }

                    // Se a porta estiver aberta, o jogador pode atravessar
                    if (portaAberta && segundoMapa[y][x] == '=') {
                        printf("\nVoce concluiu a segunda fase!\n");
                        printf("Pressione qualquer tecla para voltar ao menu principal...\n");
                        getch();
                        system("cls");
                        break; // Encerra o loop do jogo
                    }

                    // Verificar se o jogador tocou no espinho
                    if (segundoMapa[y][x] == '#') {
                        printf("\nVoce tocou no espinho!\n");
                        printf("Pressione qualquer tecla para reiniciar...\n");
                        getch(); // Aguardar entrada do jogador
                        espinhosTocados++;
                        x = 1;
                        y = 1;
                        if (espinhosTocados == 3) {
                            printf("\nVoce tocou no espinho 3 vezes! Voce perdeu!\n");
                            printf("Pressione qualquer tecla para voltar ao menu principal...\n");
                            getch();
                            system("cls");
                            break;
                        }
                    }
                }
                break;
            case 2:
                system("cls"); 
                printf("\n\n\n\t\t\t\t\t\tDungeon Crawler - Tutorial\n");
                printf("\n\n\t\t\tBem-vindo ao Dungeon Crawler! Aqui esta um resumo das funcoes basicas do jogo:\n\n");
                printf("\t\t\t\tControles:\n");
                printf("\t\t\t\tW: Mover para cima.\n");
                printf("\t\t\t\tA: Mover para a esquerda.\n");
                printf("\t\t\t\tS: Mover para baixo.\n");
                printf("\t\t\t\tD: Mover para a direita.\n");
                printf("\t\t\t\tI: Interagir com objetos.\n\n");
                printf("\t\t\t\tSimbolos:\n");
                printf("\t\t\t\t&: Voce, o jogador.\n");
                printf("\t\t\t\t*: Parede, voce nao pode atravessar.\n");
                printf("\t\t\t\t@: Chave para abrir a porta.\n");
                printf("\t\t\t\tD: Porta fechada.\n");
                printf("\t\t\t\t=: Porta aberta depois de pegar a chave.\n");
                printf("\t\t\t\t#: Espinhos, reiniciam a fase se tocados.\n");
                printf("\t\t\t\t>: Teletransporte, leva voce de um lugar para outro.\n");
                printf("\t\t\t\tX: Monstro nivel 1, reinicia a fase se tocado.\n");
                printf("\t\t\t\tV: Monstro nivel 2, inteligente e perigoso.\n\n");
                printf("\t\t\t\tPressione qualquer tecla para voltar ao menu principal...");
                getch();
                system("cls"); 
                break;
            case 3:
                system("cls");
                printf("\n\n\n\n\n\n\t\t\t\t\t\tObrigado por jogar!!\n\n\n\n\n\n\t\t\t\t\t\tFechando jogo...\n");
                return 0;
            default:
                printf("\n\n\t\t\t\t\t\tOpcao invalida! Escolha novamente: ");
                getch();
                system("cls");
                break;
        }
    } while (numero >= 1 || numero <= 3);
    system("pause"); 
    return 0;
}
