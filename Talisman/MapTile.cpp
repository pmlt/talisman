#include "StdAfx.h"
#include "MapTile.h"


MapTile::MapTile(string title) :
  title(title),top(NULL),right(NULL),bottom(NULL),left(NULL),inward_bridge(NULL),outward_bridge(NULL)
{
}


MapTile::~MapTile(void)
{
}

string MapTile::getTitle() const { return this->title; }

void MapTile::setNeighbors(MapTile* top, MapTile* right, MapTile* bottom, MapTile* left)
{
  this->top = top;
  this->right = right;
  this->bottom = bottom;
  this->left = left;
}
void MapTile::setInwardBridge(MapTile* bridge) { this->inward_bridge = bridge; }
void MapTile::setOutwardBridge(MapTile* bridge) { this->outward_bridge = bridge; }

unsigned char MapTile::rollMovement()
{
  //Random number between 1 and 6
  return 1;
}