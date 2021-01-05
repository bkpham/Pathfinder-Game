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
public:  // public methods
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    void run();

private:  // private methods
    /**
     * You DO NOT need to have any of the private methods below.
     * I just left some commented out declarations in case it
     * helps guide your thinking, but you don't need to use them.
     */

    /**
     * Set up the 2D vector of strings that is then given to the draw()
     * method of an instance of a subclass of View.
     */
    std::vector<std::string> draw( MapSegment& map);
    //given a map segment, checks if moving forward will result in collision
    int noCollision( MapSegment& map);



    /**
     * Loop until the game is over. On each iteration, use the controller
     * to get input from the user.
     */
    // void doGameLoop();

    /**
     * Update matters related to game logic, e.g. collisions, level completion.
     */
    // void update();

    /**
     * Load information related to new level into member variables,
     * being careful to not leave traces of information from previous levels. 
     */
    // void loadLevel();

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



    /**
     * Because one of the constructor parameters must be checked in order
     * to determine the subclass types for the below members, they can't
     * be references, because there's no default constructors for them.
     * (Recall that each member in a class must either be initialized by an
     * initializer list in the constructor OR have a default constructor.)
     */
    View* mView;
    Controller* mController;

    InterfaceType mInterfaceType;
};



#endif // GAME_HPP
