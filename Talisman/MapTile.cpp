#include "StdAfx.h"
#include "MapTile.h"


MapTile::MapTile() :
  top(NULL),right(NULL),bottom(NULL),left(NULL),inward_bridge(NULL),outward_bridge(NULL)
{
}


MapTile::~MapTile(void)
{
}

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

string VillageTile::getTitle() const { return "Village"; }

string FieldsTile::getTitle() const { return "Fields"; }

string GraveyardTile::getTitle() const { return "Graveyard"; }

string WoodsTile::getTitle() const { return "Woods"; }

string SentinelTile::getTitle() const { return "Sentinel"; }

string HillsTile::getTitle() const { return "Hills"; }

string ChapelTile::getTitle() const { return "Chapel"; }

string CragsTile::getTitle() const { return "Crags"; }

string CityTile::getTitle() const { return "City"; }

string TavernTile::getTitle() const { return "Tavern"; }

string RuinsTile::getTitle() const { return "Ruins"; }

string ForestTile::getTitle() const { return "Forest"; }

string PortalOfPowerTile::getTitle() const { return "Portal of Power"; }

string BlackKnightTile::getTitle() const { return "Black Knight"; }

string HiddenValleyTile::getTitle() const { return "Hidden Valley"; }

string CursedGladeTile::getTitle() const { return "Cursed Glade"; }

string RunesTile::getTitle() const { return "Runes"; }

string ChasmTile::getTitle() const { return "Chasm"; }

string WarlocksCaveTile::getTitle() const { return "Warlock's Cave"; }

string DesertTile::getTitle() const { return "Desert"; }

string OasisTile::getTitle() const { return "Oasis"; }

string TempleTile::getTitle() const { return "Temple"; }

string CastleTile::getTitle() const { return "Castle"; }

string PlainsOfPerilTile::getTitle() const { return "Plains of Peril"; }

string MinesTile::getTitle() const { return "Mines"; }

string VampiresTowerTile::getTitle() const { return "Vampire's Tower"; }

string PitsTile::getTitle() const { return "Pits"; }

string ValleyOfFireTile::getTitle() const { return "Valley of Fire"; }

string WerewolfDenTile::getTitle() const { return "Werewolf Den"; }

string DeathTile::getTitle() const { return "Death"; }

string CryptTile::getTitle() const { return "Crypt"; }
