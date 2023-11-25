//
// board.h
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

#include <stdio.h>
#include <stdlib.h>

#define N_BOARD       15 //�ڵ����� ��ũ�η� ���� �ϴ°� ���� 

#define BOARDSTATUS_OK     1 //main���� �˷��ֱ� ���� board.h �� ����. main�� board.h�� �����Ѵ�.  
#define BOARDSTATUS_NOK    0



int board_initboard(void); //���� �ʱ�ȭ 
int board_printBoardStatus(void); //��ü ������ ���� ��� 

int board_getBoardStatus(int pos); //�Է��� Ư�� ��ġ�� �ļյǾ����� �ȵǾ����� �˾ƾ� �Ǵϱ�. �Է�:Ư����ġ, ���:������� 
int board_getBoardCoin(int pos); //������ �ִ��� �ľ�, ������ ������ ���� , �Է�:��ġ

int board_getSharkPosition(void); //���� ��򰡿� �����״� �Է��� �ʿ����. ���:����� ��ġ
int board_stepShark(void); //�˾Ƽ� �̵��ϸ� �Ǵϱ� �Է� �ʿ����.

