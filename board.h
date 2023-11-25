//
// board.h
// SHARK GAME
//
// Created by Sieun Lee on 2023/11/21
//

#include <stdio.h>
#include <stdlib.h>

#define N_BOARD       15 //코딩에선 메크로로 정의 하는게 유리 

#define BOARDSTATUS_OK     1 //main에게 알려주기 위해 board.h 에 삽입. main은 board.h를 포함한다.  
#define BOARDSTATUS_NOK    0



int board_initboard(void); //보드 초기화 
int board_printBoardStatus(void); //전체 보드의 상태 출력 

int board_getBoardStatus(int pos); //입력은 특정 위치가 파손되었는지 안되었는지 알아야 되니까. 입력:특정위치, 출력:보드상태 
int board_getBoardCoin(int pos); //동전이 있는지 파악, 동전이 있으면 습득 , 입력:위치

int board_getSharkPosition(void); //상어는 어딘가에 있을테니 입력은 필요없음. 출력:상어의 위치
int board_stepShark(void); //알아서 이동하면 되니까 입력 필요없음.

