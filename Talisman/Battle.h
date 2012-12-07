#ifndef BATTLE_H
#define BATTLE_H
#include "Character.h"
#include "Game.h"
#include "AdventureCard.h"
using namespace std;

//class Character;
//class AdventureCard;
//class Game;

class Battle{

  public:
    Battle(void);
    virtual ~Battle(void);
    void fight(Character * character, AdventureCard * card, Game * game);
    int warriorAbility(int r1, Character * character, Game * game);
    int result(int r1, int r2);
};

#endif