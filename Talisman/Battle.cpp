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

int Battle::cardFight(Character * character, EnemyCard * card, Game * game)
{
  system("cls");
  int enemyStrength = 3; //Enemy strength placeholder
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();
  bool evasion = false;
  bool save = false;

  /*
    Step 1:
    Choice to evade
  */
 
  /*
    Step 2:
    Cast spells
  */
  if (!character->spells().empty())
    evasion = evade(character, game);

  if (evasion)
  {
    game->getUI()->announce("You have chosen to evade the battle.");
    system("pause");
    return 0;
  }

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
    game->getUI()->announce(character->name() + " wins!" );
    //increase trophies
    //remove enemy
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    //enemy stays in place
    system("pause");
    return 0;
    break;
  case 2:
    game->getUI()->announce(character->name() + " loses!");
    save = saveLife(character, game);
    if (!save)
      character->lifeLost();
    //enemy stays in place
    system("pause");
    return -1;
    break;
  }

  

}


int Battle::playerFight(Character * c1, Character * c2, Game * game)
{
  system("cls");
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();
  bool evasion;
  /*
    Step 1:
    Choice to evade
  */
 
  /*
    Step 2:
    Cast spells
  */
  if (!c1->spells().empty())
    evasion = evade(c1, game);

  if (evasion)
  {
    game->getUI()->announce("You have chosen to evade the battle.");
    system("pause");
    return 0;
  }

  if (!c2->spells().empty())
    evasion = evade(c2, game);

  if (evasion)
  {
    game->getUI()->announce("You have chosen to evade the battle.");
    system("pause");
    return 0;
  }


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
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    return 0;
    system("pause");
    break;
  case 2:
    playerWin(c2, c1, game);
    system("pause");
    return -1;
    break;
  }
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
    if (!saveLife(loser, game))
      loser->lifeLost();
    game->getUI()->announce(loser->name() + " loses 1 life.");
    break;
  case 1:
    loser->setGold(loser->gold() - 1);
    game->getUI()->announce(loser->name() + " loses 1 gold.");
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

bool Battle::evade(Character * c, Game * game)
{
  //check for invisibility
  if (c->hasSpell("Invisibility"))
  {
    string options[2] = 
    {
      "Yes",
      "No"
    };
    unsigned char choice = game->getUI()->prompt(c->name() + ", you have the Invisibility spell. Will you use it to evade the battle?", options, 2);

    if (choice == 0)
    {
      //drop spell
      return true;
    }
    else
      return false;
  }
}

bool Battle::saveLife(Character * c, Game * game)
{
  if (c->hasObject("Shield"))
  {
    string options[2] = 
    {
      "Yes",
      "No"
    };
    unsigned char choice = game->getUI()->prompt(c->name() + ", you have a shield. Would you like to use it to protect yourself?", options, 2);

    if (choice == 0)
    {
      //drop shield
      return true;
    }
    else
      return false;
  }
}