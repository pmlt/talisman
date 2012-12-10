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
bool FollowerCard::encounter(Character* character, Game* game) {
  game->getUI()->announce("You find the " + this->title() + " wandering around. They have decided to follow you.");
  character->addFollower(this);
  return true; //Yes, remove card from tile
}
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
bool WitchCard::encounter(Character* character, Game* game)
{
  game->getUI()->announce("You find a witch lurking here.");
  unsigned int roll = game->roll();
  if (roll == 1) {
    game->getUI()->announce("She turns you into a toad!");
    character->transformIntoToad();
  }
  else if (roll == 2) {
    game->getUI()->announce("She beats you with her cane!  You lose a life.");
    game->loseLife(character, 1);
  }
  else if (roll == 3) {
    game->getUI()->announce("She casts a spell and gives you strength!");
    character->incrementStrength();
  }
  else if (roll == 4) {
    game->getUI()->announce("She casts a spell and gives you craft!");
    character->incrementCraft();
  }
  else if (roll == 5) {
    game->getUI()->announce("She is feeling generous; you gain the CounterSpell spell!");
    character->pickup(new CounterSpellCard());
  }
  else if (roll == 6) {
    game->getUI()->announce("She predicts your fate; your fate is replenished!");
    if (character->fateLost() > 0) {
      character->setFate(character->fate() + character->fateLost());
    }
  }
  return false; //She is ALWAYS there!
}
HealerCard::HealerCard() : StrangerCard(4) {}
string HealerCard::title() { return "Healer"; }
bool HealerCard::encounter(Character* character, Game* game) {
  game->getUI()->announce("A Healer has made his home here.");
  if (character->lifeLost() > 0) {
    int lifegained = min(character->lifeLost(), 2);
    character->setLife(character->life() + lifegained);
    game->getUI()->announce("He heals some of your wounds for free.");
  }
  else {
    game->getUI()->announce("You do not require his help.");
  }
  return false; //He is ALWAYS here!
}

PrincessCard::PrincessCard() : FollowerCard(5) {}
string PrincessCard::title() { return "Princess"; }
GuideCard::GuideCard() : FollowerCard(5) {}
string GuideCard::title() { return "Guide"; }

MarshCard::MarshCard() : PlaceCard(6) {}
string MarshCard::title() { return "Marsh"; }
bool MarshCard::encounter(Character* character, Game* game)
{
  if (character->strength() >= 5) {
    game->getUI()->announce("You find a marsh here. Your extraordinary strength helps you wade through the mud.");
  }
  else {
    game->getUI()->announce("You find a marsh here; you will spend the next turn wading through the mud!");
  }
  return false;
}
ShrineCard::ShrineCard() : PlaceCard(6) {}
string ShrineCard::title() { return "Shrine"; }
bool ShrineCard::encounter(Character* character, Game* game)
{
  game->getUI()->announce("You find a shrine here. You pray for a little bit.");
  unsigned int roll = game->roll();
  if (roll == 2) {
    character->setFate(character->fate()+1);
    game->getUI()->announce("You gain 1 fate!");
  }
  else if (roll == 3) {
    character->setGold(character->gold()+1);
    game->getUI()->announce("You gain 1 gold!");
  }
  else if (roll == 4) {
    game->getUI()->announce("You gain the Destroy Magic spell!");
    character->pickup(new DestroyMagicCard());
  }
  else if (roll == 5) {
    game->getUI()->announce("You gain 1 life!");
    character->setLife(character->life() + 1);
  }
  return false;
}

BlizzardCard::BlizzardCard() : EventCard(1) {}
string BlizzardCard::title() { return "Blizzard"; }
bool BlizzardCard::encounter(Character* character, Game* game)
{
  // XXX implement blizzard!
  game->getUI()->announce("A terrible blizzard sets in... but nothing happens :-)");
  return false;
}
MarketDayCard::MarketDayCard() : EventCard(1) {}
string MarketDayCard::title() { return "Market Day"; }
bool MarketDayCard::encounter(Character* character, Game* game)
{
  if (character->remainingCapacity() <= 0) {
    game->getUI()->announce("You find a market, but you are already fully loaded so you keep on going.");
    return false;
  }
  string options[6] = {
    "Sword: 1G",
    "Axe: 1G",
    "Water Bottle: 1G",
    "Shield: 2G",
    "Raft: 3G"
  };
  unsigned int choice = game->getUI()->prompt("You find a market here. The items on sale are:", options, 5);
  unsigned int cost = 1;
  ObjectCard* card = NULL;
  if (choice == 0) {
    card = new SwordCard();
  }
  else if (choice == 1) {
    card = new AxeCard();
  }
  else if (choice == 2) {
    card = new WaterBottleCard();
  }
  else if (choice == 3) {
    cost = 2;
    card = new ShieldCard();
  }
  else if (choice == 4) {
    cost = 3;
    card = new RaftCard();
  }
  if (character->gold() < cost) {
    game->getUI()->announce("You don't have enough gold for that!  Sorry!");
  }
  else {
    game->getUI()->announce(card->title() + " purchased.");
    character->pickup(card);
  }
  return false;
}

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
BrigandCard::BrigandCard() : EnemyCard(1) {}
string BrigandCard::title() { return "Brigand"; }
unsigned int BrigandCard::strength() const { return 4; }

string CounterSpellCard::title() { return "CounterSpell"; }
string DestroyMagicCard::title() { return "DestroyMagic"; }
string HealingCard::title() { return "Healing"; }
string InvisibilityCard::title() { return "Invisibility"; }
string ImmobilityCard::title() { return "Immobility"; }
string PreservationCard::title() { return "Preservation"; }
