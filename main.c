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


void opening(void) //opening�̶�� �Լ� ����
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
            //�׳� �ƿ� �Լ��� ������ �������. 
            
  //1. �ʱ�ȭ & �÷��̾� �̸� ����
  board_initboard();
  
     //1-1.
     //1-2. 1st �÷��̾� �̸� �Է�
     //1-3. 2nd �÷��̾� �̸� �Է�
     //1-4. 3rd �÷��̾� �̸� �Է�
      
  
  //2. �ݺ��� (�÷��̾� ��)
  do {
     int step = rolldie();
     int coinResult;
     char c;
     
     board_printBoardStatus();
     
     pos += step;
     printf(//��� ���� �̵��ߴ�)
     coinResult = board_getBoardCoin(pos)
     
     printf("press any key to continue : ");
     scanf("%d", &c);
     fflush(stdin);
     
     //2-1. �÷��̾��� ���� ���
     //2-2. �ֻ��� ������
     //2-3. �̵�
     //2-4. ���� �ݱ�
     //2-5. ���� ��
     //2-6. if (���� : ��� �÷��̾ �ѹ��� ���� ��) 
        //��� ���� 
    } while(1);
      
  //3. ���� (���� ���, ��� ��) 
  
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
