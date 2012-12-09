#ifndef BATTLE_H
#define BATTLE_H
#include "Character.h"
#include "Game.h"
#include "AdventureCard.h"
using namespace std;

class Battle{

  public:
    Battle(void);
    virtual ~Battle(void);

    /*
      Method: cardFight
      Initiates player versus encounter card battle
    */
    void cardFight(Character * character, AdventureCard * card, Game * game);

    /*
      Method: playerFight
      Initiates player versus player battle
    */
    void playerFight(Character * c1, Character * c2, Game * game);

    /*
      Method: playerWin
      Outputs the choices the winning player can make
    */
    void playerWin(Character * winner, Character * loser, Game * game);

    /*
      Method: warriorAbility
      Asks the player if they'd like to use warrior ability
    */
    int warriorAbility(int r1, Character * character, Game * game);

    /*
      Method: useFate
      Asks the player if they'd like to use a fate token
    */
    int useFate(int r1, Character * character, Game * game);

    /*
      Method: result
      Check the result of the batte
      0 = initiator wins
      1 = draw
      2 = initiator loses
    */
    int result(int r1, int r2);

    /*
      Method: promptSpells
      Prompts the player to use a spell
    */
    void promptSpells(Character * c, Game * game);
    
};

#endif