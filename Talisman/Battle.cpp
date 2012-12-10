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

  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();
  bool evasion = false;
  bool save = false;

  /*
    Step 1 & 2:
    Cast spells and/or evade
  */
  if (!character->spells().empty())
    evasion = evade(character, game);

  if (evasion)
  {
    game->getUI()->announce("You have chosen to evade the battle.");
    system("pause");
    return 0;
  }

  //psychic combat check
  if (card->craft() > 0)
    return cardPsychic(character, card, game);

  /*
    Step 3 & 4:
    Character and creature rolls
  */
  cout << character->name() << " versus " << card->title() << endl << endl;
  cout << "The " << character->name() << " rolls a " << r1 << " for a total of " << character->strength() + r1 << " strength!\n";
  cout << "The " << card->title() << " rolls a " << r2 << " for a total of " << card->strength() + r2 << " strength!\n\n";
  
  if ((character->strength() + r1) <= (card->strength() + r2) && character->name() == "Warrior")
    r1 = this->warriorAbility(r1, character, game);

  if ((character->strength() + r1) <= (card->strength() + r2) && character->fate() > 0)
    r1 = this->useFate(r1, character, game);
  
  cout << endl << character->strength() + r1 << " versus " << card->strength() + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(character->strength() + r1, card->strength() + r2);
  switch (result){
  case 0:
    game->getUI()->announce(character->name() + " wins!" );
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    system("pause");
    return 0;
    break;
  case 2:
    game->getUI()->announce(character->name() + " loses!");
    save = saveLife(character, game);
    if (!save)
      character->lifeLost();
    system("pause");
    return -1;
    break;
  }
  return 0; //compiler
}


