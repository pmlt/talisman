#pragma once
#include <vector>
#include <string.h>
using namespace std;

class Character;
class Game;

class AdventureCard
{
public:
  AdventureCard(unsigned char number);
  virtual ~AdventureCard(void);

  static void createDeckFromFile(std::string deck_file, std::vector<AdventureCard*> &deck, bool set_purchase_flag);

  virtual string title() = 0;
  bool isPurchaseCard() const;
  void setPurchaseCard(bool isPurchase);
  unsigned char number();
  void number(unsigned char number);

  virtual bool encounter(Character* character, Game* game);

private:
  unsigned char _number; //encounter number
  bool _isPurchaseCard;
};

class EnemyCard : public AdventureCard
{
public:
  EnemyCard(unsigned char number);
  string type();
  void type(string type);
  virtual bool encounter(Character* character, Game* game);
  virtual unsigned int strength() const;
  virtual unsigned int craft() const;
private:
  string _type;
};

class ObjectCard : public AdventureCard
{
public:
  ObjectCard(unsigned char number);
  string type();
  void type(string type);
  virtual bool encounter(Character* character, Game* game);
private:
  string _type;
};

class StrangerCard : public AdventureCard
{
public:
  StrangerCard(unsigned char number);
};

class FollowerCard : public AdventureCard
{
public:
  FollowerCard(unsigned char number);
};

class EventCard : public AdventureCard
{
public:
  EventCard(unsigned char number);
};

class PlaceCard : public AdventureCard
{
public:
  PlaceCard(unsigned char number);
};

class SpellCard : public AdventureCard
{
public:
  SpellCard();
};

/**** Actual cards ****/

class SwordCard : public ObjectCard
{
public:
  SwordCard();
  virtual string title();
};

class BagOfGoldCard : public ObjectCard
{
public:
  BagOfGoldCard();
  virtual string title();
  virtual bool encounter(Character* character, Game* game);
};

class WaterBottleCard : public ObjectCard
{
public:
  WaterBottleCard();
  virtual string title();
};

class ShieldCard : public ObjectCard
{
public:
  ShieldCard();
  virtual string title();
};

class AxeCard : public ObjectCard
{
public:
  AxeCard();
  virtual string title();
};

class RaftCard : public ObjectCard
{
public:
  RaftCard();
  virtual string title();
};

class TalismanCard : public ObjectCard
{
public:
  TalismanCard();
  virtual string title();
};

class WitchCard : public StrangerCard
{
public:
  WitchCard();
  virtual string title();
};

class HealerCard : public StrangerCard
{
public:
  HealerCard();
  virtual string title();
};

class PrincessCard : public FollowerCard
{
public:
  PrincessCard();
  virtual string title();
};

class GuideCard : public FollowerCard
{
public:
  GuideCard();
  virtual string title();
};

class MarshCard : public PlaceCard
{
public:
  MarshCard();
  virtual string title();
};

class ShrineCard : public PlaceCard
{
public:
  ShrineCard();
  virtual string title();
};

class BlizzardCard : public EventCard
{
public:
  BlizzardCard();
  virtual string title();
};

class MarketDayCard : public EventCard
{
public:
  MarketDayCard();
  virtual string title();
};

class WolfCard : public EnemyCard
{
public:
  WolfCard();
  virtual string title();
  virtual unsigned int strength() const;
};

class WildBoarCard : public EnemyCard
{
public:
  WildBoarCard();
  virtual string title();
  virtual unsigned int strength() const;
};

class BearCard : public EnemyCard
{
public:
  BearCard();
  virtual string title();
  virtual unsigned int strength() const;
};

class SentinelCard : public EnemyCard
{
public:
  SentinelCard();
  virtual string title();
  virtual unsigned int strength() const;
};

class SpiritCard : public EnemyCard
{
public:
  SpiritCard();
  virtual string title();
  virtual unsigned int craft() const;
};

class CounterSpellCard : public SpellCard
{
public:
  virtual string title();
};

class DestroyMagicCard : public SpellCard
{
public:
  virtual string title();
};

class HealingCard : public SpellCard
{
public:
  virtual string title();
};

class InvisibilityCard : public SpellCard
{
public:
  virtual string title();
};

class ImmobilityCard : public SpellCard
{
public:
  virtual string title();
};

class PreservationCard : public SpellCard
{
public:
  virtual string title();
};

