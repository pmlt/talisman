#include "stdafx.h"
#include "Battle.h"
#include <iostream>
using namespace std;

Battle::Battle(void)
{
}

Battle::~Battle()
{
}

void Battle::cardFight(Character * character, AdventureCard * card, Game * game)
{
  system("cls");
  int enemyStrength = 3; //Enemy strength placeholder
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();

  /*
    Step 1:
    Choice to evade
  */
 
  /*
    Step 2:
    Cast spells
  */
  if (!character->spells().empty())
    promptSpells(character, game);


  /*
    Step 3 & 4:
    Character and creature rolls
  */
  cout << character->name() << " versus " << card->title() << endl << endl;
  cout << "The " << character->name() << " rolls a " << r1 << " for a total of " << character->strength() + r1 << " strength!\n";
  cout << "The " << card->title() << " rolls a " << r2 << " for a total of " << enemyStrength + r2 << " strength!\n\n";
  
  if (character->name() == "Warrior")
    r1 = this->warriorAbility(r1, character, game);

  if (character->fate() > 0)
    r1 = this->useFate(r1, character, game);
  
  cout << endl << character->strength() + r1 << " versus " << enemyStrength + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(character->strength() + r1, enemyStrength + r2);
  switch (result){
  case 0:
    cout << character->name() << " wins!" << endl;
    //increase trophies
    //remove enemy
    break;
  case 1:
    cout << "Draw!" << endl;
    //enemy stays in place
    break;
  case 2:
    cout << character->name() << " loses!" << endl;
    character->setLife(character->life() - 1);
    //check if character is dead
    //enemy stays in place
    break;
  }

  cout << endl;
  system("pause");

}

void Battle::playerFight(Character * c1, Character * c2, Game * game)
{
  system("cls");
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();

  /*
    Step 1:
    Choice to evade
  */
 
  /*
    Step 2:
    Cast spells
  */

  /*
    Step 3 & 4:
    Character rolls
  */
  cout << c1->name() << " versus " << c2->name() << endl << endl;
  cout << "The " << c1->name() << " rolls a " << r1 << " for a total of " << c1->strength() + r1 << " strength!\n";
  cout << "The " << c2->name() << " rolls a " << r2 << " for a total of " << c2->strength() + r2 << " strength!\n\n";
  
  if (c1->name() == "Warrior")
    r1 = this->warriorAbility(r1, c1, game);

  if (c2->name() == "Warrior")
    r2 = this->warriorAbility(r2, c2, game);
  
  if (c1->fate() > 0)
    r1 = this->useFate(r1, c1, game);

  if (c2->fate() > 0)
    r2 = this->useFate(r2, c2, game);

  cout << endl << c1->strength() + r1 << " versus " << c2->strength() + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(c1->strength() + r1, c2->strength() + r2);
  switch (result){
  case 0:
    playerWin(c1, c2, game);
    break;
  case 1:
    cout << "Draw!" << endl;
    break;
  case 2:
    playerWin(c2, c1, game);
    break;
  }
  
  cout << endl;
  system("pause");
}

int Battle::warriorAbility(int r1, Character * character, Game * game)
{
  string options[2] = 
  {
    "Yes",
    "No"
  };
  unsigned char choice = game->getUI()->prompt(character->name() + ", you can activate your special ability to re-roll your attack. Will you?", options, 2);

  if (choice == 0)
  {
	r1 = game->roll();
	cout << endl << "Your new attack roll is " << r1 << ", giving you a total of " << character->strength() + r1 << " strength!\n\n";
  }
  
  return r1;
}


int Battle::result(int r1, int r2)
{
  if (r1 > r2)
    return 0;
  else if (r1 == r2)
    return 1;
  else if (r1 < r2)
    return 2;

  return 1; //make compiler happy
}

void Battle::playerWin(Character * winner, Character * loser, Game * game)
{
  cout << endl;

  string options[3] = 
  {
    loser->name() + " loses 1 life",
    loser->name() + " loses 1 gold",
    loser->name() + " loses 1 object"
  };
  unsigned char choice = game->getUI()->prompt("As the winner, " + winner->name() + " can choose one of the following options:", options, 3);

  switch (choice)
  {
  case 0: 
    loser->setLife(loser->life() - 1);
    break;
  case 1:
    loser->setGold(loser->gold() - 1);
    break;
  case 2:
    //take an object
    break;

  }
}

int Battle::useFate(int r1, Character * character, Game * game)
{
  string options[2] = 
  {
    "Yes",
    "No"
  };
  unsigned char choice = game->getUI()->prompt(character->name() + ", you can spend 1 fate token to reroll your attack. Will you?", options, 2);

  if (choice == 0)
  {
    character->setFate(character->fate() - 1);
	r1 = game->roll();
	cout << endl << "Your new attack roll is " << r1 << ", giving you a total of " << character->strength() + r1 << " strength!\n\n";
  }
  
  return r1;
}

void Battle::promptSpells(Character * c, Game * game)
{
  //check for invisibility

}