int Battle::playerFight(Character * c1, Character * c2, Game * game)
{
  system("cls");
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();
  bool evasion = false;
 
  /*
    Step 1 & 2:
    Cast spells and/or evade
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

  if (c1->name() == "Wizard")
  {
    string options[2] = 
    {
      "Yes",
      "No"
    };
    unsigned char choice = game->getUI()->prompt(c1->name() + ", your special ability allows you to initiate psychic combat. Will you?", options, 2);

    if (choice == 0)
      return playerPsychic(c1, c2, game);
  }

  /*
    Step 3 & 4:
    Character rolls
  */
  cout << c1->name() << " versus " << c2->name() << endl << endl;
  cout << "The " << c1->name() << " rolls a " << r1 << " for a total of " << c1->strength() + r1 << " strength!\n";
  cout << "The " << c2->name() << " rolls a " << r2 << " for a total of " << c2->strength() + r2 << " strength!\n\n";
  
  if ((c1->strength() + r1) <= (c2->strength() + r2) && c1->name() == "Warrior")
    r1 = this->warriorAbility(r1, c1, game);

  if ((c2->strength() + r2) <= (c1->strength() + r1) && c2->name() == "Warrior")
    r2 = this->warriorAbility(r2, c2, game);
  
  if ((c1->strength() + r1) <= (c2->strength() + r2) && c1->fate() > 0)
    r1 = this->useFate(r1, c1, game);

  if ((c2->strength() + r2) <= (c1->strength() + r1) && c2->fate() > 0)
    r2 = this->useFate(r2, c2, game);

  cout << endl << c1->strength() + r1 << " versus " << c2->strength() + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(c1->strength() + r1, c2->strength() + r2);
  switch (result){
  case 0:
    playerWin(c1, c2, game, false);
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    return 0;
    system("pause");
    break;
  case 2:
    playerWin(c2, c1, game, false);
    system("pause");
    return -1;
    break;
  }
  system("pause");

  return 0; //compiler
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

void Battle::playerWin(Character * winner, Character * loser, Game * game, bool ifPsychic)
{
  cout << endl;
  string options[3]= { loser->name() + " loses 1 life", "", "" };
  int numChoices = 1;
  bool hasGold = false;
  bool hasObject = false;

  if (loser->gold() > 0)
  {
    options[numChoices] = loser->name() + " loses 1 gold";
    numChoices++;
    hasGold = true;
  }

  if (!loser->inventory().empty())
  {
    options[numChoices] = loser->name() + " loses 1 object";
    numChoices++;
    hasObject = true;
  }

  if (numChoices == 1)
  {
    if (ifPsychic)
      loser->lifeLost();
    else if (!saveLife(loser, game))
        loser->lifeLost();
    game->getUI()->announce(loser->name() + " loses 1 life.");
    return;
  }

  unsigned char choice = game->getUI()->prompt("As the winner, " + winner->name() + " can choose one of the following options:", options, 3);

  switch (choice)
  {
  case 0: 
    if (ifPsychic)
      loser->lifeLost();
    else if (!saveLife(loser, game))
        loser->lifeLost();
    game->getUI()->announce(loser->name() + " loses 1 life.");
    break;
  case 1:
    if (hasGold == true)
    {
      loser->setGold(loser->gold() - 1);
      game->getUI()->announce(loser->name() + " loses 1 gold.");
    }
    else if (hasObject == true)
      takeObject(winner, loser, game);
    break;
  case 2:
    takeObject(winner, loser, game);
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
  if (c->findSpell("Invisibility") != NULL)
  {
    string options[2] = 
    {
      "Yes",
      "No"
    };
    unsigned char choice = game->getUI()->prompt(c->name() + ", you have the Invisibility spell. Will you use it to evade the battle?", options, 2);

    if (choice == 0)
    {
      c->drop(c->findSpell("Invisibility"));
      return true;
    }
    else
      return false;
  }

  return false; //compiler
}

bool Battle::saveLife(Character * c, Game * game)
{
  //check for shield
  if (c->findObject("Shield") != NULL)
  {
    string options[2] = 
    {
      "Yes",
      "No"
    };
    unsigned char choice = game->getUI()->prompt(c->name() + ", you have a shield. Would you like to use it to protect yourself?", options, 2);

    if (choice == 0)
    {
      c->drop(c->findObject("Shield"));
      return true;
    }
    else
      return false;
  }

  return false; //compiler
}

int Battle::cardPsychic(Character * character, EnemyCard * card, Game * game)
{
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();

  game->getUI()->announce(card->title() + " initiates psychic combat!");

  cout << character->name() << " versus " << card->title() << endl << endl;
  cout << "The " << character->name() << " rolls a " << r1 << " for a total of " << character->craft() + r1 << " craft!\n";
  cout << "The " << card->title() << " rolls a " << r2 << " for a total of " << card->craft() + r2 << " craft!\n\n";

  if ((character->craft() + r1) <= (card->craft() + r2) && character->fate() > 0)
    r1 = this->useFate(r1, character, game);
  
  cout << endl << character->craft() + r1 << " versus " << card->craft() + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(character->craft() + r1, card->craft() + r2);
  switch (result){
  case 0:
    game->getUI()->announce(character->name() + " wins!" );
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    system("pause");
    return 0;
    break;
  case 2:
    game->getUI()->announce(character->name() + " loses!");
    character->lifeLost();
    system("pause");
    return -1;
    break;
  }

  return 0; //compiler
}

int Battle::playerPsychic(Character * c1, Character * c2, Game * game)
{
  int r1, r2;
  r1 = game->roll();
  r2 = game->roll();

  game->getUI()->announce(c1->name() + " initiates psychic combat!");
  cout << c1->name() << " versus " << c2->name() << endl << endl;
  cout << "The " << c1->name() << " rolls a " << r1 << " for a total of " << c1->craft() + r1 << " craft!\n";
  cout << "The " << c2->name() << " rolls a " << r2 << " for a total of " << c2->craft() + r2 << " craft!\n\n"; 
  
  if ((c1->craft() + r1) <= (c2->craft() + r2) && c1->fate() > 0)
    r1 = this->useFate(r1, c1, game);

  if ((c2->craft() + r2) <= (c1->craft() + r1) && c2->fate() > 0)
    r2 = this->useFate(r2, c2, game);

  cout << endl << c1->craft() + r1 << " versus " << c2->craft() + r2 << ": ";


  /*
    Step 5:
    Compare
  */
  int result = this->result(c1->craft() + r1, c2->craft() + r2);
  switch (result){
  case 0:
    playerWin(c1, c2, game, true);
    system("pause");
    return 1;
    break;
  case 1:
    game->getUI()->announce("Draw!");
    return 0;
    system("pause");
    break;
  case 2:
    playerWin(c2, c1, game, true);
    system("pause");
    return -1;
    break;
  }

  return 0; //compiler
}

void Battle::takeObject(Character * winner, Character * loser, Game * game)
{
  string * options = new string[loser->inventory().size()];
  int i = 0;

  game->getUI()->announce(loser->name() + " has the following objects:");


  for (auto it = loser->inventory().begin(); it != loser->inventory().end(); it++)
  {
    options[i] = (*it)->title();
  }
  unsigned char choice = game->getUI()->prompt(winner->name() + ", which item would you like to take?", options, loser->inventory().size());

  game->getUI()->announce(winner->name() + " has taken " + loser->inventory()[choice]->title() + " from " + loser->name() + ".");
  
  winner->pickup(loser->inventory()[choice]);
  loser->drop(loser->inventory()[choice]);

}

