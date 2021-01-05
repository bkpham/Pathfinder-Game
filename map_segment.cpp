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
    //std::cout << "TRYING TO DELETE ITEMS" <<std::endl;
    for(auto item : Item_List){
        //std::cout<< "comparing our posy: " << ypos << " posx:  " << xpos << std::endl;
        //std::cout << "to item posy: " << item.getY() << " item posx: " <<item.getX() << std::endl;
        if (item.getY() == ypos && item.getX() == xpos) {
            //std::cout << "we should delete this item" << std::endl;
            //std::cout << "size of itemlist before delete: " << Item_List.size();
            Item_List.erase(Item_List.begin() + i );
            return true;
            //std::cout << "size of itemlist now: " << Item_List.size();
        }
        i++;
    }
    return false;
}

std::vector<std::string> MapSegment::getAsLines() {
    std::vector<std::string> Map;
    std::string temp;
    //std::cout << "SHOULD BE A " << mHeight << " by " << mWidth << std::endl;
    for(int i= 0; i < mWidth; i++)
        temp.push_back(' ');
    //std::cout << "this is temp : " << temp << " size of " << temp.size()<< std::endl;
    /*Map.push_back(temp);
    Map.push_back(temp);
    Map.push_back(temp);
    std::cout << Map[0] << std::endl;
    std::cout << Map[1] << std::endl;
    std::cout << Map[2] << std::endl;*/
    for(int j=0; j<mHeight; j++)
        Map.push_back(temp);

    /*for (int i = 0; i < mHeight; i++) {
        for (int j = 0; j < mWidth; j++)
            std::cout << Map[i][j];
        std::cout << std::endl;
    }*/

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

