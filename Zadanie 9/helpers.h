#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#define armorBoost 1
#define attackBoost 2
#define critBoost 3
#define healthBoost 4
#define tank 5
#define battleRage 6

#define peasant {"Peasant",3,2,1,'M',battleRage, 1 }	
#define footman { "Footman" , 5,2,2, 'M',armorBoost,2 }
#define defender { "Defender" , 5,1,3, 'M',tank,2 }
#define archer { "Archer", 3,3,1, 'R',critBoost,3 }
#define berserker { "Berserker", 4,5,1, 'M',attackBoost,4 }
#define wizard { "Wizard", 3,3,2, 'R',healthBoost,5 }
//..................................................
typedef struct _minion {
	char name[10];
	int HP; int ATT; int DEF;
	char range; int special; int cost;
} Minion;

typedef struct _player {
	char name[10];
	Minion *minions;
}Player;
//.........................................
//FUNCTIONS

char* meno(int ID);
int beginning(int ID, int* armySize, Player* Ptr, char* previous);
Minion* minionsInit(int playerID, int* armySize, Player* Ptr,Minion* goldTest);
void show_stats(Minion* minion, int ID);
void show_armies(const Player* P0, const Player* P1, const int* armySize);
int check_army(Player* P0, Player* P1, int* armySize);
void battle(Player* P0, Player* P1, int* armySize);
void attack(Minion* attacker, Minion* deffender);
Minion* goldTest();
void help();
void death(Player* P, int* armySize, int ID);

#ifdef _WIN32
#define CLEAR_SCREEN()	system("cls")
#else
#define CLEAR_SCREEN()	printf("\x1b[2J");
#endif

#endif // HELPERS_H_INCLUDED