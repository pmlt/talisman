#pragma once

#include "AdventureCard.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class Character;
class Game;

/*
  Class: MapTile
  Represents a location on the board. Dummy class to help model Character for now.
*/
class MapTile
{
public:
  MapTile();
  virtual ~MapTile(void);

  virtual string getTitle() const = 0;

  void addPlayer(Character *player);
  void removePlayer(Character *player);
  unsigned int getPlayerCount() const;
  Character* getPlayer(unsigned int index) const;

  
  void setNeighbors(MapTile* cw, MapTile* ccw);

  unsigned char rollMovement(Character *character, Game *game);

  /*
    Method: start
    Start a character's turn on this tile.
  */
  virtual void start(Character* character, Game* game);
  /*
    Method: leave
    Callback for when a character leaves the tile he started in on this turn.
  */
  virtual void leave(Character* character, Game* game, unsigned int movement, unsigned int direction);
  /*
    Method: step
    Callback for when a character steps on a tile on his way to another one.
  */
  virtual void step(Character* character, Game* game, unsigned int movement_left, unsigned int direction);
  
  /*
    Method: land
    Callback for when a character lands on a tile (his final destination).
  */
  void land (Character* character, Game* game);
  
  /*
    Method: encounter
    Callback for when a character decides to encounter a tile
  */
  virtual void encounter(Character *character, Game* game) = 0;

protected:
  MapTile* cw;
  MapTile* ccw;

  vector<Character*> players;
  vector<AdventureCard*> cards;
};

class DrawCardsTile : public MapTile
{
public:
  virtual void encounter(Character *character, Game* game);
  virtual unsigned int numCards() const;
};
bool sortCard(AdventureCard* a, AdventureCard* b);

/*
  Class: VillageTile
  Visit the Blacksmith, Healer, or Mystic
  Blacksmith: Helmet (2G), Sword (2G), Axe (3G), Shield (3G), Armour (4G)
  Healer: Heal up to your life value at the cost of one gold each
  Mystic (roll 1 die): 
    1 - Become evil
    2 - Ignored
    3 - Ignored
    4 - Become good; 
    5 - Gain 1 craft
    6 - Gain 1 spell
*/
class VillageTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: FieldsTile
  Draw one card.
  Do not draw a card if there is already one in this space.
*/
class FieldsTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: GraveyardTile
  Based on alignment.
  Good    - Lose one life.
  Neutral - Replenish fate up to your fate value at the cost of
            one gold each.
  Evil    - Either replenish fate up to your fate value for free, 
            or pray by rolling one die.

  Pray:
    1 to 4 - Ignored
    5      - Gain 1 fate
    6      - Gain 1 spell
*/
class GraveyardTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: WoodsTile
  Draw one card.
  Do not draw a card if there is already one in this space.
*/
class WoodsTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: SentinelTile
  Draw one card. 
  Do not draw a card if there is already one in this space. 
  If you are crossing the middle region, do not draw a card. Instead, you
  must first defeat the Sentinel with Strength 9. Do not fight the Sentinel
  when crossing from the Middle Region.
*/
class SentinelTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual void step(Character *character, Game* game, unsigned int movement, unsigned int direction);
};

/*
  Class: HillsTile
  Draw one card.
  Do not draw a card if there is already one in this space.
*/
class HillsTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: SentinelHillsTile
  Draw one card.
  Do not draw a card if there is already one in this space.
  This is the destination space for the Sentinel tile.
*/
class SentinelHillsTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: ChapelTile
  Based on alignment.
  Evil    - Lose one life.
  Neutral - Heal up to your life value at the cost of one gold each.
  Good    - Either heal up to your life value for free, 
            or pray by rolling one die.

  Pray:
    1 to 4 - Ignored
    5      - Gain 1 life
    6      - Gain 1 spell
*/
class ChapelTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: CragsTile
  Roll 1 die.
  1      - Attacked by a Spirit with Craft 4.
  2 to 3 - Lost; lose your next turn
  4 to 5 - Safe, no effect
  6      - A barbarian leads you out; gain 1 strength.
*/
class CragsTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: PlainsTile
  Draw one card.
  Do not draw a card if there is already one in this space.
*/
class PlainsTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: CityTile
  Visit the Doctor, Alchemist, or Enchantress

  Doctor:
    Heal up to two lives at the cost of one gold each.

  Alchemist:
    Discard any number of Objects you have and gain one gold for each.

  Enchantress (roll 1 die):
    1 - Turned into a toad
    2 - Lose 1 strength
    3 - Lose 1 craft
    4 - Gain 1 craft
    5 - Gain 1 strength
    6 - Gain 1 spell
*/
class CityTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: Tavern
  Roll 1 die.
  1 - Get drunk and collapse in a corner; miss 1 turn.
  2 - Get tipsy and fight a farmer with strength 3.
  3 - Gamble and lose 1 gold
  4 - Gamble and win 1 gold
  5 - A wizard offers to teleport you to any other space in this Region as your next move.
  6 - A boatman offers to ferry you to the Temple as your next move.
*/
class TavernTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: RuinsTile
  Draw 2 cards.
  If there are any cards already in this space, draw only enough to take the total to two cards.
*/
class RuinsTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual unsigned int numCards() const;
};

/*
  Class: ForestTile
  Roll 1 die.
  1      - Attacked by a brigand with Strength 4.
  2 to 3 - Lost; lose your next turn.
  4 to 5 - Safe.
  6      - A ranger guides you out; gain 1 craft.
*/
class ForestTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: PortalOfPowerTile
  Draw 1 card.
  Do not draw a card if there is already one in this space. If you are crossing to the 
  Plains of Peril, do not draw a card. Instead, you must first use Craft to pick the lock
  or Strength to force it. Choose which ability you are using and roll two dice.
