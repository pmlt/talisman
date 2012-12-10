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
  if (players.size() > 0) {
    string* options = new string[players.size()+1];
    for (unsigned int i=0; i < players.size(); i++) {
      options[i] = "The " + players[i]->name();
    }
    options[players.size()] = this->getTitle();
    unsigned int choice = game->getUI()->prompt("There are other players here! What do you want to encounter?", options, players.size()+1);

    if (choice == players.size()) {
      character->move(this);
      this->encounter(character, game);
    }
    else {
      Character* opponent = players[choice];
      character->move(this);
      Battle battle;
      int result = battle.playerFight(character, opponent, game);
    }
  }
  else {
    //Set the new position
    character->move(this);
    this->encounter(character, game);
  }

  //Redraw
  game->notify();
}

unsigned int DrawCardsTile::numCards() const { return 1; }
void DrawCardsTile::encounter(Character* character, Game* game)
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
}
bool sortCard(AdventureCard* a, AdventureCard* b)
{
  return a->number() < b->number();
}

string VillageTile::getTitle() const { return "Village"; }
void VillageTile::encounter(Character *character, Game* game) {
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
      return;
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
  return;
}

string FieldsTile::getTitle() const { return "Fields"; }

string GraveyardTile::getTitle() const { return "Graveyard"; }
void GraveyardTile::encounter(Character* character, Game* game) {
  if (character->alignment() > 0) {
    game->getUI()->announce("You land on the Graveyard; you lose one life due to your Good alignment...");
    game->loseLife(character, 1);
  }
  else if (character->alignment() == 0) {
    game->getUI()->announce("You land on the Graveyard; you can spend gold to replenish fate.");
    //XXX replenish fate.
  }
  else {
    string options[2] = {
      "I want to pray to the evil spirits.",
      "No, just replenish my Fate."
    };
    unsigned int choice = game->getUI()->prompt("You land on the Graveyard; you can pray if you wish...", options, 2);
    if (choice == 0) {
      unsigned int roll = game->roll();
      if (roll == 5) {
        game->getUI()->announce("You pray and regain one fate.");
        character->setFate(character->fate()+1);
      }
      else if (roll == 6) {
        game->getUI()->announce("You pray and gain the Invisibility spell!");
        SpellCard* card = new InvisibilityCard();
        character->pickup(card);
      }
      else {
        game->getUI()->announce("You pray, but the spirits do not listen...");
      }
    }
    else {
      game->getUI()->announce("You regain one fate...");
      character->setFate(character->fate()+1);
    }
  }
}

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
      SentinelCard sentinel;
      Battle battle;
      int results = battle.cardFight(character, &sentinel, game);
      if (results == 1) {
        game->getUI()->announce("You emerge victorious and cross into the middle region...");
        MapTile* dest = game->getBoard()->find("Hills (Sentinel)");
        if (dest != NULL) {
          character->move(dest);
          game->notify();
          return; //Do NOT continue
        }
      }
      else if (results == 0) {
        game->getUI()->announce("After a great battle, no victor emerges. Too tired to go on, you remain on the Sentinel space.");
        character->move(this);
        game->notify();
        return;
      }
      else {
        game->getUI()->announce("After a great battle, the Sentinel gets the better of you. You lose a life, and are too tired to move on.");
        character->move(this);
        game->notify();
        return;
      }
    }
  }
  //Continue normally
  MapTile::step(character, game, movement, direction);
}

string HillsTile::getTitle() const { return "Hills"; }

string SentinelHillsTile::getTitle() const { return "Hills (Sentinel)"; }

void SentinelHillsTile::step(Character *character, Game* game, unsigned int movement, unsigned int direction) {
  //Ask user to move to inner region
  string options[2] = {
    "Yes, cross into the outer region.",
    "No, continue my way in the middle region."
  };
  unsigned char choice = game->getUI()->prompt("You are passing the Hills near the Sentinel space and you still have movement left. Do you want to cross over into the outer region?", options, 2);
  if (choice == 0) {
    MapTile* dest = game->getBoard()->find("Sentinel");
    if (dest != NULL) {
      dest->land(character, game);
      return; //Do NOT continue
    }
  }
  //Continue normally
  MapTile::step(character, game, movement, direction);
}

