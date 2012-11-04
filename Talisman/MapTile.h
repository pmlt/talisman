#pragma once

#include <string>

using namespace std;

/*
  Class: MapTile
  Represents a location on the board. Dummy class to help model Character for now.
*/
class MapTile
{
public:
  MapTile(string title);
  virtual ~MapTile(void);

  virtual string getTitle() const;
  
  void setNeighbors(MapTile* top, MapTile* right, MapTile* bottom, MapTile* left);
  void setInwardBridge(MapTile* bridge);
  void setOutwardBridge(MapTile* bridge);

  unsigned char rollMovement();

private:
  string title;
  MapTile* top;
  MapTile* left;
  MapTile* bottom;
  MapTile* right;
  MapTile* inward_bridge;
  MapTile* outward_bridge;
};

class OuterMapTile : public MapTile
{
public:
  OuterMapTile();
  virtual ~OuterMapTile();
};

class MiddleMapTile : public MapTile
{
public:
  MiddleMapTile();
  virtual ~MiddleMapTile();
};

class InnerMapTile : public MapTile
{
public:
  InnerMapTile();
  virtual ~InnerMapTile();
};
