#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//macros variable (height, weidth)
#define HEIGHT 20
#define WIDTH 40

//to store snake's tail's coordinates
int snaketailX[100] , snaketailY[100];
//to store snake's tail's length
int snaketaillen;
//score and signals
int gameover, key, score;
//coordinates of snake's head and fruit
int x,y,fruitx,fruity;
//functions to generate the fruit withing the boundary
void setup() {
    //flag to signal gameover
    gameover = 0;
    key =0;
    snaketaillen = 0;
    //initial coordinates of snake
    x = WIDTH / 2;
    y = HEIGHT / 2;

    //INITIAL COORDINATES OF THE FRUIT 
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;
    while (fruitx == 0)
        fruitx = rand() % WIDTH;
    
    while (fruity == 0)
        fruity = rand() %HEIGHT;

    //SCORE INITIALISED
    score = 0;
}

//function to draw feild, snake and fruit
void draw() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    //top wall
    for (int i = 0; i< WIDTH + 2; i++)
        printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j <= WIDTH; j++) {

            //creating side walls with '#'
            if (j == 0 || j == WIDTH)
                printf("#");
            
            //creating snake's head with 'o'
            if(i == y && j == x)
                printf("o");

            //creating fruit with *
            else if(i == fruity && j == fruitx)
                printf("*");

            //creating snake's body with 'o'
            else {
                int prtail = 0;
                for (int k = 0; k < snaketaillen; k++) {
                    if (snaketailX[k] == j
                       && snaketailY[k] == i) {
                       printf("o");
                       prtail = 1;
                    }
                }
                if (!prtail)
                    printf(" ");
            }
        }
      printf("\n");

    }

    //creating bottom walls with '-'
    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
     printf("\n");

    //print the score and instructions
    printf("Score =%d", score);
    printf("\n");
    printf("Press W,A,S,D for movement.\n");
    printf("Press X to quit the game.");
}

//function to take the real time input
//set the flag variable accordingly
void input(){
    if (kbhit()) {
        switch (tolower(getch())) {
            case 'a':
                if(key!=2)
                key = 1;
                break;
            case 'd':
                if(key!=1)
                key = 2;
                break;
            case 'w':
                if(key!=4)
                key = 3;
                break;
            case 's':
                if(key!=3)
                key = 4;
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

//function for the movement logic that
// checks, eat, move, collision
void logic(){

    //updating the coordinates for continuous
    //movement of snake
    int prevx = snaketailX[0];
    int prevy = snaketailY[0];
    int prev2x, prev2y;
    snaketailX[0] = x;
    snaketailY[0] = y;
    for (int i = 1; i< snaketaillen; i++) {
        prev2x = snaketailX[i];
        prev2y = snaketailY[i];
        snaketailX[i] = prevx;
        snaketailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch(key){
        case 1:
            x--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        case 4:
            y++;
            break;
        default:
            break;
           
    }
    //if game is over
    if(x < 0 || x>= WIDTH || y < 0 || y>= HEIGHT)
       gameover = 1;
    //checks for collision with the tail (0)
    for(int i= 0; i< snaketaillen; i++) {
        if(snaketailX[i] == x && snaketailY[i] == y)
           gameover = 1;
    }
    //if snake reaches the fruit
    // then update the score
    if (x == fruitx && y == fruity){
        fruitx = rand() % WIDTH;
        fruity = rand() %HEIGHT;
        while (fruitx == 0)
            fruitx = rand() % WIDTH;

        //GENERATION OF NEW FRUIT
        while (fruity == 0)
            fruity = rand() % HEIGHT;
        score += 10;
         snaketaillen++;
    }
}
int main(){
    //initial setup that initialize the 
    //required variabls
    setup();

    //game loop starts here
    while (!gameover) {
        //funtions that will be called
        // repeatedly after the given intervals 
        draw();
        input();
        logic();
        Sleep(100);
    }
}
