#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Para getch e kbhit
#include <windows.h> // Para Sleep

#define MAPA_ALTURA 10
#define MAPA_LARGURA 20
#define SEGUNDO_MAPA_ALTURA 20
#define SEGUNDO_MAPA_LARGURA 40
#define TERCEIRO_MAPA_ALTURA 40
#define TERCEIRO_MAPA_LARGURA 80

// Função para imprimir o mapa (primeira fase)
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

// Função para imprimir o segundo mapa (segunda fase)
void printSecondMap(char map[SEGUNDO_MAPA_ALTURA][SEGUNDO_MAPA_LARGURA], int playerX, int playerY, int monstroX, int monstroY) {
    system("cls");

    for (int i = 0; i < SEGUNDO_MAPA_ALTURA; i++) {
        for (int j = 0; j < SEGUNDO_MAPA_LARGURA; j++) {
            if (i == playerY && j == playerX) {
                printf("&");
            } else if (i == monstroY && j == monstroX) {
                printf("X");
            } else {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para imprimir o terceiro mapa (terceira fase)
void printThirdMap(char map[TERCEIRO_MAPA_ALTURA][TERCEIRO_MAPA_LARGURA], int playerX, int playerY, int monstroX, int monstroY) {
    system("cls");

    for (int i = 0; i < TERCEIRO_MAPA_ALTURA; i++) {
        for (int j = 0; j < TERCEIRO_MAPA_LARGURA; j++) {
            if (i == playerY && j == playerX) {
                printf("&");
            } else if (i == monstroY && j == monstroX) {
                printf("V"); // Monstro representado por 'V'
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

// Função para teleportar o jogador para o outro teletransporte
void teleport(char map[][TERCEIRO_MAPA_LARGURA], int* x, int* y) {
    for (int i = 0; i < TERCEIRO_MAPA_ALTURA; i++) {
        for (int j = 0; j < TERCEIRO_MAPA_LARGURA; j++) {
            if (map[i][j] == '>' && (i != *y || j != *x)) {
                *y = i;
                *x = j;
                return;
            } else if (map[i][j] == '<' && (i != *y || j != *x)) {
                *y = i;
                *x = j;
                return;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int mortes = 0; // Variável para contar as mortes por espinhos
    bool passagemAberta = false; // Indica se a passagem está aberta

    do {
        int numero;
        printf("\n\n\t\t\t\t\t\tDungeon Crawler\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t1 - Jogar\n\n\n\n\n");
        printf("\t\t\t\t\t\t2 - Tutorial\n\n\n\n\n");
        printf("\t\t\t\t\t\t3 - Sair\n\n\n\n\n");
        printf("\t\t\t\t\t\tEscolha a opcao desejada: ");
        scanf("%d", &numero);
        
        switch (numero) {
            case 1:
                mortes = 0; // Reinicia o contador de mortes
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
                            } else if (mapa[y][x] == 'O') {
                                // Teletransporte para um local aleatório
                                do {
                                    x = rand() % (MAPA_LARGURA - 2) + 1;
                                    y = rand() % (MAPA_ALTURA - 2) + 1;
                                } while (mapa[y][x] != ' ');
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
                passagemAberta = false; // Reinicia a variável para a segunda fase

                int monstroX = 17, monstroY = 8; // Posição inicial do monstro
                char segundoMapa[SEGUNDO_MAPA_ALTURA][SEGUNDO_MAPA_LARGURA] = {
                    "* * * * * * * * * * * * * * * * * * * *",
                    "* #            #************      *   *",
                    "*  #                              *   *",
                    "*              #*************#    *   *",
                    "*## #********# *             *    *   *",
                    "* #  #    *  * *##**************# *   *",
                    "*###  #   D  * *                * *###*",
                    "*#### #   *  * *                *     *",
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

                while (1) {
                    system("cls");
                    printSecondMap(segundoMapa, x, y, monstroX, monstroY);
                    
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
                            } else if (segundoMapa[y][x] == 'O') {
                                // Teletransporte para um local aleatório
                                do {
                                    x = rand() % (SEGUNDO_MAPA_LARGURA - 2) + 1;
                                    y = rand() % (SEGUNDO_MAPA_ALTURA - 2) + 1;
                                } while (segundoMapa[y][x] != ' ');
                            }
                            break;
                    }

                    // Movimento do monstro (aleatório)
                    int movimentoMonstro = rand() % 4; // 0 cima, 1 baixo, 2 esquerda, 3 direita
                    switch (movimentoMonstro) {
                        case 0:
                            if (monstroY > 1 && segundoMapa[monstroY - 1][monstroX] != '*' && segundoMapa[monstroY - 1][monstroX] != '#' && segundoMapa[monstroY - 1][monstroX] != 'D') monstroY--;
                            break;
                        case 1:
                            if (monstroY < SEGUNDO_MAPA_ALTURA - 2 && segundoMapa[monstroY + 1][monstroX] != '*' && segundoMapa[monstroY + 1][monstroX] != '#' && segundoMapa[monstroY + 1][monstroX] != 'D') monstroY++;
                            break;
                        case 2:
                            if (monstroX > 1 && segundoMapa[monstroY][monstroX - 1] != '*' && segundoMapa[monstroY][monstroX - 1] != '#' && segundoMapa[monstroY][monstroX - 1] != 'D') monstroX--;
                            break;
                        case 3:
                            if (monstroX < SEGUNDO_MAPA_LARGURA - 2 && segundoMapa[monstroY][monstroX + 1] != '*' && segundoMapa[monstroY][monstroX + 1] != '#' && segundoMapa[monstroY][monstroX + 1] != 'D') monstroX++;
                            break;
                    }

                    // Verificar se o jogador está na mesma posição do monstro
                    if (x == monstroX && y == monstroY) {
                        printf("\nVoce foi pego pelo monstro! Pressione qualquer tecla para reiniciar...\n");
                        getch(); // Aguardar entrada do jogador
                        x = 1;
                        y = 1;
                        monstroX = 17; // Reinicia a posição do monstro
                        monstroY = 8;
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
                        printf("Pressione qualquer tecla para continuar...\n");
                        getch();
                        system("cls");
                        break; // Encerra o loop do jogo
                    }

                    // Verificar se o jogador tocou no espinho
                    if (segundoMapa[y][x] == '#') {
                        printf("\nVoce tocou no espinho!\n");
                        mortes++; // Incrementa o número de mortes
                        printf("Mortes: %d\n", mortes);
                        if (mortes >= 3) {
                            system("cls");

                            printf("\n\n\n\n\n\n\n\t\t\t    ## ##     ##     ##   ##  ### ###            ## ##   ### ###  ### ###  ### ## \n");
                            printf("\t\t\t   ##   ##     ##     ## ##    ##  ##           ##   ##   ##  ##   ##  ##   ##  ## \n");
                            printf("\t\t\t   ##        ## ##   # ### #   ##               ##   ##   ##  ##   ##       ##  ## \n");
                            printf("\t\t\t   ##  ###   ##  ##  ## # ##   ## ##            ##   ##   ##  ##   ## ##    ## ## \n");
                            printf("\t\t\t   ##   ##   ## ###  ##   ##   ##               ##   ##   ### ##   ##       ## ## \n");
                            printf("\t\t\t   ##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ###     ##  ##   ##  ## \n");
                            printf("\t\t\t   ## ###    ##  ##  ##   ##   ### ###           ## ##      ##     ### ###  ###  ## *\n");

                            printf("\n\n\n\t\t\tVoce morreu 3 vezes. Pressione qualquer tecla para voltar ao menu principal...\n");
                            getch();
                            system("cls");
                            goto menu_principal; // Volta ao menu principal
                        } else {
                            printf("\nPressione qualquer tecla para reiniciar...\n");
                            getch(); // Aguardar entrada do jogador
                            x = 1;
                            y = 1;
                        }
                    }
                }

                              // Iniciar o terceiro mapa após a conclusão do segundo
                printf("\n\n\n\n\n\n\t\t\t\t\t\tIniciando terceira fase...\n\n\n\n\n\n");
                Sleep(500);
                x = 1, y = 1;
                chavePegou = 0;
                portaAberta = 0;
                passagemAberta = false; // Reinicia a variável para a terceira fase

                monstroX = 35, monstroY = 20; // Posição inicial do monstro
                char terceiroMapa[TERCEIRO_MAPA_ALTURA][TERCEIRO_MAPA_LARGURA] = {
                    "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
                    "*                                                                             *",
                    "*                                                                             *",
                    "*######################################  #####################################*",
                    "*    ##                               #  #                                   #*",
                    "*    <#                               #  #    ########## #####################*",
                    "*    ##                               #  #     #         ###########          D",
                    "*     #                               #  #    #   ##################     #####*",
                    "*     #                               #  #   #    #             #      ####   *",
                    "*     #                               #  #    #   #       #### ###   ##       *",
                    "*     #                               #  #     #     #####  #  #   #          *",
                    "*                                       #      #   #         #    #           *",
                    "*######################################  #    #   #           # #             *",
                    "*                                      #  #      #             #              *",
                    "*                                       #  #### ##                            *",
                    "*                                        #      #                             *",
                    "*                                         #  #################################*",
                    "*##########################################                                   *",
                    "*@          #                   ##                                            *",
                    "* ######  ###############       ##     ###### ######  #####  #      #         *",
                    "*  ##      #                #   ##       #    #    #  #   #  #      #         *",
                    "*#   #     ##########       #   ##       #    #  ###  #   #  #      #         *",
                    "*     #            #       #    ##       #    #  #    #   #  #      #         *",
                    "*      #   #   ######## #       ##       #    #   #   #####  #####  ######    *",
                    "*        #   #                   #                                            *",
                    "*#############################  ###################   ########################*",
                    "*                             # #                 #   #                       *",
                    "*                             #  #                #   #                       *",
                    "*                            #  #                 #   #                       *",
                    "*                           #  #                  #   #                       *",
                    "*                          #  #                   #   #                       *",
                    "*                         #  #                    #   #                       *",
                    "*                        #  #######################   ########################*",
                    "*                       #  #                                                  *",
                    "*###################   #  #     #####  ######  #######  #    #                *",
                    "*                  #  #  #      #   #  #    #     #     #    #                *",
                    "*      >#          # #  #       #####  ######     #     ######                *",
                    "*########          ##  #        #      #    #     #     #    #                *",
                    "*########             #         #      #    #     #     #    #0#              *",
                    "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
                };

                while (1) {
                    system("cls");
                    printThirdMap(terceiroMapa, x, y, monstroX, monstroY);
                    
                    char move = getch();
                    
                    switch(move) {
                        case 'w':
                            if(y > 1 && terceiroMapa[y-1][x] != '*') y--;
                            break;
                        case 's':
                            if(y < TERCEIRO_MAPA_ALTURA - 2 && terceiroMapa[y+1][x] != '*') y++;
                            break;
                        case 'a':
                            if(x > 1 && terceiroMapa[y][x-1] != '*') x--;
                            break;
                        case 'd':
                            if(x < TERCEIRO_MAPA_LARGURA - 2 && terceiroMapa[y][x+1] != '*') x++;
                            break;
                        case 'q':
                            return 0;
                        case 'i':
                            // Verificar se o jogador está em cima de um teletransporte
                            if (terceiroMapa[y][x] == '>' || terceiroMapa[y][x] == '<') {
                                teleport(terceiroMapa, &x, &y);
                            } else if (terceiroMapa[y][x] == '@') {
                                chavePegou = 1;
                                terceiroMapa[y][x] = ' ';
                            }
                            break;
                    }

                  // Movimento do monstro para seguir o jogador
					if (monstroX < x && terceiroMapa[monstroY][monstroX + 1] != '*' && terceiroMapa[monstroY][monstroX + 1] != '#') {
 					   monstroX++;
						} else if (monstroX > x && terceiroMapa[monstroY][monstroX - 1] != '*' && terceiroMapa[monstroY][monstroX - 1] != '#') {
 					   monstroX--;
						} else if (monstroY < y && terceiroMapa[monstroY + 1][monstroX] != '*' && terceiroMapa[monstroY + 1][monstroX] != '#') {
					    monstroY++;
					} else if (monstroY > y && terceiroMapa[monstroY - 1][monstroX] != '*' && terceiroMapa[monstroY - 1][monstroX] != '#') {
 					   monstroY--;
}

                    // Verificar se o jogador está na mesma posição do monstro
                    if (x == monstroX && y == monstroY) {
                        printf("\nVoce foi pego pelo monstro! Pressione qualquer tecla para reiniciar...\n");
                        getch(); // Aguardar entrada do jogador
                        x = 1;
                        y = 1;
                        monstroX = 30; // Reinicia a posição do monstro
                        monstroY = 35;
                    }

                    // Se o jogador tem a chave e está em frente à porta, abre a porta
                    if (chavePegou) {
                        if (move == 'w' && terceiroMapa[y-1][x] == 'D') {
                            portaAberta = 1;
                            terceiroMapa[y-1][x] = '='; // Abre a porta
                        } else if (move == 's' && terceiroMapa[y+1][x] == 'D') {
                            portaAberta = 1;
                            terceiroMapa[y+1][x] = '='; // Abre a porta
                        } else if (move == 'a' && terceiroMapa[y][x-1] == 'D') {
                            portaAberta = 1;
                            terceiroMapa[y][x-1] = '='; // Abre a porta
                        } else if (move == 'd' && terceiroMapa[y][x+1] == 'D') {
                            portaAberta = 1;
                            terceiroMapa[y][x+1] = '='; // Abre a porta
                        }
                    }

                    // Verificar se o jogador está na posição da porta aberta e pressionou em direção a ela
                    if (portaAberta && (terceiroMapa[y][x] == '=')) {
                    	system ("cls");
                        printf("\n\n\t\t\t\t\t\tVoce concluiu todas as fases e venceu o jogo!\n\n\n");
                        printf("\t\t\t\t\t\tPressione qualquer tecla para voltar ao menu principal...\n");
                        getch();
                        system("cls");
                        goto menu_principal; // Volta ao menu principal
                    }

                    // Verificar se o jogador tocou no espinho
                    if (terceiroMapa[y][x] == '#') {
                        printf("\nVoce tocou no espinho!\n");
                        mortes++; // Incrementa o número de mortes
                        printf("Mortes: %d\n", mortes);
                        if (mortes >= 3) {
                            system("cls");

                            printf("\n\n\n\n\n\n\n\t\t\t    ## ##     ##     ##   ##  ### ###            ## ##   ### ###  ### ###  ### ## \n");
                            printf("\t\t\t   ##   ##     ##     ## ##    ##  ##           ##   ##   ##  ##   ##  ##   ##  ## \n");
                            printf("\t\t\t   ##        ## ##   # ### #   ##               ##   ##   ##  ##   ##       ##  ## \n");
                            printf("\t\t\t   ##  ###   ##  ##  ## # ##   ## ##            ##   ##   ##  ##   ## ##    ## ## \n");
                            printf("\t\t\t   ##   ##   ## ###  ##   ##   ##               ##   ##   ### ##   ##       ## ## \n");
                            printf("\t\t\t   ##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ###     ##  ##   ##  ## \n");
                            printf("\t\t\t   ## ###    ##  ##  ##   ##   ### ###           ## ##      ##     ### ###  ###  ## *\n");

                            printf("\n\n\n\t\t\tVoce morreu 3 vezes. Pressione qualquer tecla para voltar ao menu principal...\n");
                            getch();
                            system("cls");
                            goto menu_principal; // Volta ao menu principal
                        } else {
                            printf("\nPressione qualquer tecla para reiniciar...\n");
                            getch(); // Aguardar entrada do jogador
                            x = 1;
                            y = 1;
                        }
                    }
                }
                break;

            case 2:
                system("cls"); 
                printf("\n\t\t\t\t\t\tDungeon Crawler - Tutorial\n");
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
                printf("\t\t\t\t<: Teletransporte.\n");
                printf("\t\t\t\t>: Teletransporte.\n");
                printf("\t\t\t\tX: Monstro 1, cuidado! \n");
                printf("\t\t\t\tV: Monstro 2, cuidado!\n\n");
                printf("\t\t\t\tObjetivo:\n");
                printf("\t\t\t\tEncontre a chave, abra a porta e evite os espinhos.\n\n");
                printf("\t\t\t\tPressione qualquer tecla para voltar ao menu principal...\n\n\n\n\n");
                getch(); // Aguardar entrada do jogador
                system("cls");
                break;

            case 3:
            	system ("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEncerrando...\n\n\n\n\n\n\n\n\n\n\n\n\n");
                Sleep(1000); 
                
                return 0;
                
            default:
                printf("\n\n\n\n\n\n\t\t\t\t\t\tOpcao invalida!\n\n\n\n\n\n\n\n\n\n\n");
                break;
        }
menu_principal:;
    } while(1);

    return 0;
}
