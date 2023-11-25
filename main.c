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

//player���¸� ������ ǥ���ؾ� �ϴϱ�.  
#define PLAYERSTATUS_LIVE     0
#define PLAYERSTATUS_DIE      1
#define PLAYERSTATUS_END      2
 
 
//------------------------------------------------------------------------------
// �ڿ��� �ʿ��� ������ ����. 
int player_position[N_PLAYER]; //player�� ��ġ 
char player_name[N_PLAYER][MAX_CHARNAME]; //player�� �̸� �Է�. 2���� �迭 �̿�[������ũ��][�� �����Ǳ���] 
int player_coin[N_PLAYER]; //������ ���� ����. ������ ������ ����.
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME]= {"LIVE", "DIE", "END"}; // 

/*
player_status[0] : 0���÷��̾��� ���� 
if (player_status[0]) == PLAYERSTATUS_LIVE : 0�� �÷��̾ ���� ����ִٸ�.
*/
 


//------------------------------------------------------------------------------
// opening :

void opening(void) //opening�̶�� �Լ� ����
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

void printPlayerPosition(int player) //���� player�� �ٸ� ��. �ȿ��� ���� ���� �����൵ �ȴ�.  
{
     int i;
     for(i=0; i<N_BOARD; i++) //i�� 0~19 �� ���� for�� �ݺ�. 
     {
         printf("|");
         if (i == player_position[player]) //player_position�� i�� ������, 
             printf("%c", player_name[player][0]); //�÷��̾� �̸��� ù��° ���ĺ� ��� 
         else
         {
             if (board_getBoardStatus(i) == BOARDSTATUS_NOK) //���� ���°� �����̸�, 
                 printf("X"); //���尡 �ļյ� ��� �����ǿ� X ���.
             else //���� ���°� ��������, 
                 printf(" "); //���尡 ������ ��� �����ǿ� ��� ����.  
         }    
     } 
     printf("|\n");
}



//------------------------------------------------------------------------------
// printPlayerStatus : ���� ��� ��� 

void printPlayerStatus(void) 
{
     int i;     
     printf("\n----------------------- PLAYER  STATUS -----------------------\n");
     for(i=0; i<N_PLAYER; i++) //i�� 0~2�϶� ���� for�� �ݺ�. 
     {
         printf("%s : position %i,   coin %i,   status : %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
     }
     printf("--------------------------------------------------------------\n");
}



//------------------------------------------------------------------------------
// checkDie : �׾����� ��Ҵ��� Ȯ��. 

void checkDie(void)
{
     int i; //�ݺ��� ���� i�ʿ� 
     for (i=0; i<N_PLAYER; i++) //3�� �� Ȯ���ؾ� �ϴϱ� �ݺ��� ��� 
         if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK) //���� ������ ���̸� 
         {
             player_status[i] = PLAYERSTATUS_DIE; //i��° �÷��̾��� ���´� 'DIE'�� �ȴ�. 
             printf("DIE %s\n", player_name[i]);
         }
}



//------------------------------------------------------------------------------
// game_end : 
  int game_end(void)
  {
      int i;
      int flag_end = 1;
      
      //���� ��� �÷��̾���� �״´ٸ�?
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
            //�׳� �ƿ� �Լ��� ������ �������. 
            
            
            
  //............................................................................          
  //1. �ʱ�ȭ & �÷��̾� �̸� ����
  
  board_initBoard();
     //1-1. �÷��̾�� �ʱ�ȭ -> 1st,2nd,3rd ���� ���� ���� �ݺ��� for�� �̿�. 
     for (i=0; i<N_PLAYER; i++) //i�� ������ ��������� ��. i�� 0,1,2�� ���� �ݺ�.  
     {
         player_position[i] = 0; //i��° �÷��̾� 0���� �ʱ�ȭ. 
         player_coin[i] = 0; //������ 0���� �ʱ�ȭ
         player_status[i] = PLAYERSTATUS_LIVE; //ó���� �÷��̾�� ����־�� ��.
         
         //player_name�� �Է��� �ʿ��ϴϱ� printf-scanf �̿�. 
         printf("Player %i's Name : ", i);
         scanf("%s", player_name[i]); //���ڿ��� �޾ƾ��ϴϱ� %s. player_name��ü�� �������̱� ������ &�ʿ� ����.  
     }
      
      
      
  //............................................................................
  //2. �ݺ��� (�÷��̾� ��)
  
  do {
     int step;
     int coinResult;
     char c;

     //�Ʒ� �ڵ带 ��Ʈ ��ų����, �Ѿ����.. ���ǹ����� �ؿ� �ڵ带 ���ϵ���.
     if (player_status[turn] != PLAYERSTATUS_LIVE) //�÷��̾ ����ִ� ���°� �ƴϸ� ���� ������.  
     {
        turn = (turn+1)%N_PLAYER;
        continue; //continue�� ������ ���� �ݺ�. 
     }   
     
     
     
     //2-1. ���� & �÷��̾��� ���� ���
     board_printBoardStatus();
     
     for (i=0; i<N_PLAYER; i++)
     {  
         printPlayerPosition(i);
     }
     printPlayerStatus();
     

     
     //2-2. �ֻ��� ������
     printf("\n\n%s turn!", player_name[turn]);
     printf("press any key to roll a die!: ");
     scanf("%d", &c);
     fflush(stdin); //ǥ���Է� flush ��Ű��. ������ �ϴٰ� �Է��� �ް� �Ѿ�� ������. �̷��� �� �ǹ� ���� ������ �ȴ�.  
     step = rolldie();
     
     
     
     //2-3. �̵�
     player_position[turn] += step;
     
     if (player_position[turn] >= N_BOARD) // ������ �� ���� �ݺ�. 
     {
        player_position[turn] = N_BOARD-1;
     } 
     
     if (player_position[turn] == N_BOARD-1)
     {
        player_status[turn] = PLAYERSTATUS_END; 
        printf("player %s End.\n", player_name[turn]);
     } //14��° �� ���� �� �� �ڵ带 ������ ���Ѵ�. -> ���� �߻�
     
     
     //2-4. ���� �ݱ� 
     coinResult = board_getBoardCoin(pos);
     player_coin[turn] += coinResult;
     printf("\n\n %s player got %i coins and now you have i% coins!\n", player_name[turn], coinResult, player_coin[turn]);
      
      
      
     //2-5. ���� ��
     turn = (turn + 1)%N_PLAYER; //N_PLAYER�� �Ǵ� ���� �ٽ� 0���� ���ư�.  
     
     

     //2-6. if (���� : ��� �÷��̾ �ѹ��� ���� ��) 
     if (turn == 0)
     {
        //��� ���� 
        int shark_pos = board_stepShark();
        printf("Shark moved to %i\n", shark_pos); //"�� �̵��ߴ�." ��� 
        checkDie(); //�׾����� ��Ҵ��� �Ǵ��ϴ� �Լ� 
        
     }               
    } while(game_end() == 0);
      
      

  //............................................................................    
  //3. ���� (���� ���, ��� ��) 
  
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