string ChapelTile::getTitle() const { return "Chapel"; }
void ChapelTile::encounter(Character* character, Game* game) {
  if (character->alignment() < 0) {
    game->getUI()->announce("You land on the Chapel; you lose one life due to your Evil alignment...");
    game->loseLife(character, 1);
  }
  else if (character->alignment() == 0) {
    game->getUI()->announce("You land on the Chapel; you spend gold to replenish life.");
    int life_to_replenish = min(character->lifeLost(), character->gold());
    character->setLife(character->life() + life_to_replenish);
    character->setGold(character->gold() - life_to_replenish);
  }
  else {
    string options[2] = {
      "I want to pray to the good spirits.",
      "No, just replenish my life for free."
    };
    unsigned int choice = game->getUI()->prompt("You land on the Chapel; you can pray if you wish...", options, 2);
    if (choice == 0) {
      unsigned int roll = game->roll();
      if (roll == 5) {
        game->getUI()->announce("You pray and regain one life.");
        character->setLife(character->life()+1);
      }
      else if (roll == 6) {
        game->getUI()->announce("You pray and gain the Invisibility spell!");
        SpellCard* card = new InvisibilityCard();
        character->pickup(card);
      }
      else {
        game->getUI()->announce("You pray, but the spirits do not listen...");
      }
    }
    else {
      game->getUI()->announce("You regain all your life...");
      character->setLife(character->life()+character->lifeLost());
    }
  }
}

string CragsTile::getTitle() const { return "Crags"; }
void CragsTile::encounter(Character* character, Game* game) {
  game->getUI()->announce("You arrive at the Crags...");
  unsigned int roll = game->roll();
  if (roll == 1) {
    game->getUI()->announce("You are attacked by an evil Spirit!");
    SpiritCard spirit;
    spirit.encounter(character, game);
  }
  else if (roll == 2 || roll == 3) {
    game->getUI()->announce("You are lost...");
  }
  else if (roll == 4 || roll == 5) {
    game->getUI()->announce("You are safe, no effect.");
  }
  else {
    game->getUI()->announce("A Barbarian leads you out; you gain one strength!");
    character->incrementStrength();
  }
}

string PlainsTile::getTitle() const { return "Plains"; }

string CityTile::getTitle() const { return "City"; }
void CityTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string TavernTile::getTitle() const { return "Tavern"; }
void TavernTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string RuinsTile::getTitle() const { return "Ruins"; }
unsigned int RuinsTile::numCards() const { return 2; }

string ForestTile::getTitle() const { return "Forest"; }
void ForestTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

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
        return character->move(dest); //Do NOT continue
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
void BlackKnightTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string HiddenValleyTile::getTitle() const { return "Hidden Valley"; }
unsigned int HiddenValleyTile::numCards() const { return 3; }

string CursedGladeTile::getTitle() const { return "Cursed Glade"; }

string RunesTile::getTitle() const { return "Runes"; }

string ChasmTile::getTitle() const { return "Chasm"; }
void ChasmTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string WarlocksCaveTile::getTitle() const { return "Warlock's Cave"; }
void WarlocksCaveTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string DesertTile::getTitle() const { return "Desert"; }
void DesertTile::encounter(Character* character, Game* game)
{
  //Check if character has Water Bottle.
  if (character->findObject("Water Bottle") != NULL) {
    game->getUI()->announce("It is scalding hot here, but your Water Bottle helps you endure the heat.");
    return DrawCardsTile::encounter(character, game);
  }
  else {
    game->getUI()->announce("It is scalding hot here!  You lose one life.");
    if (game->loseLife(character, 1)) return DrawCardsTile::encounter(character, game);
  }
}

string OasisTile::getTitle() const { return "Oasis"; }
unsigned int OasisTile::numCards() const { return 2; }

