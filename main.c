//
// main.c
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"  

#define MAX_CHARNAME 200 
#define N_PLAYER     3
#define MAX_DIE      6

//player상태를 변수로 표현해야 하니까.  
#define PLAYERSTATUS_LIVE     0
#define PLAYERSTATUS_DIE      1
#define PLAYERSTATUS_END      2
 
 
//------------------------------------------------------------------------------
// 뒤에서 필요한 변수들 선언. 
int player_position[N_PLAYER]; //player의 위치 
char player_name[N_PLAYER][MAX_CHARNAME]; //player의 이름 입력. 2차원 배열 이용[문자의크기][한 문자의길이] 
int player_coin[N_PLAYER]; //동전의 개수 저장. 동전의 개수는 정수.
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME]= {"LIVE", "DIE", "END"}; // 

/*
player_status[0] : 0번플레이어의 상태 
if (player_status[0]) == PLAYERSTATUS_LIVE : 0번 플레이어가 만약 살아있다면.
*/
 


//------------------------------------------------------------------------------
// opening :

void opening(void) //opening이라는 함수 정의
{
     printf("==============================================================\n");
     printf("**************************************************************\n");
     printf("      +               +-+-+-+-+-+-+-+-+               +       \n");
     printf("     + +            -                   -            + +      \n");
     printf("    +   +          +     SHARK GAME      +          +   +     \n");
     printf("     + +            -                   -            + +      \n");
     printf("      +               +-+-+-+-+-+-+-+-+               +       \n");
     printf("**************************************************************\n");
     printf("==============================================================\n");
     printf("                                                              \n");
     printf("                     I HOPE YOU SURVIVE                       \n");
     printf("                                                              \n");  
     printf("==============================================================\n");
     printf("                                                              \n");      
}



//------------------------------------------------------------------------------
//rolldie : 

int rolldie(void)
{
    return rand()%MAX_DIE+1;
}



//------------------------------------------------------------------------------
// printPlayerPosition : 

void printPlayerPosition(int player) //밖의 player랑 다른 것. 안에서 굳이 선언 안해줘도 된다.  
{
     int i;
     for(i=0; i<N_BOARD; i++) //i가 0~19 일 동안 for문 반복. 
     {
         printf("|");
         if (i == player_position[player]) //player_position이 i와 같으면, 
             printf("%c", player_name[player][0]); //플레이어 이름의 첫번째 알파벳 출력 
         else
         {
             if (board_getBoardStatus(i) == BOARDSTATUS_NOK) //보드 상태가 엉망이면, 
                 printf("X"); //보드가 파손된 경우 보드판에 X 출력.
             else //보드 상태가 괜찮으면, 
                 printf(" "); //보드가 멀쩡한 경우 보드판에 출력 안함.  
         }    
     } 
     printf("|\n");
}



//------------------------------------------------------------------------------
// printPlayerStatus : 최종 결과 출력 

void printPlayerStatus(void) 
{
     int i;     
     printf("\n----------------------- PLAYER  STATUS -----------------------\n");
     for(i=0; i<N_PLAYER; i++) //i가 0~2일때 까지 for문 반복. 
     {
         printf("%s : position %i,   coin %i,   status : %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
     }
     printf("--------------------------------------------------------------\n");
}



//------------------------------------------------------------------------------
// checkDie : 죽었는지 살았는지 확인. 

void checkDie(void)
{
     int i; //반복문 사용시 i필요 
     for (i=0; i<N_PLAYER; i++) //3명 다 확인해야 하니까 반복문 사용 
         if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK) //만약 망가진 판이면 
         {
             player_status[i] = PLAYERSTATUS_DIE; //i번째 플레이어의 상태는 'DIE'가 된다. 
             printf("DIE %s\n", player_name[i]);
         }
}



//------------------------------------------------------------------------------
// game_end : 
  int game_end(void)
  {
      int i;
      int flag_end = 1;
      
      //만약 모든 플레이어들이 죽는다면?
      for(i=0; i<N_PLAYER; i++)
      {
          if(player_status[i] == PLAYERSTATUS_LIVE)
          {
              flag_end = 0;
              break;
          }
      }
          return flag_end;
  }
  
  
  
//------------------------------------------------------------------------------
// getAlivePlayer : 
                  
  int getAlivePlayer(void)
  {
      int i;
      int cnt=0;
      for(i=0; i<N_PLAYER; i++)
      {
          if(player_status[i] == PLAYERSTATUS_END)
          cnt++;
      }
      return cnt;
  }
  
  int getWinner(void)
  {
      int i;
      int winner=0;
      int max_coin = -1;
      for(i=0; i<N_PLAYER; i++)
      {
          if(player_coin[i] > max_coin)
          {
              max_coin = player_coin[i];
              winner = i;
          }
      }
      return winner;
  }
  
  
  
