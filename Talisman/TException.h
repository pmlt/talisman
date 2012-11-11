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
  TException(string msg);
  virtual ~TException(void);

  virtual string message();
private:
  string msg;
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
  Class: FileOpenException
  Occurs when a file can't be opened for reading or writing
*/
class FileOpenException : public TException
{
public:
  FileOpenException(string filename);
  virtual string message();
private:
  string filename;
};

/*
  Class: InvalidMapFileException
  Occurs whenever a bad file was passed to Board::createFromFile.
*/
class InvalidMapFileException : public TException
{
public:
  InvalidMapFileException(string line);
  virtual string message();
private:
  string line;
};

/*
  Class: InvalidCharacterFileException
  Occurs whenever a bad file was passed to Character::createFromFile.
*/
class InvalidCharacterFileException : public TException
{
public:
  InvalidCharacterFileException(string line);
  virtual string message();
private:
  string line;
};