*/
class PortalOfPowerTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual void step(Character *character, Game* game, unsigned int movement, unsigned int direction);
};

/*
  Class: BlackKnightTile
  Suffer one penalty.
  Either pay one gold (discard) or lose one life.
*/
class BlackKnightTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: HiddenValleyTile
  Draw 3 cards
  If there are any cards already in this space, draw only enough to take the total to three cards.
*/
class HiddenValleyTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual unsigned int numCards() const;
};

/*
  Class: CursedGladeTile
  Draw 1 card.
  Do not draw a card if there is already one in this space. Strength and Craft derived from Objects
  and Magic Objects do not count on this space, nor may you use Magic Objects or cast Spells.
*/
class CursedGladeTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: RunesTile
  Draw 1 card.
  Do not draw a card if there is already one in this space. Any creature that you fight here add 2
  to their attack rolls.
*/
class RunesTile : public DrawCardsTile
{
  virtual string getTitle() const;
};

/*
  Class: ChasmTile
  Roll 1 die for yourself, and one for each of your Followers. If a 1 or a 2 is rolled for yourself, 
  lose 1 life. If a 1 or a 2 is rolled for a Follower, it is killed.
*/
class ChasmTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: WarlocksCaveTile
  You may roll 1 die to accept a quest.
  When you complete the quest, the Warlock immediately teleports you back here and gives
  you a Talisman, if available, as your reward.
  1 - Take 1 life from another character.
  2 - Kill 1 enemy.
  3 - Deliver (discard) 1 Follower.
  4 - Deliver (discard) 1 Magic Object.
  5 - Deliver (discard) 3 gold.
  6 - Deliver (discard) 2 gold.
*/
class WarlocksCaveTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: DesertTile
  Lose 1 life and then draw 1 card.
  Do not draw a card if there is already one in this space.
*/
class DesertTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual void encounter(Character* character, Game* game);
};

/*
  Class: OasisTile
  Draw 2 cards.
  If there are any cards already in this space, 
  draw only enough to take the total to two cards.
*/
class OasisTile : public DrawCardsTile
{
  virtual string getTitle() const;
  virtual unsigned int numCards() const;
};

/*
  Class: TempleTile
  Pray: Roll 2 dice.
  2  - Lose 2 lives.
  3  - Lose 1 life.
  4  - Lose 1 Follower.
  5  - Enslaved: stay here until you roll a 4, 5, or 6 for your move.
  6  - Gain 1 Strength.
  7  - Gain 1 Craft.
  8  - Gain 1 Spell.
  9  - Gain 1 Spell.
  10 - Gain a Talisman.
  11 - Gain 2 fate.
  12 - Gain 2 lives.
*/
class TempleTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: CastleTile
  Royal Doctor.
  Heal up to your life value at the cost of one gold each. If you have the Prince or Princess, 
  heal up to two lives for free.
*/
class CastleTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: PlainsOfPerilTile
  Stop here.
  Move only one space per turn.
*/
class PlainsOfPerilTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: MinesTile
  Roll 3 dice.
  Subtract your Craft from the total and move directly to:
  0  - Mines
  1  - Plains of Peril
  2  - Portal of Power
  3  - Portal of Power
  4  - Warlock's Cave
  5  - Warlock's Cave
  6+ - Tavern
*/
class MinesTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: VampiresTowerTile
  Suffer blood loss.
  Roll one die to determine how many lives the Vampire takes. You may discard any number of Followers
  to avoid this loss of life. Each Follower you discard prevents the loss of one life.
  1 to 2 - Lose 1 life.
  3 to 4 - Lose 2 lives.
  5 to 6 - Lose 3 lives.
*/
class VampiresTowerTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: PitsTile
  Fight the Pitfiends.
  Roll one die and fight that many Pitfiends with Strength 4 each one-by-one until either of you are defeated
  or you defeat all of the Pitfiends. You may move on the turn after all Pitfiends are defeated.
*/
class PitsTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: ValleyOfFireTile
  You must have a Talisman to enter.
  You can only enter if you have a Talisman. If you do not have one, you must turn back. The Crown of Command 
  can only be reached from this space.
*/
class ValleyOfFireTile : public MapTile
{
public:
  virtual string getTitle() const;
  virtual void start(Character* character, Game* game);
  virtual void encounter(Character *character, Game* game);

  bool hasCrown(Character* character);

  void fightOtherPlayers(Character* character, Game* game);
  void castCommand(Character* character, Game* game);
private:
  vector<Character*> playersVyingForControl;
};

/*
  Class: WerewolfDenTile
  Fight the Werewolf.
  Roll two dice for the Werewolf's Strength, then fight it. If you lose, lose one life and you fight the
  same Werewolf again on your next turn. You cannot move on until you have defeated the Werewolf.
*/
class WerewolfDenTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: DeathTile
  Dice with Death.
  Roll 2 dice for yourself and two dice for Death. If the scores are equal: Dice with Death again on your next turn.
  If your score is lower: Lose one life and Dice with Death again on your next turn. If your score is higher: you may
  move on your next turn.
*/
class DeathTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};

/*
  Class: CryptTile
  Roll 3 dice.
  Subtract your Strength from the total and move directly to:
  0      - Crypt
  1      - Plains of Peril
  2 to 3 - Portal of Power
  4 to 5 - Warlock's Cave
  6+     - City
*/
class CryptTile : public MapTile
{
  virtual string getTitle() const;
  virtual void encounter(Character *character, Game* game);
};
