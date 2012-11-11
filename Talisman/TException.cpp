#include "StdAfx.h"
#include "TException.h"

using namespace std;

TException::TException(void) : msg("Generic error.")
{
}

TException::TException(string msg) : msg(msg)
{
}

TException::~TException(void)
{
}

string TException::message() { return this->msg; }
string NotInInventoryException::message() { return "The item was not found in the inventory."; }
string InventoryFullException::message() { return "This character's inventory is full."; }
string PlayerNotFoundException::message() { return "Player not found."; }
string PlayerExistsException::message() { return "This player is already in the game."; }

FileOpenException::FileOpenException(string filename) : filename(filename) {}
string FileOpenException::message() { return "The file " + this->filename + " could not be opened!"; }

InvalidMapFileException::InvalidMapFileException(string l) : line(l) {}
string InvalidMapFileException::message() {
  if (this->line.size() > 0) return "The provided map file has an error on line: " + this->line;
  else return "The provided map file was invalid.";
}

InvalidCharacterFileException::InvalidCharacterFileException(string l) : line(l) {}
string InvalidCharacterFileException::message() {
  if (this->line.size() > 0) return "The provided character file has an error on line: " + this->line;
  else return "The provided character file was invalid.";
}

InvalidCardFileException::InvalidCardFileException(string l) : line(l) {}
string InvalidCardFileException::message() {
  if (this->line.size() > 0) return "The provided card deck file has an error on line: " + this->line;
  else return "The provided card deck file was invalid.";
}
