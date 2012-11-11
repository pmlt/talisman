#include "StdAfx.h"
#include "TException.h"

using namespace std;

TException::TException(void)
{
}


TException::~TException(void)
{
}

string TException::message() { return "Generic error."; }
string NotInInventoryException::message() { return "The item was not found in the inventory."; }
string InventoryFullException::message() { return "This character's inventory is full."; }
string PlayerNotFoundException::message() { return "Player not found."; }
string PlayerExistsException::message() { return "This player is already in the game."; }

InvalidMapFileException::InvalidMapFileException() {}
InvalidMapFileException::InvalidMapFileException(string l) : line(l) {}
string InvalidMapFileException::message() {
  if (this->line.size() > 0) return "The provided map file has an error on line: " + this->line;
  else return "The provided map file was invalid.";
}
