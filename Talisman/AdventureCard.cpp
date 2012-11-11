#include "stdafx.h"
#include "AdventureCard.h"
#include "TException.h"
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

AdventureCard::AdventureCard(void)
{
}


AdventureCard::~AdventureCard(void)
{
}

void AdventureCard::createDeckFromFile(std::string deck_file, std::stack<AdventureCard*> &deck)
{
  //Read file and create deck
  ifstream file;
  file.open(deck_file);
  if (file.is_open()) {
    string line;
    AdventureCard* c;
    while (file.good()) {
      getline(file, line);
      if (line.size() <= 0) continue; //Empty line
      if (line[0] == ';') continue; //Comment line
      if (line == "SwordCard") c = new SwordCard();
      else if (line == "BagOfGoldCard") c = new BagOfGoldCard();
      else if (line == "TalismanCard") c = new TalismanCard();
      else if (line == "WitchCard") c = new WitchCard();
      else if (line == "HealerCard") c = new HealerCard();
      else if (line == "PrincessCard") c = new PrincessCard();
      else if (line == "GuideCard") c = new GuideCard();
      else if (line == "MarshCard") c = new MarshCard();
      else if (line == "ShrineCard") c = new ShrineCard();
      else if (line == "BlizzardCard") c = new BlizzardCard();
      else if (line == "MarketDayCard") c = new MarketDayCard();
      else if (line == "WolfCard") c = new WolfCard();
      else if (line == "WildBoarCard") c = new WildBoarCard();
      else if (line == "BearCard") c = new BearCard();
      else throw new InvalidCardFileException(line);
      deck.push(c);
    }
  }
  else {
    throw new FileOpenException(deck_file);
  }
  file.close();
}

string AdventureCard::title() { return this->_title; }
void AdventureCard::title(string title) { this->_title = title; }

unsigned char AdventureCard::number() { return this->_number; }
void AdventureCard::number(unsigned char number) { this->_number = number; }

string EnemyCard::type() { return this->_type; }
void EnemyCard::type(string type) { this->_type = type; }

string ObjectCard::type() { return this->_type; }
void ObjectCard::type(string type) { this->_type = type; }
