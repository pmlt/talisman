#pragma once
#include <queue>

class AdventureCard
{
public:
  AdventureCard(void);
  virtual ~AdventureCard(void);

  static void createDeckFromFile(std::string deck_file, std::queue<AdventureCard*> &deck);

  string title();
  void title(string title);
  unsigned char number();
  void number(unsigned char number);

  virtual void doEncounter();

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
  string _type();
};

class ObjectCard : public AdventureCard
{
public:
  string type();
  void type(string type);
private:
  string _type();
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
