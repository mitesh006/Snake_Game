#include <stdio.h>
#include <time.h>
#include <stdlib.h> // for rand() 
#include <conio.h> // for _getch() and _kbhit()
#include <windows.h> //for Sleep()

// Constants
#define WIDTH 50 
#define HEIGHT 20 

//Directions
enum direction {STOP = 0, RIGHT, LEFT, UP, DOWN};

//Variables
int gameOver;
int x, y, fx, fy; 
int tailX[100] ;
int tailY[100] ;
int tail = 0;
int score;
enum direction dir;

// Function to set the cursor position
void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hConsole, position);
}

// Setting up game function
void setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH/2;
    y = HEIGHT/2;
    fx = rand() % WIDTH;   // randomize coordinate
    fy = rand() % HEIGHT;
    score = 0;
}

//Game interface
void draw() {
    setCursorPosition(38,4);
    for(int j = 0;j < WIDTH + 2;j++){
        printf("#");  // Borders
    } printf("\n");

    for(int i = 0;i < HEIGHT;i++){
        setCursorPosition(38,5+i);
        for(int j = 0;j < WIDTH;j++) {
            if(j==0) printf("#");
            if(j==x && i==y) {
                printf("0");  // Head
            } else if(j==fx && i==fy) {
                printf("*");  // Fruit
            }  else {
                int z = 0;
                for(int k=0; k < tail; k++) {
                    if(tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        z = 1;
                    }
                }
                if (!z) printf(" ");   //  Spaces
            }
            if(j==WIDTH-1) printf("#");  // Borders
        }
    }
    setCursorPosition(38,25);
    for(int j = 0;j < WIDTH + 2;j++){
        printf("#");
    }
    setCursorPosition(38,26);
    printf("Score: %d", score);
    setCursorPosition(38,28);
    printf("Press X to end the game");
}

//Take input
void input() {
    if (kbhit()) {
        switch (getch()) {
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
        case 'A':
            dir = LEFT;
            break;
        case 'D':
            dir = RIGHT;
            break;
        case 'W':
            dir = UP;
            break;
        case 'S':
            dir = DOWN;
            break;
        case 'X':
            gameOver = 1;
            break;
        }
    }
}

//Game logic
void logic() {
    int prevX = tailX[0];           // Tail logic
    int prevY = tailY[0];
    int tempX,tempY;
    tailX[0] = x;
    tailY[0] = y;

    for(int k = 1; k < tail ; k++) {
         tempX = tailX[k];
         tempY = tailY[k];
         tailX[k] = prevX;
         tailY[k] = prevY;
         prevX = tempX;
         prevY = tempY;  
    }
    // Navigation
    switch (dir) {
        case UP :
        y--;
        break;
        case DOWN :
        y++;
        break;
        case RIGHT :
        x++;
        break;
        case LEFT :
        x--;
        break;
        default :
        break;
    }

    // Snake hitting wall
    if(x >= WIDTH || x < 0 || y < 0 || y >= HEIGHT) {
        gameOver = 1;
    }

    //Snake hitting itself
    for(int k = 0; k < tail; k++) {
        if (tailX[k] == x && tailY[k] == y) {
            gameOver = 1;
        }
    }

    //Snake eating fruit
    if(x == fx && y == fy) {
        score = score + 10;
        fx = rand() % WIDTH;
        fy = rand() % HEIGHT;
        tail++;
    }
}

// Main function
int main() {
    jump:
    system("cls");
    setCursorPosition(59,2);
    printf("Snake Game");
    srand(time(0));
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(50); // Game speed
    }
    setCursorPosition(38,28);
    printf("Game Over! Final Score: %d", score);
    setCursorPosition(38,29);
    printf("Press R to play again");
    setCursorPosition(38,30);
    printf("Press any other key to exit the game");
    char c = getch();
    if(c == 'r' || c == 'R') goto jump;
    else {
        return 0;
    }
}