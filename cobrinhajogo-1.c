#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 15
#define MAX_LENGTH 100

int x, y, fruitX, fruitY, score;
int tailX[MAX_LENGTH], tailY[MAX_LENGTH];
int length;
int gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    length = 0;
}

void Draw() {
    system("cls");
    printf("Jogo Cobrinha por Valeria Gomes\n");
    printf("Pontuacao: %d\n", score);

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("*");
            else {
                int isTail = 0;
                for (int k = 0; k < length; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < length; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < length; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        length++;
    }
}

int main() {
    int difficulty;

    printf("Escolha a dificuldade:\n");
    printf("1. Facil\n");
    printf("2. Medio\n");
    printf("3. Dificil\n");
    printf("Digite sua escolha: ");
    scanf("%d", &difficulty);

    int speed;
    switch (difficulty) {
        case 1:
            speed = 100; // Fácil
            break;
        case 2:
            speed = 50;  // Médio
            break;
        case 3:
            speed = 25;  // Difícil
            break;
        default:
            printf("Dificuldade invalida! Usando padrão (Fácil).\n");
            speed = 100;
            break;
    }

    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }

    return 0;
}
