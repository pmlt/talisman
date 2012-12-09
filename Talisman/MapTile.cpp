#include "StdAfx.h"
#include "MapTile.h"
#include "Character.h"
#include "Game.h"
#include "CharacterCommand.h"
#include "Battle.h"
#include <sstream>
#include <algorithm>

using namespace std;

MapTile::MapTile() :
  cw(NULL),ccw(NULL),players()
{
}


MapTile::~MapTile(void)
{
}

Character* MapTile::getPlayer(unsigned int index) const { return this->players[index]; }
unsigned int MapTile::getPlayerCount() const { return players.size(); }
void MapTile::addPlayer(Character* player) { this->players.push_back(player); }
void MapTile::removePlayer(Character* player) {
  for (auto it = players.begin(); it != players.end(); it++) {
    if ((*it) == player) {
      players.erase(it);
      break;
    }
  }
}

void MapTile::setNeighbors(MapTile* cw, MapTile* ccw)
{
  this->cw = cw;
  this->ccw = ccw;
}

unsigned char MapTile::rollMovement(Character *character, Game *game)
{
  //Random number between 1 and 6
  return game->roll();
}

void MapTile::start(Character *character, Game* game)
{
  //Redraw
  game->notify();

  //Roll how much for movement
  unsigned char movement = this->rollMovement(character, game);
  stringstream smov;
  smov << (int)movement;

  //Prompt for which direction.
  string opts[2] = {
    "Clockwise",
    "Counter-clockwise"
  };
  unsigned int direction = game->getUI()->prompt("You rolled a " + smov.str() + "! Which direction do you want to go", opts, 2);

  //Go!
  this->leave(character, game, movement, direction);
}

void MapTile::leave(Character* character, Game* game, unsigned int movement, unsigned int direction)
{
  //Simply move out by default
  this->step(character, game, movement, direction);
}

void MapTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction)
{
  if (movement == 0) {
    this->land(character, game);
    return;
  }
  if (direction == 0) {
    //Clockwise
    this->cw->step(character, game, movement - 1, direction);
  }
  else {
    //Counter-clockwise
    this->ccw->step(character, game, movement - 1, direction);
  }
}

void MapTile::land(Character* character, Game* game)
{
  //Set the new position
  character->move(this);
  //Redraw
  game->notify();
}

unsigned int DrawCardsTile::numCards() const { return 1; }
void DrawCardsTile::land(Character* character, Game* game)
{
  game->getUI()->announce("You have arrived at the " + this->getTitle() + "...");
  //Draw cards
  while (cards.size() < numCards()) {
    AdventureCard *card = game->drawAdventureCard();
    if (card == NULL) {
      //No more cards in deck!
      break;
    }
    cards.push_back(card);
  }
  sort(cards.begin(), cards.end(), sortCard);
  for (unsigned int i=0; i < cards.size(); i++) {
    //Encounter the card!
    AdventureCard* card = cards[i];
    bool remove = card->encounter(character, game);
    if (remove) {
      cards.erase(cards.begin()+i);
      i--;
    }
  }
  return MapTile::land(character, game);
}
bool sortCard(AdventureCard* a, AdventureCard* b)
{
  return a->number() < b->number();
}

string VillageTile::getTitle() const { return "Village"; }
void VillageTile::land(Character *character, Game* game) {
  GameUI* ui = game->getUI();
  string opts[4] = {
    "Do nothing.",
    "Blacksmith: Helmet (2G), Sword (2G), Axe (3G), Shield (3G), Armour (4G)",
    "Healer: Heal up to your life value at the cost of one gold each)",
    "Mystic: roll 1 die"
  };
  unsigned int visit = ui->prompt("You have arrived at the village. You can visit one of the following: ", opts, 4);
  if (visit == 0) {
    //Do nothing
  }
  else if (visit == 1) {
    unsigned int gold = character->gold();
    unsigned int cap = character->remainingCapacity();
    if (cap <= 0) {
      ui->announce("Your inventory is full!  You cannot buy anything.");
      return MapTile::land(character, game);
    }
    string items[5] = {
      "Helmet (2G)", 
      "Sword (2G)", 
      "Axe (3G)", 
      "Shield (3G)", 
      "Armour (4G)"
    };
    unsigned int item_choice = ui->prompt("Hello there!  What do you want to buy? ", items, 5);
    if (item_choice == 1) {
      if (gold < 2) {
        ui->announce("You do not have enough gold to buy the Sword!");
      }
      SwordCard* sword = new SwordCard();
      character->pickup(sword);
      ui->announce("Nice doin' businedss witcha!");
    }
    else {
      ui->announce("Sorry, that item is not yet implemented...");
    }
  }
  else if (visit == 2) {
    unsigned int life_to_recover = min(character->gold(), character->lifeLost());
    character->setLife(character->life() + life_to_recover);
    character->setGold(character->gold()-life_to_recover);
    ui->announce("The Healer has healed you!");
  }
  else {
    unsigned int roll = game->roll();
    SpellCard *spell;
    string spells[6] = {
      "CounterSpell",
      "Destroy Magic",
      "Healing",
      "Invisibility",
      "Immobility",
      "Preservation"
    };
    unsigned int spellchoice;
    switch (roll) {
    case 1: 
      character->setAlignment(-1);
      ui->announce("The Mystic has made you Evil!");
      break;
    case 4: 
      character->setAlignment(1);
      ui->announce("The Mystic has made you Good!");
      break;
    case 5:
      character->incrementCraft();
      ui->announce("The Mystic gave you 1 Craft!");
      break;
    case 6:
      spellchoice = ui->prompt("The Mystic gives you a spell! Choose from the following:", spells, 6);
      if (spellchoice == 0) {
        spell = new CounterSpellCard();
      } else if (spellchoice == 1) {
        spell = new DestroyMagicCard();
      } else if (spellchoice == 2) {
        spell = new HealingCard();
      } else if (spellchoice == 3) {
        spell = new InvisibilityCard();
      } else if (spellchoice == 4) {
        spell = new ImmobilityCard();
      } else if (spellchoice == 5) {
        spell = new PreservationCard();
      }
      character->pickup(spell);
      ui->announce("You now have that spell in your spellbook!");
      break;
    default:
      ui->announce("Nothing happens.");
    }
  }
  return MapTile::land(character, game);
}

