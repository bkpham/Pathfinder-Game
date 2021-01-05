#ifndef GAME_HPP
#define GAME_HPP

#include <utility>

#include "controller.hpp"
#include "view.hpp"
#include "interface_type.hpp"
#include "map_segment.hpp"
class Level
{
public:
    explicit Level(const std::string& filename, std::string path);
    int getStartY() const{return start_y;}
    int getStartX() const{return start_x;}
    std::string getStartDir() const{return start_direction;}
    int getStartSeg() const{return start_segment;}
    int getMaxMoves() const{return max_movements;}
    int getNumItems() const{return number_items;}
    std::vector<MapSegment> getMapList() const{return Map_List;}
    void addDeleted_Item(Item item) {Deleted_Items.push_back(item);}
    std::vector<Item> getDeleted_Item(){return Deleted_Items; }
    void updateMapList(MapSegment newMap, int MapID){Map_List[MapID] = std::move(newMap);}


private:
    int start_segment{};
    int start_y{};
    int start_x{};
    std::string start_direction;
    std::vector<MapSegment> Map_List;
    int max_movements;
    int number_items;
    std::string path_name;
    std::vector<Item> Deleted_Items;

};

class Game
{
public:  
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    void run();

private:  
    std::vector<std::string> draw( MapSegment& map);
    
    int noCollision( MapSegment& map);

    static const int MIN_VIEW_HEIGHT;
    static const int MIN_VIEW_WIDTH;
    static const char HERO_ICON_LEFT;
    static const char HERO_ICON_RIGHT;
    static const char HERO_ICON_UP;
    static const char HERO_ICON_DOWN;
    int screen_height;
    int screen_width;
    int num_levels;
    std::vector<std::string> level_names;
    std::vector<Level> level_list;
    int posx;
    int posy;
    int direction;
    int moves;
    int items;
    int map_segment;

    View* mView;
    Controller* mController;

    InterfaceType mInterfaceType;
};



#endif // GAME_HPP
