#pragma once

/*
  Class: TException
  Base class for all Talisman exceptions.
*/
class TException
{
public:
  TException(void);
  virtual ~TException(void);
};

/*
  Class: NotInInventoryException
  Occurs when a character attempts to drop something that he
  is not carrying.
*/
class NotInInventoryException : public TException {};

/*
  Class: InventoryFullException
  Occurs when a character attempts to pickup an object when
  his inventory is already full.
*/
class InventoryFullException : public TException {};
