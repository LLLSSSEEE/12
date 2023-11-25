//
// board.c
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_COINPOS      12
#define MAX_COIN        4

#define MAX_SHARKSTEP   6 //게임의 난이도 조절. 상어는 최대 6칸 이동. 
#define SHARK_INITPOS  -4 //게임의 난이도 조절. 상어가 얼마나 뒤에 있는지. 


/*
#define BOARDSTATUS_OK     1 //값은 정수면 아무거나 상관 없음. 메크로를 이렇게 정의해놓는다. 임의로 의미 부여. 
#define BOARDSTATUS_NOK    0  
*/


//------------------------------------------------------------------------------
//필요한 변수 전역변수로 정의 
static int board_status[N_BOARD]; //몇번째 칸이 파손되었는지, 아닌지를 판단. 15개의 정수가 배열로 만들어짐. 1이면 괜찮고, 0은 파손됨. 
static int board_coin[N_BOARD]; //i번째 칸이 동전을 몇개  가지고 있는지  

static int board_sharkPosition; //상어의 위치 저장. 
                                //static을 이용해 고정. 남이 손대지 못하도록. 
                               
                              
                              
//------------------------------------------------------------------------------
//board status와 coin 초기화 
int board_initBoard(void)
{
    int i;
    for (i=0; i<N_BOARD; i++)
    {
        board_status[i] = BOARDSTATUS_OK; //board_status와 i번째 요소 0설정 
        board_coin[i] = 0; //board_coin의 i번째 요소 0 설정 
    }
    
    board_sharkPosition = SHARK_INITPOS;
     
    //coin 할당 
    for(i=0; i<N_COINPOS; i++)
    {
        int flag = 0; // 변수 아무거나 잡고 0으로 초기화 
        while(flag == 0) //깃발이 내려가있는지만 파악 
        {
               int allocPos = rand()%N_BOARD; // 할당하는 위치. rand함수로 불러옴. 0부터 14까지 
               if (board_coin[allocPos] == 0) // allocpos가 0이면 할당이 안된 것. 
               { 
                   board_coin[allocPos] = rand()%MAX_COIN+1;
                   flag = 1;
               }
        }
    }    
     
    return 0;              
}


//------------------------------------------------------------------------------
//board 판 만들어주기 -> main.c에서 갖다 쓸 예정. 
int board_printBoardStatus(void)
{
    int i;
    
    printf("                                                               \n");
    printf("===============================================================\n");
    printf("------------------------ BOARD  STATUS ------------------------\n");
    for (i=0; i<N_BOARD; i++) //i가 0~19가 될 때 까지 for문 반복.  
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK) //만약 보드 상태가 망가지면 
           printf("X"); //보드판에 X출력 
        else
           printf("O"); //보드판이 안망가지면 출력안함. 
   }
   printf("|\n");
   printf("----------------------------------------------------------------\n");
   printf("================================================================\n");
   printf("                                                                \n");
   
   return 0;
}

//------------------------------------------------------------------------------
// board_getBoardStatus : 
int board_getBoardStatus(int pos)
{
    // 단순한 상태조회함수  
     return board_status[pos]; //값 자체 반환 
}

//------------------------------------------------------------------------------
// board_getBoardCoin : 
int board_getBoardCoin(int pos)
{ 
    int coin = board_coin[pos]; // 아래에서 필요했던 지역변수. 0으로 만들어지기 전에 미리 저장.  
    //coin은 한번 주우면 없어지는 거니까 그냥 return을 하면 안되고 0으로 만들어줘야 한다.  
    board_coin[pos] = 0; // 근데 이렇게 하면 문제가 발생할 것이다. 이 배열의 요소를 0으로 초기화. 
    return coin; // 이 배열을 그대로 반환해주면 0밖에 안나온다. 따라서 지역변수 필요. 
}


//------------------------------------------------------------------------------
// board_getSharkPosition(void);
int board_stepShark(void)
{
    int step = rand()%MAX_SHARKSTEP+1; //1~6까지를 원하는데 random 숫자를 7로 나눠야 1~6이 출력된다.  
    int i;
    
    for(i=board_sharkPosition+1; i<=board_sharkPosition+step; i++)
    {
        if(i>=0 && i<N_BOARD) //상어가 이 범위 안에 있을 때만! (음수 범위는 안됨) 
            board_status[i] = BOARDSTATUS_NOK;
    }

    board_sharkPosition += step;
    
    return board_sharkPosition;
     
}
