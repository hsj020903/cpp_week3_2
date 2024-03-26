#include "console.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cstring>
#define BOARD_SIZE 20
#define MOVE_DELAY 15
using namespace console;
using namespace std;


void draw_board(){
    draw(0, 0 ,"┏");
    draw(BOARD_SIZE-1, 0 , "┓");
    draw(0,BOARD_SIZE-1, "┗");
    draw(BOARD_SIZE-1, BOARD_SIZE-1, "┛");

    for(int i = 1; i < BOARD_SIZE-1; i++){
        draw(0, i, "┃");
        draw(BOARD_SIZE-1, i, "┃");
        draw(i, 0, "━");
        draw(i, BOARD_SIZE-1, "━");
    }

}


int main(){
    init();
    string last = "K_RIGHT";
    bool end = true, out = false;
    int snakex = BOARD_SIZE/2, snakey = BOARD_SIZE/2;
    int snake_size = 1;
    int applex, appley, score = 0, random, timer = 0;
    int snake_body[BOARD_SIZE*BOARD_SIZE][2];
    snake_body[0][1] = snakex;
    snake_body[0][0] = snakey;
    srand(time(NULL));
    int n = 0;
    int ck1[BOARD_SIZE*BOARD_SIZE][2];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            ck1[i][j] = 0;
        }
    }
    int ck2[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            ck2[i][j] = 0;
        }
    }
    ck2[snake_body[0][0]][snake_body[0][1]] == 1;
    for(int i = 1; i <= BOARD_SIZE-2; i++){
        for(int j = 1; j <= BOARD_SIZE-2; j++){
            if(ck2[i][j] != 1){
                ck1[n][0] = i;
                ck1[n][1] = j;
                n++;
            }
        }
    }
    random = rand()%n;
    n = 0;
    applex = ck1[random][0];
    appley = ck1[random][1];
    clock_t end_time;
    clock_t start_time = clock();
    while(end){  
    // 게임시작
        clear();
        draw_board();   // 판그리기
        
        int socre_size = ("Score: " + to_string(score)).size();                         // 점수바의 길이를 구함
        draw((BOARD_SIZE/2)-(socre_size/2),BOARD_SIZE, "Score: " + to_string(score));   // 스코어 출력
        draw(applex, appley, "●");                                                      // 사과 출력  
        for(int i = snake_size-1; i >= 0; i--){                                         // 뱀 출력
            draw(snake_body[i][0], snake_body[i][1], "■");
        }
        if(snakex == 0 || snakex == BOARD_SIZE-1 || snakey == 0 || snakey == BOARD_SIZE-1){ // 맵에 닿았을때 사망처리
            out = true;
        }
        for(int i = snake_size-1; i >= 4; i--){                             // 자신의 몸에 닿았을때 사망처리
            if(snake_body[i][0] == snakex && snake_body[i][1] == snakey){
                out = true;
            }
        }
        while(out){ 
            clear();                                                   //아웃되었을때 게임 종료화면
            draw(0, 0 ,"┏");
            draw(BOARD_SIZE-1, 0 , "┓");
            draw(0,BOARD_SIZE-1, "┗");
            draw(BOARD_SIZE-1, BOARD_SIZE-1, "┛");

            for(int i = 1; i < BOARD_SIZE-1; i++){
                if(0 != snakex || i != snakey)
                    draw(0, i, "┃");
                if(BOARD_SIZE-1 != snakex || i != snakey)
                    draw(BOARD_SIZE-1, i, "┃");
                if(i != snakex || 0 != snakey)
                    draw(i, 0, "━");
                if(i != snakex || BOARD_SIZE-1 != snakey)
                    draw(i, BOARD_SIZE-1, "━");
            }
            for(int i = snake_size-1; i >= 0; i--){                             // 뱀 출력
                draw(snake_body[i][0], snake_body[i][1], "■");
            }
            draw((BOARD_SIZE/2)-4, BOARD_SIZE/2, "YOU LOSE!");
            draw((BOARD_SIZE/2)-9, (BOARD_SIZE/2)+1, "Try again? (Enter)");
            draw((BOARD_SIZE/2)-(socre_size/2),BOARD_SIZE, "Score: " + to_string(score));
            wait();
            if(key(K_ENTER)){
                out = false;
                snakex = BOARD_SIZE/2, 
                snakey = BOARD_SIZE/2;
                snake_size = 1;
                last="K_RIGHT";
                score = 0;
            }
            else if(key(K_ESC)){
                end = false;
                out = false;
            }
            wait();
        }
        if(timer >= MOVE_DELAY){
            timer = 0;
        
            if(key(K_LEFT) && (snake_size == 1 || last != "K_RIGHT")){  // 이동방향 처리
                snakex--;
                last = "K_LEFT";
            }
            else if(key(K_RIGHT) && (snake_size == 1 || last != "K_LEFT" )){
                snakex++;
                last="K_RIGHT";
            }
            else if(key(K_UP) && (snake_size == 1 || last != "K_DOWN")){
                snakey--;
                last="K_UP";
            }
            else if(key(K_DOWN) && (snake_size == 1 || last != "K_UP")){
                snakey++;
                last="K_DOWN";
            }
            else if(key(K_ESC)){
                end = false;
            }
            else{
                if(last == "K_LEFT")
                    snakex--;
                else if(last == "K_RIGHT")
                    snakex++;
                else if(last == "K_UP")
                    snakey--;
                else if(last == "K_DOWN")
                    snakey++;
            }
            for(int i = snake_size-1; i >= 0;i--){  //뱀 위치설정
                if(i != 0){
                snake_body[i][0] = snake_body[i-1][0];
                snake_body[i][1] = snake_body[i-1][1];
                }
                else{
                    snake_body[0][0] = snakex;
                    snake_body[0][1] = snakey;
                }
            }
        
            if(applex == snakex && appley == snakey){ // 사과를 먹었을때 처리
                score += 10;
                n = 0;

                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < 2; j++) {
                        ck1[i][j] = 0;
                    }
                }

                    for (int i = 0; i < BOARD_SIZE; i++) {
                        for (int j = 0; j < BOARD_SIZE; j++) {
                            ck2[i][j] = 0;
                        }
                    }
                for(int i = 0; i < snake_size; i++){
                    ck2[snake_body[i][0]][snake_body[i][1]] = 1;
                }
                for(int i = 1; i <= BOARD_SIZE-2; i++){
                        for(int j = 1; j <= BOARD_SIZE-2; j++){
                        if(ck2[i][j] != 1){
                            ck1[n][0] = i;
                            ck1[n][1] = j;
                            n++;
                        }
                    }
                }
                random = rand() % n;
                applex = ck1[random][0];
                appley = ck1[random][1];
                snake_size++;
                snake_body[snake_size-1][0] = snake_body[snake_size-2][0];
                snake_body[snake_size-1][1] = snake_body[snake_size-2][1];
            }
        }
        timer++;
        wait();

        if(snake_size == (BOARD_SIZE-2) * (BOARD_SIZE-2)){
            end = false;
            draw((BOARD_SIZE/2)-9, (BOARD_SIZE/2)+1, "You Win!");
        }
        
    }
    return 0;
}