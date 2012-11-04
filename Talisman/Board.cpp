#include "stdafx.h"
#include "Board.h"

#include "MapTile.h"

Board::Board(void)
{
}


Board::~Board(void)
{
}

Board* Board::createFromFile(string map_file)
{
  // Read file and construct and arrange tiles from the file
  return NULL;
}

MapTile*** Board::getTiles() const { return (MapTile***)this->tiles; }
