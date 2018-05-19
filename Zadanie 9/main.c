#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "helpers.h"


int main()
{
	srand(time(NULL));
	int i;
	int armySize[2] = { 0,0 };
	Player P0, *Ptr0, P1, *Ptr1;
	Ptr0 = &P0;
	Ptr1 = &P1;

	printf("\n\n\n\n\n\t\t\tWelcome to Battle Arena 2k18!\n");
	printf("\n\t\t\t\tLoading");
	for (i = 0;i < 3;i++) {
		Sleep(750);
		printf(".");
	}
	CLEAR_SCREEN();

	if (beginning(0,armySize,Ptr0,NULL) != 0) {
		printf("Error.");
		return -1;
	}
	if (beginning(1, armySize+1, Ptr1,P0.name) != 0) {
		printf("Error.");
		return -1;
	}
	show_armies(Ptr0, Ptr1, armySize);
	battle(Ptr0, Ptr1, armySize);

	return 0;
}