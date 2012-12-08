#include "stdafx.h"
#include "AdventureCard.h"
#include "TException.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

AdventureCard::AdventureCard(void) : _number(0), _isPurchaseCard(false)
{
}


AdventureCard::~AdventureCard(void)
{
}

void AdventureCard::createDeckFromFile(std::string deck_file, std::vector<AdventureCard*> &deck, bool set_purchase_flag)
{
  //Read file and create deck
  ifstream file;
  file.open(deck_file);
  if (file.is_open()) {
    string line, ident;
    AdventureCard* c;
    while (file.good()) {
      getline(file, line);
      if (line.size() <= 0) continue; //Empty line
      if (line[0] == ';') continue; //Comment line

      unsigned int howmany = line[0] - ASCII0;
      ident = line.substr(2);
      
      for (int i=0; i < howmany; i++) {
        if (ident == "SwordCard") c = new SwordCard();
        else if (ident == "BagOfGoldCard") c = new BagOfGoldCard();
        else if (ident == "TalismanCard") c = new TalismanCard();
        else if (ident == "WitchCard") c = new WitchCard();
        else if (ident == "HealerCard") c = new HealerCard();
        else if (ident == "PrincessCard") c = new PrincessCard();
        else if (ident == "GuideCard") c = new GuideCard();
        else if (ident == "MarshCard") c = new MarshCard();
        else if (ident == "ShrineCard") c = new ShrineCard();
        else if (ident == "BlizzardCard") c = new BlizzardCard();
        else if (ident == "MarketDayCard") c = new MarketDayCard();
        else if (ident == "WolfCard") c = new WolfCard();
        else if (ident == "WildBoarCard") c = new WildBoarCard();
        else if (ident == "BearCard") c = new BearCard();
        else if (ident == "CounterSpellCard") c = new CounterSpellCard();
        else if (ident == "DestroyMagicCard") c = new DestroyMagicCard();
        else if (ident == "HealingCard") c = new HealingCard();
        else if (ident == "InvisibilityCard") c = new InvisibilityCard();
        else if (ident == "ImmobilityCard") c = new ImmobilityCard();
        else if (ident == "PreservationCard") c = new PreservationCard();
        else throw new InvalidCardFileException(line);
        if (set_purchase_flag) c[i].setPurchaseCard(true);
        deck.push_back(c);
      }
    }
  }
  else {
    throw new FileOpenException(deck_file);
  }
  file.close();
  //Randomize the deck
  std::random_shuffle(deck.begin(), deck.end());
}

bool AdventureCard::isPurchaseCard() const { return _isPurchaseCard; }
void AdventureCard::setPurchaseCard(bool isPurchase) { _isPurchaseCard = isPurchase; }
unsigned char AdventureCard::number() { return this->_number; }
void AdventureCard::number(unsigned char number) { this->_number = number; }

void AdventureCard::encounter(Character* character, Game* game)
{
  //Demo: just print card's title for now
  game->getUI()->announce("You have encountered the " + this->title() + "!");
}

string EnemyCard::type() { return this->_type; }
void EnemyCard::type(string type) { this->_type = type; }

string ObjectCard::type() { return this->_type; }
void ObjectCard::type(string type) { this->_type = type; }

string SwordCard::title() { return "Sword"; }
string BagOfGoldCard::title() { return "Bag of Gold"; }
string TalismanCard::title() { return "Talisman"; }
string WitchCard::title() { return "Witch"; }
string HealerCard::title() { return "Healer"; }
string PrincessCard::title() { return "Princess"; }
string GuideCard::title() { return "Guide"; }
string MarshCard::title() { return "Marsh"; }
string ShrineCard::title() { return "Shrine"; }
string BlizzardCard::title() { return "Blizzard"; }
string MarketDayCard::title() { return "Market Day"; }
string WolfCard::title() { return "Wolf"; }
string WildBoarCard::title() { return "Wild Boar"; }
string BearCard::title() { return "Bear"; }
string CounterSpellCard::title() { return "CounterSpell"; }
string DestroyMagicCard::title() { return "DestroyMagic"; }
string HealingCard::title() { return "Healing"; }
string InvisibilityCard::title() { return "Invisibility"; }
string ImmobilityCard::title() { return "Immobility"; }
string PreservationCard::title() { return "Preservation"; }
