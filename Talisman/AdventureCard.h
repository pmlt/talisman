#pragma once
#include <queue>

class AdventureCard
{
public:
  AdventureCard(void);
  virtual ~AdventureCard(void);

  static void createDeckFromFile(std::string deck_file, std::queue<AdventureCard*> &deck);
};

