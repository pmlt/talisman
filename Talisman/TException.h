#pragma once
#include <string>

using namespace std;

/*
  Class: TException
  Base class for all Talisman exceptions.
*/
class TException
{
public:
  TException(void);
  virtual ~TException(void);

  virtual string message();
};

/*
  Class: NotInInventoryException
  Occurs when a character attempts to drop something that he
  is not carrying.
*/
class NotInInventoryException : public TException
{
public:
  virtual string message();
};

/*
  Class: InventoryFullException
  Occurs when a character attempts to pickup an object when
  his inventory is already full.
*/
class InventoryFullException : public TException
{
public:
  virtual string message();
};

/*
  Class: PlayerNotFoundException
  Occurs when the game tries to remove a player that is not
  currently playing.
*/
class PlayerNotFoundException : public TException
{
public:
  virtual string message();
};

/*
  Class: PlayerExistsException
  Occurs when the game tries to add a player that is
  already currently playing.
*/
class PlayerExistsException : public TException
{
public:
  virtual string message();
};

/*
  Class: InvalidMapFileException
  Occurs whenever a bad file was passed to Board::from_file.
*/
class InvalidMapFileException : public TException
{
public:
  InvalidMapFileException();
  InvalidMapFileException(string line);
  virtual string message();
private:
  string line;
};