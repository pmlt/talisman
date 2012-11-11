#pragma once
#include <stack>
#include <string.h>
using namespace std;

class AdventureCard
{
public:
  AdventureCard(void);
  virtual ~AdventureCard(void);

  static void createDeckFromFile(std::string deck_file, std::stack<AdventureCard*> &deck);

  string title();
  void title(string title);
  unsigned char number();
  void number(unsigned char number);

private:
  string _title;
  unsigned char _number; //encounter number
};

class EnemyCard : public AdventureCard
{
public:
  string type();
  void type(string type);
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

/**** Actual cards ****/

class SwordCard : public ObjectCard
{
};

class BagOfGoldCard : public ObjectCard
{
};

class TalismanCard : public ObjectCard
{
};

class WitchCard : public StrangerCard
{
};

class HealerCard : public StrangerCard
{
};

class PrincessCard : public FollowerCard
{
};

class GuideCard : public FollowerCard
{
};

class MarshCard : public PlaceCard
{
};

class ShrineCard : public PlaceCard
{
};

class BlizzardCard : public EventCard
{
};

class MarketDayCard : public EventCard
{
};

class WolfCard : public EnemyCard
{
};

class WildBoarCard : public EnemyCard
{
};

class BearCard : public EnemyCard
{
};