//------------------------------------------------------------------------------
// main : 

int main(int argc, char *argv[])
{
  int pos = 0;
  int i;
  int turn = 0;
  srand((unsigned)time(NULL));
  
  
  //............................................................................
  //0. opening 
  opening();
  
            /*
            printf("==================================================\n");
            printf("**************************************************\n");
            printf("                    SHARK GAME                    \n");
            printf("**************************************************\n");
            printf("==================================================\n");
            */
            //그냥 아예 함수로 위에서 만들어줌. 
            
            
            
  //............................................................................          
  //1. 초기화 & 플레이어 이름 결정
  
  board_initBoard();
     //1-1. 플레이어별로 초기화 -> 1st,2nd,3rd 따로 하지 말로 반복문 for문 이용. 
     for (i=0; i<N_PLAYER; i++) //i를 위에서 선언해줘야 함. i가 0,1,2일 동안 반복.  
     {
         player_position[i] = 0; //i번째 플레이어 0으로 초기화. 
         player_coin[i] = 0; //동전도 0으로 초기화
         player_status[i] = PLAYERSTATUS_LIVE; //처음엔 플레이어들 살아있어야 함.
         
         //player_name은 입력이 필요하니까 printf-scanf 이용. 
         printf("Player %i's Name : ", i);
         scanf("%s", player_name[i]); //문자열로 받아야하니까 %s. player_name자체가 포인터이기 때문에 &필요 없음.  
     }
      
      
      
  //............................................................................
  //2. 반복문 (플레이어 턴)
  
  do {
     int step;
     int coinResult;
     char c;

     //아래 코드를 히트 시킬건지, 넘어갈건지.. 조건문으로 밑에 코드를 안하도록.
     if (player_status[turn] != PLAYERSTATUS_LIVE) //플레이어가 살아있는 상태가 아니면 다음 턴으로.  
     {
        turn = (turn+1)%N_PLAYER;
        continue; //continue를 만나면 무한 반복. 
     }   
     
     
     
     //2-1. 보드 & 플레이어의 상태 출력
     board_printBoardStatus();
     
     for (i=0; i<N_PLAYER; i++)
     {  
         printPlayerPosition(i);
     }
     printPlayerStatus();
     

     
     //2-2. 주사위 던지기
     printf("\n\n%s turn!", player_name[turn]);
     printf("press any key to roll a die!: ");
     scanf("%d", &c);
     fflush(stdin); //표준입력 flush 시키기. 게임을 하다가 입력을 받고 넘어가고 싶으면. 이렇게 별 의미 없이 넣으면 된다.  
     step = rolldie();
     
     
     
     //2-3. 이동
     player_position[turn] += step;
     
     if (player_position[turn] >= N_BOARD) // 같아질 때 까지 반복. 
     {
        player_position[turn] = N_BOARD-1;
     } 
     
     if (player_position[turn] == N_BOARD-1)
     {
        player_status[turn] = PLAYERSTATUS_END; 
        printf("player %s End.\n", player_name[turn]);
     } //14번째 딱 갔을 땐 위 코드를 만나질 못한다. -> 버그 발생
     
     
     //2-4. 동전 줍기 
     coinResult = board_getBoardCoin(pos);
     player_coin[turn] += coinResult;
     printf("\n\n %s player got %i coins and now you have i% coins!\n", player_name[turn], coinResult, player_coin[turn]);
      
      
      
     //2-5. 다음 턴
     turn = (turn + 1)%N_PLAYER; //N_PLAYER가 되는 순간 다시 0으로 돌아감.  
     
     

     //2-6. if (조건 : 모든 플레이어가 한번씩 턴을 돔) 
     if (turn == 0)
     {
        //상어 동작 
        int shark_pos = board_stepShark();
        printf("Shark moved to %i\n", shark_pos); //"상어가 이동했다." 출력 
        checkDie(); //죽었는지 살았는지 판단하는 함수 
        
     }               
    } while(game_end() == 0);
      
      

  //............................................................................    
  //3. 정리 (승자 계산, 출력 등) 
  
  int winner=getWinner();
  int Alive=getAlivePlayer();
  
  printf("\n\n\n\n\n\n\n\n\n\n");
  printf("=================================================================\n");
  printf("*****************************************************************\n");
  printf("                      CONCGRATULATION!!!!!                       \n");
  printf("*#&$*#^&*$&^@($!@(*   %s win        , %i alive     #)!@*(#)*%&(#*)@*(\n", player_name[winner],Alive);
  printf("*****************************************************************\n");                 
  printf("=================================================================\n");               
  
  system("PAUSE");
               
  
  return 0;
}
