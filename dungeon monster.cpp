
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAPA_ALTURA 10
#define MAPA_LARGURA 12

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
                        "**********",
                        "*        *",
                        "* ** *** D",
                        "* **   ***",
                        "* **** ***",
                        "* **** ***",
                        "*        *",
                        "* ****** *",
                        "* *@     *",
                        "**********"
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
                        printf("Pressione qualquer tecla para sair...\n");
                        return 0;
                        break; // Encerra o loop do jogo
                    }
                }
                break;
            case 2:
                system("cls"); 
                printf("\n\n\n\n\n\n\t\t\t\t\t\tIniciando Tutorial...\n");
                Sleep(500);
                printf("\n\n\n\n\n\n\t\t\t\tPressione qualquer tecla para voltar ao menu principal...");
                getch(); 
                system("cls"); 
                break;
            case 3:
                system("cls"); 
                printf("\n\n\n\n\n\n\t\t\t\t\t\tObrigado por jogar!!\n\n\n\n\n\n\t\t\t\t\t\tFechando jogo...\n");
                system("pause");
                system("cls"); 
                return 1;
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

