#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Board.h"
#include "MapTile.h"
#include "TException.h"

#define ASCII0 48;

Board::Board(void)
{
  for (int i=0; i < BOARD_ROWS; i++) {
    for (int j=0; j < BOARD_COLS; j++) {
      this->tiles[i][j] = NULL;
    }
  }
}


Board::~Board(void)
{
  for (int i=0; i < BOARD_ROWS; i++) {
    for (int j=0; j < BOARD_COLS; j++) {
      if (this->tiles[i][j] == NULL) continue;
      delete this->tiles[i][j];
    }
  }
}

MapTile* Board::find(string title)
{
  for (int i=0; i < BOARD_ROWS; i++) {
    for (int j=0; j < BOARD_COLS; j++) {
      if (this->tiles[i][j] == NULL) continue;
      if (this->tiles[i][j]->getTitle() == title) return this->tiles[i][j];
    }
  }
  return NULL;
}

Board* Board::createFromFile(string map_file)
{
  // Read file and construct and arrange tiles from the file
  string line;
  unsigned int x,y;
  string ident;
  MapTile *tile;

  Board* b = new Board();

  ifstream maphandle;
  maphandle.open(map_file, ios::in);
  if (maphandle.is_open()) {
    while (maphandle.good()) {
      getline(maphandle, line);
      if (line.size() <= 0) continue; //Empty line
      if (line[0] == ';') continue; //Comment line
      x = line[0] - ASCII0;
      y = line[1] - ASCII0;
      if (x > (BOARD_ROWS - 1) ||
          y > (BOARD_COLS - 1) ||
          line[2] != ' ') {
        throw new InvalidMapFileException(line);
      }
      ident = line.substr(3);
      if (ident == "VillageTile") tile = new VillageTile();
      else if (ident == "FieldsTile") tile = new FieldsTile();
      else if (ident == "GraveyardTile") tile = new GraveyardTile();
      else if (ident == "WoodsTile") tile = new WoodsTile();
      else if (ident == "SentinelTile") tile = new SentinelTile();
      else if (ident == "HillsTile") tile = new HillsTile();
      else if (ident == "ChapelTile") tile = new ChapelTile();
      else if (ident == "CragsTile") tile = new CragsTile();
      else if (ident == "PlainsTile") tile = new PlainsTile();
      else if (ident == "CityTile") tile = new CityTile();
      else if (ident == "TavernTile") tile = new TavernTile();
      else if (ident == "RuinsTile") tile = new RuinsTile();
      else if (ident == "ForestTile") tile = new ForestTile();
      else if (ident == "PortalOfPowerTile") tile = new PortalOfPowerTile();
      else if (ident == "BlackKnightTile") tile = new BlackKnightTile();
      else if (ident == "HiddenValleyTile") tile = new HiddenValleyTile();
      else if (ident == "CursedGladeTile") tile = new CursedGladeTile();
      else if (ident == "RunesTile") tile = new RunesTile();
      else if (ident == "ChasmTile") tile = new ChasmTile();
      else if (ident == "WarlocksCaveTile") tile = new WarlocksCaveTile();
      else if (ident == "DesertTile") tile = new DesertTile();
      else if (ident == "OasisTile") tile = new OasisTile();
      else if (ident == "TempleTile") tile = new TempleTile();
      else if (ident == "CastleTile") tile = new CastleTile();
      else if (ident == "PlainsOfPerilTile") tile = new PlainsOfPerilTile();
      else if (ident == "MinesTile") tile = new MinesTile();
      else if (ident == "VampiresTowerTile") tile = new VampiresTowerTile();
      else if (ident == "PitsTile") tile = new PitsTile();
      else if (ident == "ValleyOfFireTile") tile = new ValleyOfFireTile();
      else if (ident == "WerewolfDenTile") tile = new WerewolfDenTile();
      else if (ident == "DeathTile") tile = new DeathTile();
      else if (ident == "CryptTile") tile = new CryptTile();
      else throw new InvalidMapFileException(line);

      b->tiles[x][y] = tile;
    }
  }
  else {
    throw new FileOpenException(map_file);
  }
  maphandle.close();
  //Set neighbors for each tile.
  for (int i=0; i < BOARD_ROWS; i++) {
    for (int j=0; j < BOARD_COLS; j++) {
      if (b->tiles[i][j] == NULL) continue;

      MapTile* cw;
      MapTile* ccw;
      int min_i = 0;
      int min_j = 0;
      int max_i = BOARD_ROWS-1;
      int max_j = BOARD_COLS-1;

      //Find the region we're in
      while (i != min_i && i != max_i && j != min_j && j != max_j) {
        min_i++;
        max_i--;
        min_j++;
        max_j--;
      }
      //Find cw
      if (i == min_i) {
        if (j == min_j) {
          //Top-left corner
          cw = b->tiles[i+1][j];
          ccw = b->tiles[i][j+1];
        }
        else if (j > min_j && j < max_j) {
          //Top row, in the middle
          cw = b->tiles[i+1][j];
          ccw = b->tiles[i-1][j];
        }
        else {
          //Top-right corner
          cw = b->tiles[i][j+1];
          ccw = b->tiles[i-1][j];
        }
      }
      else if (i > min_i && i < max_i) {
        if (j == min_j) {
          //Left column, in the middle
          cw = b->tiles[i][j-1];
          ccw = b->tiles[i][j+1];
        }
        else {
          //Right column, in the middle
          cw = b->tiles[i][j+1];
          ccw = b->tiles[i][j-1];
        }
      }
      else {
        if (j == min_j) {
          //Bottom-left corner
          cw = b->tiles[i][j-1];
          ccw = b->tiles[i+1][j];
        }
        else if (j > min_j && j < max_j) {
          //Bottom row, in the middle
          cw = b->tiles[i-1][j];
          ccw = b->tiles[i+1][j];
        }
        else {
          //Bottom-right corner
          cw = b->tiles[i-1][j];
          ccw = b->tiles[i][j-1];
        }
      }
      
      b->tiles[i][j]->setNeighbors(cw, ccw);
    }
  }
  return b;
}

MapTile*** Board::getTiles() const { return (MapTile***)this->tiles; }
