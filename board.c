//
// board.c
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

#include <stdio.h>
#include <stdlib.h>

#define N_BOARD     20 //코딩에선 메크로로 정의 하는게 유리 

#define N_COINPOS     12
#define MAX_COIN     4
/*
#define BOARDSTATUS_OK     1 //값은 정수면 아무거나 상관 없음. 메크로를 이렇게 정의해놓는다. 임의로 의미 부여. 
#define BOARDSTATUS_NOK    0  
*/



//필요한 변수 적어주기 
static int board_status[N_BOARD]; //몇번째 칸이 파손되었는지, 아닌지를 판단. 15개의 정수가 배열로 만들어짐. 1이면 괜찮고, 0은 파손됨. 
static int board_coin[N_BOARD]; //i번째 칸이 동전을 몇개  가지고 있는지  

static int board_sharkPosition; //상어의 위치 저장. 
                                //static을 이용해 고정. 남이 손대지 못하도록. 
                               
                              
                              
//------------------------------------------------------------------------------
int board_initBoard(void)
{
    int i;
    for (i=0; i<N_BOARD; i++);
    {
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = 0;
    }
    
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



int board_printBoardStatus(void)
   //board 판 만들어주기 
{
    int i;
    printf("-------------------- BOARD STATUS --------------------\n");
    for (i=0; i<N_BOARD; i++)
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)
           printf("X");
        else
           printf("O");
   }
   pirntf("|\n");
   pritnf("-------------------------------------------------------\n");
   
   return 0;
}

//------------------------------------------------------------------------------
int board_getBoardStatus(int pos)
{
    // 단순한 상태조회함수  
     return board_status[pos]; //값 자체 반환 
}


int board_getBoardCoin(int pos)
{ 
    int coin = board_coin[pos]; // 아래에서 필요했던 지역변수. 0으로 만들어지기 전에 미리 저장.  
    //coin은 한번 주우면 없어지는 거니까 그냥 return을 하면 안되고 0으로 만들어줘야 한다.  
    board_coin[pos] = 0; // 근데 이렇게 하면 문제가 발생할 것이다. 이 배열의 요소를 0으로 만들어준 상태에서 
    return coin; // 이 배열을 그대로 반환해주면 0밖에 안나온다. 따라서 지역변수 필요. 
}


//------------------------------------------------------------------------------
//int board_getSharkPosition(void);
//int board_stepShark(void);
