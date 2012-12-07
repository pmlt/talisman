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

void Battle::fight(Character * character, AdventureCard * card, Game * game)
{
  system("cls");

  int enemyStrength = 3; //Enemy strength placeholder
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();
  cout << character->name() << " versus " << card->title() << endl << endl;
  cout << "The " << character->name() << " rolls a " << r1 << " for a total of " << character->strength() + r1 << " strength!\n";
  cout << "The " << card->title() << " rolls a " << r2 << " for a total of " << enemyStrength + r2 << " strength!\n\n";
  
  if (character->name() == "Warrior")
    r1 = this->warriorAbility(r1, character, game);
  
  cout << endl << character->strength() + r1 << " versus " << enemyStrength + r2 << ": ";

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
    //decrement life
    //enemy stays in place
    break;
  }

  cout << endl;
  system("pause");

}

int Battle::warriorAbility(int r1, Character * character, Game * game){
  string options[2] = 
  {
    "Yes",
    "No"
  };
  unsigned char choice = game->getUI()->prompt("You can activate your special ability to re-roll your attack, will you?", options, 2);

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
}