string FieldsTile::getTitle() const { return "Fields"; }

string GraveyardTile::getTitle() const { return "Graveyard"; }

string WoodsTile::getTitle() const { return "Woods"; }

string SentinelTile::getTitle() const { return "Sentinel"; }

void SentinelTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction)
{
  if (movement > 0) {
    //Ask user to move to inner region
    string options[2] = {
      "Yes, cross into the middle region.",
      "No, continue my way in the outer region."
    };
    unsigned char choice = game->getUI()->prompt("You are passing the Sentinel space and you still have movement left. Do you want to cross the Sentinel into the middle region?", options, 2);
    if (choice == 0) {
      //Cross!
      MapTile* dest = game->getBoard()->find("Hills (Sentinel)");
      if (dest != NULL) {
        dest->land(character, game);
        return; //Do NOT continue
      }
    }
  }
  //Continue normally
  MapTile::step(character, game, movement, direction);
}

string HillsTile::getTitle() const { return "Hills"; }

string SentinelHillsTile::getTitle() const { return "Hills (Sentinel)"; }

string ChapelTile::getTitle() const { return "Chapel"; }

string CragsTile::getTitle() const { return "Crags"; }

string PlainsTile::getTitle() const { return "Plains"; }

string CityTile::getTitle() const { return "City"; }

string TavernTile::getTitle() const { return "Tavern"; }

string RuinsTile::getTitle() const { return "Ruins"; }
unsigned int RuinsTile::numCards() const { return 2; }

string ForestTile::getTitle() const { return "Forest"; }

string PortalOfPowerTile::getTitle() const { return "Portal of Power"; }
void PortalOfPowerTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction)
{
  if (movement > 0) {
    string options[3] = {
      "Yes, attempt to open the Portal of Power by picking the lock (Craft).",
      "Yes, attempt to open the Portal of Power by forcing the lock (Strength).",
      "No, continue my way in the middle region."
    };
    unsigned char choice = game->getUI()->prompt("You are passing the Portal of Power. Do you want to try crossing into the inner region?", options, 3);
    if (choice == 2) {
      //Continue normally.
      return MapTile::step(character, game, movement, direction);
    }
    unsigned int roll_value = game->roll() + game->roll();
    unsigned ability_value = choice == 1 ? character->strength() : character->craft();
    if (roll_value <= ability_value) {
      //Success!
      game->getUI()->announce("You successfully open the Portal of Power...");
      MapTile* dest = game->getBoard()->find("Plains of Peril");
      if (dest != NULL) {
        return dest->land(character, game); //Do NOT continue
      }
    }
    else {
      if (choice == 0) {
        character->decrementCraft();
        game->getUI()->announce("You failed to pick the lock... you lost one craft!");
      }
      else {
        character->decrementStrength();
        game->getUI()->announce("You failed to force the lock... you lost one strength!");
      }
      return this->land(character, game); // Do NOT continue
    }
  }
  //Continue normally
  MapTile::step(character, game, movement, direction);
}

string BlackKnightTile::getTitle() const { return "Black Knight"; }

string HiddenValleyTile::getTitle() const { return "Hidden Valley"; }
unsigned int HiddenValleyTile::numCards() const { return 3; }

string CursedGladeTile::getTitle() const { return "Cursed Glade"; }

string RunesTile::getTitle() const { return "Runes"; }

string ChasmTile::getTitle() const { return "Chasm"; }

string WarlocksCaveTile::getTitle() const { return "Warlock's Cave"; }

string DesertTile::getTitle() const { return "Desert"; }
void DesertTile::land(Character* character, Game* game)
{
  //Check if character has Water Bottle.
  if (character->findObject("Water Bottle") != NULL) {
    game->getUI()->announce("It is scalding hot here, but your Water Bottle helps you endure the heat.");
    return MapTile::land(character, game);
  }
  else {
    game->getUI()->announce("It is scalding hot here!  You lose one life.");
    if (game->loseLife(character, 1)) return MapTile::land(character, game);
  }
}

string OasisTile::getTitle() const { return "Oasis"; }
unsigned int OasisTile::numCards() const { return 2; }

string TempleTile::getTitle() const { return "Temple"; }

string CastleTile::getTitle() const { return "Castle"; }

string PlainsOfPerilTile::getTitle() const { return "Plains of Peril"; }

string MinesTile::getTitle() const { return "Mines"; }

string VampiresTowerTile::getTitle() const { return "Vampire's Tower"; }

string PitsTile::getTitle() const { return "Pits"; }

string ValleyOfFireTile::getTitle() const { return "Valley of Fire"; }

string WerewolfDenTile::getTitle() const { return "Werewolf Den"; }

string DeathTile::getTitle() const { return "Death"; }

string CryptTile::getTitle() const { return "Crypt"; }
