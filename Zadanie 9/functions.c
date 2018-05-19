#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "helpers.h" 
 
char* meno(int ID) {
	printf("Enter name of player %d:", ID+1);
	char name[10];
	int test;
	do {
		test = scanf("%s", name);
	} while (test != 1);
	return name;
}
Minion* goldTest() {
	Minion *goldTest = (Minion*)malloc(6*sizeof(Minion)), Peasant = peasant, Footman = footman, Defender = defender, Archer = archer, Berserker = berserker, Wizard = wizard;
	goldTest[0] = Peasant;
	goldTest[1] = Footman;
	goldTest[2] = Defender;
	goldTest[3] = Archer;
	goldTest[4] = Berserker;
	goldTest[5] = Wizard;
	return goldTest;
}
void help() {
	CLEAR_SCREEN();
	printf("INFO:\n");
	printf("\tHP = Body zivota\tAtt = Body utoku\tDef = Body obrany\n");
	printf("\tmelee = utok zblizka\tranged = utok z dialky\n");
	printf(" Specialne schopnosti: Battle Rage - po smrti spolubojovnika +1 utok\n");
	printf("                       Armor Boost - pridava vsetkym spolubojovnikom +1 obranu\n");
	printf("                       Tank - nepriatelia s utokom z blizka nemozu utocit na ostatnych\n");
	printf("                       Crit Boost - pridava 25%% sancu na kriticky zasah\n");
	printf("                       Attack Boost - pridava vsetkym spolubojovnikom +1 utok\n");
	printf("                       Health Boost - pridava vsetkym spolubojovnikom +1 zdravia\n");
	printf(" Hra prebieha na kola, v ktorom hrac vysle 1 bojovnika proti 1 bojovnikovy supera.\n");
	printf(" Zranenie ktore udeli sa vypocita z jeho utoku, a zranenie ktore utrzi z obrany protivnika.\n");
	printf(" Obe strany maju sancu udelit kriticky zasah (2-nasobny). Hra konci ked je jedna z armad porazena.\n");
	printf("\nPre navrat stlac ENTER.\n");
	system("pause");
}
Minion* minionsInit(int playerID, int* armySize, Player* Ptr, Minion* goldTest)
{
	Minion *minions = (Minion*)calloc(15 , sizeof(Minion));
	int gold = 15, i, ID = 0, brPoint = 0;
	char cInput;

	while (gold >= 0) {
		CLEAR_SCREEN();
		printf("%s it's time to build your army. You have %d gold left.\n", Ptr->name, gold);
		printf("You can choose from these warriors:\n");
		printf("\n\t ID\tName\tHP/Att/Def   Range\tSpecial\t\tPrice  \n");
		printf("\t 1.    Peasant    3/2/0      melee    Battle Rage         1\n");
		printf("\t 2.    Footman    5/2/2      melee    Armor Boost         2\n");
		printf("\t 3.    Defender   5/1/3      melee    Tank                2\n");
		printf("\t 4.    Archer     4/3/1      ranged   Crit Boost          3\n");
		printf("\t 5.    Berserker  4/5/0      melee    Attack Boost        4\n");
		printf("\t 6.    Wizard     4/3/2      ranged   Health Boost        5\n");
		printf("\nCurrent warband :[");
		for (i = 0;i<*armySize;i++) {
			printf("%s", minions[i].name);
			if (i != (*armySize - 1))
				printf(", ");
			if ((i + 1) % 5 == 0)
				printf("\n\t");
			
		}
		
		printf("]\n");
		printf("\n Press 'H' for info.\n");
		if (gold == 0) {
			printf("Press 'A', if you are satisfied with your choices or 'R' to reset.\n");
			while (1) {
				if (_kbhit()) {
					cInput = _getch();
					if (cInput == 'A' || cInput == 'a') {
						brPoint = 1;
						break;
					}
					if (cInput == 'R' || cInput == 'r') {
						free(minions);
						*armySize = 0;
						Ptr->minions = minionsInit(ID, armySize, Ptr, goldTest);
						return  minions;
					}
				}
			}
		}
		if (brPoint == 1) {
			break;
		}
		while (1) {
			if (_kbhit()) {
				cInput = _getch();
				if (cInput == 'H' || cInput == 'h') {
					help();
					break;
				}
				if (goldTest[cInput - 49].cost > gold) {
					printf("You can't buy this one! Need %d more gold. Pick someone else.\n", goldTest[cInput - 49].cost - gold);
					Sleep(1000);
					break;
				}
				else if (cInput == '1') {
					Minion minion1 = peasant;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				else if (cInput == '2') {
					Minion minion1 = footman;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				else if (cInput == '3') {
					Minion minion1 = defender;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				else if (cInput == '4') {
					Minion minion1 = archer;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				else if (cInput == '5') {
					Minion minion1 = berserker;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				else if (cInput == '6') {
					Minion minion1 = wizard;
					minions[ID++] = minion1;
					gold -= minion1.cost;
				}
				if (cInput >= '1' && cInput <= '6') {
					*armySize += 1;
					break;
				}
			}
		}
	}
	return  minions;
}
void show_stats(Minion* minion, int ID)
{
	printf("%d. %s HP:%d/ATT:%d/DEF:%d %c", ID, minion->name, minion->HP, minion->ATT, minion->DEF, minion->range);
}
void show_armies(const Player* P0, const Player* P1, const int* armySize)
{
	int i, size;
	printf("\t\t\t Battleground\n");
	printf("Player %s:\t\t\t\tPlayer %s:\n",P0->name,P1->name);
	if (armySize[0] > armySize[1])
		size = armySize[0];
	else
		size = armySize[1];
	for (i = 0; i < size;i++) {
		if (i<armySize[0]) {
			if (P0->minions[i].HP <= 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			show_stats(&P0->minions[i], i + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
			printf("\t\t\t");
		printf("\t\t");
		if (i<armySize[1]) {
			if (P1->minions[i].HP <= 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			show_stats(&P1->minions[i], i + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		printf("\n");
	}
}

void attack(Minion* attacker, Minion* deffender) {
	int dmg, retDmg, x, y;
	x =rand()%(attacker->ATT * 2) - rand() % (deffender->DEF);
	y =rand()%(deffender->ATT)+1 - rand() % (attacker->DEF);
	if (y < 0)
		y *= -1;
	if (x < 0)
		x *= -1;
	if (x == 0)
		++x;
	if (y == 0)
		++y;
	if (attacker->range == 'M') {
		dmg = rand() % (x) + (attacker->ATT / 2 + 1);
		retDmg = rand() % (y) + (deffender->ATT / 2 + 1);
		printf("%s dealt %d damage - %s returned %d damage.\n", attacker->name, dmg, deffender->name, retDmg);
	}
	else if (attacker->range == 'R') {
		
		dmg = rand() % (x) + (attacker->ATT / 2 + 1);
		if (deffender->range == 'R') {
			retDmg = rand() % (y) + (deffender->ATT / 2 + 1);
			printf("%s hit from distance for %d damage, but %s fought back for %d damage.\n", attacker->name, dmg, deffender->name, retDmg);
		}
		else if (deffender->range == 'M'){
			retDmg = 0;
			printf("%s attacked from range and dealt %d damage to %s.\n", attacker->name, dmg, deffender->name);
		}
	}
	
	Sleep(1500);
	attacker->HP -= retDmg;
	deffender->HP -= dmg;
}
void battle(Player* P0, Player* P1, int* armySize)
{
	char cInput;
	int att, deff, round = 0, alive = 1;
	while (alive>0) {
		if (armySize[0] <= 0 || armySize[1] <= 0)
			break;
		CLEAR_SCREEN();
		show_armies(P0, P1, armySize);
		printf("\n\t\t\t Round: %i\n", round++);
		printf("\n%s, choose your fighter and enemy you wish to attack.\n",P0->name);
		while (1) {
			if (_kbhit()) {
				cInput = _getch();
				if ((cInput - 49) <= armySize[0] && P0->minions[cInput - 49].HP > 0 && (cInput - 49 >= 0)) {
					printf("%s's %s", P0->name, P0->minions[cInput - 49].name);
					att = cInput - 49;
					break;
				}
			}
		}
		while (1) {
			if (_kbhit()) {
				cInput = _getch();
				if ((cInput - 49) <= armySize[0] && P1->minions[cInput - 49].HP > 0 && (cInput - 49 >= 0)) {
					printf(" vs. %s's %s\n", P1->name, P1->minions[cInput - 49].name);
					deff = cInput - 49;
					break;
				}
			}	
		}
		system("pause");
		attack(&P0->minions[att], &P1->minions[deff]);
		alive = check_army(P0,P1, armySize);
		if (armySize[0] <= 0 || armySize[1] <= 0)
			break;
		CLEAR_SCREEN();
		show_armies(P0, P1, armySize);
		printf("\n\t\t\t Round: %i\n", round);
		printf("\n%s, choose your fighter and enemy you wish to attack.\n", P1->name);
		while (1) {
			if (_kbhit()) {
				cInput = _getch();
				if ((cInput - 49) <= armySize[0] && P1->minions[cInput - 49].HP > 0 && (cInput - 49 >= 0)) {
					printf("%s's %s", P1->name, P1->minions[cInput - 49].name);
					att = cInput - 49;
					break;
				}
			}
		}
		while (1) {
			if (_kbhit()) {
				cInput = _getch();
				if ((cInput - 49) <= armySize[0] && P0->minions[cInput - 49].HP > 0 && (cInput - 49 >= 0)) {
					printf(" vs. %s's %s\n", P0->name, P0->minions[cInput - 49].name);
					deff = cInput - 49;
					break;
				}
			}
		}

		system("pause");
		attack(&P1->minions[att], &P0->minions[deff]);
		alive = check_army(P0,P1,armySize+1);
		if (armySize[0] <= 0 || armySize[1] <= 0)
			break;
	}
	if (armySize[0] > 0 && armySize[1] == 0) {
		printf("%s's army destroyed their opponents and wins this battle.\n",P0->name);
	}
	else if (armySize[0] == 0 && armySize[1] > 0) {
		printf("%s proved to be more experienced general this day and his army is victorius!\n", P1->name);
	}
	else if (armySize[0] == 0 && armySize[1] == 0) {
		printf("After rough battle, casualities are enormous and there's no winner.\n");
	}

}
void death(Player* P, int* armySize, int ID) {
	for (int i = ID;i < *armySize;i++) {
		P->minions[i] = P->minions[i + 1];
	}
	*armySize -= 1;
	Sleep(1500);
}
int check_army(Player* P0,Player* P1,int* armySize) {
	int i,alive = 0;
	for (i = 0;i < armySize[0];i++) {
		if (P0->minions[i].HP <= 0) {
			printf("%s's %s died.", P0->name, P0->minions[i].name);
			death(P0, &armySize[0], i);
		}
		else {
			alive++;
		}
	}
	for (i = 0;i < armySize[1];i++) {
		if (P1->minions[i].HP <= 0) {
			printf("\n%s's %s died.\n", P1->name, P1->minions[i].name);
			death(P1, &armySize[1], i);
		}
		else {
			alive++;
		}
	}
	return alive;
	}

int beginning(int ID, int* armySize, Player* Ptr,char* previous) {
	
	strcpy(Ptr->name, meno(ID));
	if (ID > 0 && strcmp(previous,Ptr->name)== 0) {
		do {
			printf("Invalid username.\n");
			strcpy(Ptr->name, meno(ID));
		} while (strcmp(previous, Ptr->name) == 0);
	}
	Ptr->minions = (Minion*)malloc(15 * sizeof(Minion*));
	Ptr->minions = minionsInit(ID, armySize, Ptr,goldTest());
	CLEAR_SCREEN();
	return 0;
}




