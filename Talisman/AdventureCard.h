#pragma once
#include <vector>
#include <string.h>
using namespace std;

class Character;
class Game;

class AdventureCard
{
public:
  AdventureCard(void);
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
  string type();
  void type(string type);
  virtual bool encounter(Character* character, Game* game);
private:
  string _type;
};

class ObjectCard : public AdventureCard
{
public:
  string type();
  void type(string type);
private:
  string _type;
};

class StrangerCard : public AdventureCard
{
};

class FollowerCard : public AdventureCard
{
};

class EventCard : public AdventureCard
{
};

class PlaceCard : public AdventureCard
{
};

class SpellCard : public AdventureCard
{
};

/**** Actual cards ****/

class SwordCard : public ObjectCard
{
public:
  virtual string title();
};

class BagOfGoldCard : public ObjectCard
{
public:
  virtual string title();
};

class TalismanCard : public ObjectCard
{
public:
  virtual string title();
};

class WitchCard : public StrangerCard
{
public:
  virtual string title();
};

class HealerCard : public StrangerCard
{
public:
  virtual string title();
};

class PrincessCard : public FollowerCard
{
public:
  virtual string title();
};

class GuideCard : public FollowerCard
{
public:
  virtual string title();
};

class MarshCard : public PlaceCard
{
public:
  virtual string title();
};

class ShrineCard : public PlaceCard
{
public:
  virtual string title();
};

class BlizzardCard : public EventCard
{
public:
  virtual string title();
};

class MarketDayCard : public EventCard
{
public:
  virtual string title();
};

class WolfCard : public EnemyCard
{
public:
  virtual string title();
};

class WildBoarCard : public EnemyCard
{
public:
  virtual string title();
};

class BearCard : public EnemyCard
{
public:
  virtual string title();
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