string TempleTile::getTitle() const { return "Temple"; }
void TempleTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string CastleTile::getTitle() const { return "Castle"; }
void CastleTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string PlainsOfPerilTile::getTitle() const { return "Plains of Peril"; }
void PlainsOfPerilTile::encounter(Character* character, Game* game) {
  //Ask user to move to inner region
  string options[2] = {
    "Yes, cross into the middle region.",
    "No, continue my way in the inner region."
  };
  unsigned char choice = game->getUI()->prompt("You have landed in the Plains of Peril. Do you want to cross over into the middle region?", options, 2);
  if (choice == 0) {
    MapTile* dest = game->getBoard()->find("Portal of Power");
    if (dest != NULL) {
      character->move(dest);
    }
  }
}

string MinesTile::getTitle() const { return "Mines"; }
void MinesTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string VampiresTowerTile::getTitle() const { return "Vampire's Tower"; }
void VampiresTowerTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string PitsTile::getTitle() const { return "Pits"; }
void PitsTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string ValleyOfFireTile::getTitle() const { return "Valley of Fire"; }
bool ValleyOfFireTile::hasCrown(Character* character) {
  return playersVyingForControl.size() == 1 && playersVyingForControl[0] == character;
}
void ValleyOfFireTile::start(Character* character, Game* game) {
  auto it = find(playersVyingForControl.begin(), playersVyingForControl.end(), character);
  if (it != playersVyingForControl.end()) {
    //Character is vying for control.
    if (playersVyingForControl.size() > 1) {
      fightOtherPlayers(character, game);
    }
    else {
      castCommand(character, game);
    }
  }
}
void ValleyOfFireTile::encounter(Character* character, Game* game) {
  bool hasTalisman = character->findObject("Talisman") != NULL;
  if (hasTalisman) {
    game->getUI()->announce("You reach the Valley of Fire. Armed with your Talisman, you climb to the Crown of Command.");
    playersVyingForControl.push_back(character);
    if (playersVyingForControl.size() > 1) {
      game->getUI()->announce("At the top, you find other adventurers...");
      fightOtherPlayers(character, game);
    }
    else {
      game->getUI()->announce("You seize the Crown of Command! Now all that is left is to kill the remaining pests...");
      castCommand(character, game);
    }
  }
}
void ValleyOfFireTile::fightOtherPlayers(Character* character, Game* game) {
  remove(playersVyingForControl.begin(), playersVyingForControl.end(), character);
  string* options = new string[playersVyingForControl.size()];
  for (int i=0; i < playersVyingForControl.size(); i++) {
    options[i] = "The " + playersVyingForControl[i]->name();
  }
  unsigned int choice = game->getUI()->prompt("You must fight! Which player do you want to fight?", options, playersVyingForControl.size());
  delete[] options;
  Character* opponent = playersVyingForControl[choice];
  playersVyingForControl.push_back(character);

  Battle battle;
  battle.playerFight(character, opponent, game);
  auto players = game->getPlayers();
  if (players.end() == find(players.begin(), players.end(), opponent)) {
    //Opponent was killed!
    remove(playersVyingForControl.begin(), playersVyingForControl.end(), opponent);
  }
  if (players.end() == find(players.begin(), players.end(), character)) {
    //Opponent was killed!
    remove(playersVyingForControl.begin(), playersVyingForControl.end(), character);
  }
}
void ValleyOfFireTile::castCommand(Character* character, Game* game) {
  game->getUI()->announce("Alone at the top of the Valley of Fire, you rain death on all your opponents...");
  unsigned int roll = game->roll();
  if (roll >= 4) {
    // All other players lose 1 life.
    auto players = game->getPlayers();
    for (unsigned int i=0; i < players.size(); i++) {
      Character* p = players[i];
      if (p == character) continue;
      game->loseLife(p, 1);
    }
  }
  else {
    game->getUI()->announce("The spell misfires and has no effect!");
  }
}

string WerewolfDenTile::getTitle() const { return "Werewolf Den"; }
void WerewolfDenTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string DeathTile::getTitle() const { return "Death"; }
void DeathTile::encounter(Character* character, Game* game) {
  // XXX TODO
}

string CryptTile::getTitle() const { return "Crypt"; }
void CryptTile::encounter(Character* character, Game* game) {
  // XXX TODO
}
