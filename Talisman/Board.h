#pragma once

#define BOARD_ROWS 7
#define BOARD_COLS 7

#include "MapTile.h"

class Board
{
public:
  Board(void);
  ~Board(void);

  static Board* createFromFile(string map_file);

  MapTile* find(string title);
  (MapTile ***) getTiles() const;
  
private:
  (MapTile*) tiles[BOARD_ROWS][BOARD_COLS]; // 7x7 game board
};
