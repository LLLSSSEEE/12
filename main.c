//
// main.c
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#includ "board.h"  

#define MAX_DIE     6


void opening(void) //opening이라는 함수 정의
{
     printf("==================================================\n");
     printf("**************************************************\n");
     printf("                    Shark Game                    \n");
     printf("**************************************************\n");
     printf("==================================================\n");



int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

int main(int argc, char *argv[])
{
  int pos = 0;
  srand((unsigned)time(NULL));
  
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
            
  //1. 초기화 & 플레이어 이름 결정
  board_initboard();
  
     //1-1.
     //1-2. 1st 플레이어 이름 입력
     //1-3. 2nd 플레이어 이름 입력
     //1-4. 3rd 플레이어 이름 입력
      
  
  //2. 반복문 (플레이어 턴)
  do {
     int step = rolldie();
     int coinResult;
     char c;
     
     board_printBoardStatus();
     
     pos += step;
     printf(//어디서 어디로 이동했다)
     coinResult = board_getBoardCoin(pos)
     
     printf("press any key to continue : ");
     scanf("%d", &c);
     fflush(stdin);
     
     //2-1. 플레이어의 상태 출력
     //2-2. 주사위 던지기
     //2-3. 이동
     //2-4. 동전 줍기
     //2-5. 다음 턴
     //2-6. if (조건 : 모든 플레이어가 한번씩 턴을 돔) 
        //상어 동작 
    } while(1);
      
  //3. 정리 (승자 계산, 출력 등) 
  
  /*
  printf("\n\n\n\n\n\n\n\n\n\n");
  printf("==================================================\n");
  printf("**************************************************\n");
  printf("CONCGRATULATION!!!!!\n");
  printf("*#&$*#^&*$&^@($!@(*   BINGO!!!!!   #)!@*(#)*%&(#*)@*(\n");
  */
  

  system("PAUSE");	
  return 0;
}
