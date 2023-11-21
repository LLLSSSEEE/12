//
// board.c
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

#include <stdio.h>
#include <stdlib.h>

#define N_BOARD     20 //�ڵ����� ��ũ�η� ���� �ϴ°� ���� 

#define N_COINPOS     12
#define MAX_COIN     4
/*
#define BOARDSTATUS_OK     1 //���� ������ �ƹ��ų� ��� ����. ��ũ�θ� �̷��� �����س��´�. ���Ƿ� �ǹ� �ο�. 
#define BOARDSTATUS_NOK    0  
*/



//�ʿ��� ���� �����ֱ� 
static int board_status[N_BOARD]; //���° ĭ�� �ļյǾ�����, �ƴ����� �Ǵ�. 15���� ������ �迭�� �������. 1�̸� ������, 0�� �ļյ�. 
static int board_coin[N_BOARD]; //i��° ĭ�� ������ �  ������ �ִ���  

static int board_sharkPosition; //����� ��ġ ����. 
                                //static�� �̿��� ����. ���� �մ��� ���ϵ���. 
                               
                              
                              
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
        int flag = 0; // ���� �ƹ��ų� ��� 0���� �ʱ�ȭ 
        while(flag == 0) //����� �������ִ����� �ľ� 
        {
               int allocPos = rand()%N_BOARD; // �Ҵ��ϴ� ��ġ. rand�Լ��� �ҷ���. 0���� 14���� 
               if (board_coin[allocPos] == 0) // allocpos�� 0�̸� �Ҵ��� �ȵ� ��. 
               { 
                   board_coin[allocPos] = rand()%MAX_COIN+1;
                   flag = 1;
               }
        }
    }    
     
    return 0;              
}



int board_printBoardStatus(void)
   //board �� ������ֱ� 
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
    // �ܼ��� ������ȸ�Լ�  
     return board_status[pos]; //�� ��ü ��ȯ 
}


int board_getBoardCoin(int pos)
{ 
    int coin = board_coin[pos]; // �Ʒ����� �ʿ��ߴ� ��������. 0���� ��������� ���� �̸� ����.  
    //coin�� �ѹ� �ֿ�� �������� �Ŵϱ� �׳� return�� �ϸ� �ȵǰ� 0���� �������� �Ѵ�.  
    board_coin[pos] = 0; // �ٵ� �̷��� �ϸ� ������ �߻��� ���̴�. �� �迭�� ��Ҹ� 0���� ������� ���¿��� 
    return coin; // �� �迭�� �״�� ��ȯ���ָ� 0�ۿ� �ȳ��´�. ���� �������� �ʿ�. 
}


//------------------------------------------------------------------------------
//int board_getSharkPosition(void);
//int board_stepShark(void);
