#include "stdafx.h"
#include "AdventureCard.h"
#include <queue>

using namespace std;

AdventureCard::AdventureCard(void)
{
}


AdventureCard::~AdventureCard(void)
{
}

void AdventureCard::createDeckFromFile(std::string deck_file, std::queue<AdventureCard*> &deck)
{
  //Read file and create deck
}

string AdventureCard::title() { return this->_title; }
void AdventureCard::title(string title) { this->_title = title; }

unsigned char AdventureCard::number() { return this->_number; }
void AdventureCard::number(unsigned char number) { this->_number = number; }

string EnemyCard::type() { return this->_type; }
void EnemyCard::type(string type) { this->_type = type; }

string ObjectCard::type() { return this->_type; }
void ObjectCard::type(string type) { this->_type = type; }
