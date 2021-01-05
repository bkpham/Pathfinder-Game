#include <iostream>
#include "map_segment.hpp"

char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width, int ID)
    : MapID(ID), mHeight(height), mWidth(width),
      mPortalY{(mHeight - 1) / 2}
    , mPortalX{(mWidth - 1) / 2}
{
}

Portal::Portal(int start_map, int end_map, int start_dir, int end_dir)
    : mstart_map(start_map), mend_map(end_map), mstart_dir(start_dir),
    mend_dir(end_dir)
{
}
bool MapSegment::deleteItem(int ypos, int xpos) {
    int i = 0;
    for(auto item : Item_List){        
        if (item.getY() == ypos && item.getX() == xpos) {          
            Item_List.erase(Item_List.begin() + i );
            return true;            
        }
        i++;
    }
    return false;
}

std::vector<std::string> MapSegment::getAsLines() {
    std::vector<std::string> Map;
    std::string temp;    
    for(int i= 0; i < mWidth; i++)
        temp.push_back(' ');    
    for(int j=0; j<mHeight; j++)
        Map.push_back(temp);

    for(int row = 0; row < mHeight; row++) {
        for (int column = 0; column < mWidth; column++){
            if(row == 0 || row == mHeight -1)
                Map[row][column] = HORIZONTAL_BORDER_CHAR;
            else if((column == 0 && (row < mHeight-1 )) || ((column == mWidth -1) &&(row < mHeight-1 )))
                Map[row][column] = VERTICAL_BORDER_CHAR;

        }
    }
    for(auto item: Item_List)
        Map[item.getY()][item.getX()] = Item::ICON;
    for(auto portal: Portal_List){
        if(Portal_List.empty())
            break;
        if(portal.get_startmap() == MapID ){
            if(portal.get_startdir() == 0)
                Map[0][mPortalX] = PORTAL_CHAR;
            else if(portal.get_startdir() == 1)
                Map[mPortalY][mWidth-1] = PORTAL_CHAR;
            else if(portal.get_startdir() == 2)
                Map[mHeight-1][mPortalX] = PORTAL_CHAR;
            else
                Map[mPortalY][0] = PORTAL_CHAR;
        }
        else if(portal.get_endmap() == MapID ){
            if(portal.get_enddir() == 0)
                Map[0][mPortalX] = PORTAL_CHAR;
            else if(portal.get_enddir() == 1)
                Map[mPortalY][mWidth-1] = PORTAL_CHAR;
            else if(portal.get_enddir() == 2)
                Map[mHeight-1][mPortalX] = PORTAL_CHAR;
            else
                Map[mPortalY][0] = PORTAL_CHAR;
        }
    }
    for(auto building: Building_List) {
        if (Building_List.empty())
            break;
        building.drawIn(Map);
    }
    return Map;

}

