#ifndef MAP_SEGMENT_HPP
#define MAP_SEGMENT_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "item.hpp"

class Portal{
public:
    Portal(int start_map, int end_map, int start_dir, int end_dir);

    int get_startmap() const {return mstart_map;}
    int get_endmap() const {return mend_map;}
    int get_startdir() const {return mstart_dir;}
    int get_enddir() const {return mend_dir;}

private:
    int mstart_map;
    int mend_map;
    int mstart_dir;
    int mend_dir;
};

class MapSegment
{
public:

    MapSegment(int height, int width, int ID);

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    int getPortalX() const { return mPortalX; }
    int getPortalY() const { return mPortalY; }
    std::vector<Building> getBuildings() const{return Building_List;}
    std::vector<Item> getItems() const{return Item_List;}
    std::vector<Portal> getPortals() const{return Portal_List;}
    void addBuilding(Building B){Building_List.push_back(B);}
    void addItem(Item I){Item_List.push_back(I);}
    void addPortal(Portal P){Portal_List.push_back(P);}
    bool deleteItem(int ypos, int xpos);
    std::vector<std::string> getAsLines();

private:
    static char VERTICAL_BORDER_CHAR;
    static char HORIZONTAL_BORDER_CHAR;
    static char PORTAL_CHAR;
    std::vector<Building> Building_List;
    std::vector<Item> Item_List;
    std::vector<Portal> Portal_List;
    int MapID;
    int mHeight;
    int mWidth;
    int mPortalY;
    int mPortalX;
};

#endif // MAP_SEGMENT_HPP
