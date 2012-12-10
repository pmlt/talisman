#include "stdafx.h"
#include "AdventureCard.h"
#include "TException.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

AdventureCard::AdventureCard(unsigned char number) : _number(number), _isPurchaseCard(false)
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
      
      for (unsigned int i=0; i < howmany; i++) {
        if (ident == "SwordCard") c = new SwordCard();
        else if (ident == "BagOfGoldCard") c = new BagOfGoldCard();
        else if (ident == "TalismanCard") c = new TalismanCard();
        else if (ident == "WaterBottleCard") c = new WaterBottleCard();
        else if (ident == "ShieldCard") c = new ShieldCard();
        else if (ident == "AxeCard") c = new AxeCard();
        else if (ident == "RaftCard") c = new RaftCard();
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

bool AdventureCard::encounter(Character* character, Game* game)
{
  //Demo: just print card's title for now
  game->getUI()->announce("You have encountered the " + this->title() + "!");
  return true;
}

EnemyCard::EnemyCard(unsigned char number) : AdventureCard(number) {}
string EnemyCard::type() { return this->_type; }
void EnemyCard::type(string type) { this->_type = type; }

ObjectCard::ObjectCard(unsigned char number) : AdventureCard(number) {}
string ObjectCard::type() { return this->_type; }
void ObjectCard::type(string type) { this->_type = type; }
bool ObjectCard::encounter(Character* character, Game* game)
{
  unsigned int cap = character->remainingCapacity();
  if (cap <= 0) {
    game->getUI()->announce("You find a " + this->title() + " lying on the ground, but you cannot carry any more items.");
    const vector<ObjectCard*> items = character->inventory();
    string* options = new string[items.size()+1];
    for (unsigned int i=0; i < items.size(); i++) {
      options[i] = items[i]->title();
    }
    options[items.size()] = "Don't pick up the " + this->title();
    unsigned int choice = game->getUI()->prompt("Drop an another item to pick up the " + this->title() + "?", options, items.size()+1);
    delete[] options;
    if (choice == items.size()) return false; //Don't pick up, leave as-is
    character->drop(items[choice]);
    character->pickup(this);
    return true;
  }
  else {
    game->getUI()->announce("You find a " + this->title() + " lying on the ground. You pick it up.");
    character->pickup(this);
    return true;
  }
}

unsigned int EnemyCard::strength() const { return 0; }
unsigned int EnemyCard::craft() const { return 0; }
bool EnemyCard::encounter(Character* character, Game* game)
{
  game->getUI()->announce("You have encountered a " + this->title() + "!");
  Battle * battle = new Battle();
  int results = battle->cardFight(character, this, game);
  if (results == 1) {
    //Player won! Card is added to trophies and removed from the tile.
    character->addTrophy(this);
    return true;
  }
  else {
    //Stand-off or player has lost. Do not remove card from the tile.
    return false;
  }
}

StrangerCard::StrangerCard(unsigned char number) : AdventureCard(number) {}
FollowerCard::FollowerCard(unsigned char number) : AdventureCard(number) {}
PlaceCard::PlaceCard(unsigned char number) : AdventureCard(number) {}
EventCard::EventCard(unsigned char number) : AdventureCard(number) {}
SpellCard::SpellCard() : AdventureCard(0) {}

SwordCard::SwordCard() : ObjectCard(5) {}
string SwordCard::title() { return "Sword"; }

BagOfGoldCard::BagOfGoldCard() : ObjectCard(5) {}
string BagOfGoldCard::title() { return "Bag of Gold"; }
bool BagOfGoldCard::encounter(Character* character, Game* game)
{
  game->getUI()->announce("You find a bag of gold lying on the ground. There are two gold coins inside.");
  character->setGold(character->gold() + 2);
  game->discardAdventureCard(this);
  return true;
}

TalismanCard::TalismanCard() : ObjectCard(5) {}
string TalismanCard::title() { return "Talisman"; }
WaterBottleCard::WaterBottleCard() : ObjectCard(5) {}
string WaterBottleCard::title() { return "Water Bottle"; }
ShieldCard::ShieldCard() : ObjectCard(5) {}
string ShieldCard::title() { return "Shield"; }
AxeCard::AxeCard() : ObjectCard(5) {}
string AxeCard::title() { return "Axe"; }
RaftCard::RaftCard() : ObjectCard(5) {}
string RaftCard::title() { return "Raft"; }

WitchCard::WitchCard() : StrangerCard(4) {}
string WitchCard::title() { return "Witch"; }
HealerCard::HealerCard() : StrangerCard(4) {}
string HealerCard::title() { return "Healer"; }

PrincessCard::PrincessCard() : FollowerCard(5) {}
string PrincessCard::title() { return "Princess"; }
GuideCard::GuideCard() : FollowerCard(5) {}
string GuideCard::title() { return "Guide"; }

MarshCard::MarshCard() : PlaceCard(6) {}
string MarshCard::title() { return "Marsh"; }
ShrineCard::ShrineCard() : PlaceCard(6) {}
string ShrineCard::title() { return "Shrine"; }

BlizzardCard::BlizzardCard() : EventCard(1) {}
string BlizzardCard::title() { return "Blizzard"; }
MarketDayCard::MarketDayCard() : EventCard(1) {}
string MarketDayCard::title() { return "Market Day"; }

WolfCard::WolfCard() : EnemyCard(2) {}
string WolfCard::title() { return "Wolf"; }
unsigned int WolfCard::strength() const { return 2; }
WildBoarCard::WildBoarCard() : EnemyCard(2) {}
string WildBoarCard::title() { return "Wild Boar"; }
unsigned int WildBoarCard::strength() const { return 1; }
BearCard::BearCard() : EnemyCard(2) {}
string BearCard::title() { return "Bear"; }
unsigned int BearCard::strength() const { return 3; }
SpiritCard::SpiritCard() : EnemyCard(1) {}
string SpiritCard::title() { return "Spirit"; }
unsigned int SpiritCard::craft() const { return 4; }
SentinelCard::SentinelCard() : EnemyCard(1) {}
string SentinelCard::title() { return "Sentinel"; }
unsigned int SentinelCard::strength() const { return 9; }

string CounterSpellCard::title() { return "CounterSpell"; }
string DestroyMagicCard::title() { return "DestroyMagic"; }
string HealingCard::title() { return "Healing"; }
string InvisibilityCard::title() { return "Invisibility"; }
string ImmobilityCard::title() { return "Immobility"; }
string PreservationCard::title() { return "Preservation"; }
