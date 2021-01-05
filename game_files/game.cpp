#include <fstream>
#include <utility>
#include "game.hpp"
#include "curses_view.hpp"
#include "curses_controller.hpp"
#include "print_view.hpp"
#include "print_controller.hpp"
#include <sstream>
#include <iostream>
#include <string>



const int Game::MIN_VIEW_HEIGHT = 15;
const int Game::MIN_VIEW_WIDTH = 15;
const char Game::HERO_ICON_LEFT = '<';
const char Game::HERO_ICON_RIGHT = '>';
const char Game::HERO_ICON_UP = '^';
const char Game::HERO_ICON_DOWN = 'v';
Level::Level(const std::string& filename, std::string path)
{
    std::string true_file;
    if(filename[0] == '.'){
        std::size_t found = filename.find_first_of("/\\");
        path_name = filename.substr(found+1, filename.size()-1);
    } else
        path_name  = path + filename;
    std::ifstream level_file{path_name};
    level_file >> start_segment >> start_y >> start_x >> start_direction;
    std::string line;
    int Mid = 0;
    number_items = 0;
    while(level_file){
        getline(level_file, line);
        if(line.find('M') != std::string::npos){
            std::stringstream ss;
            int h,w;
            ss << line;
            std::string temp;
            ss>> temp; ss>>temp;
            h = std::stoi(temp);
            ss>>temp;
            w = std::stoi(temp);
            MapSegment map{h,w,Mid};
            Mid++;
            Map_List.push_back(map);
        }
        else if(line.find('B') != std::string::npos){
            std::stringstream ss;
            int id, y,x;
            ss << line;
            std::string temp;
            ss>> temp; ss>>temp;
            id = std::stoi(temp);
            ss >> temp;
            y = std::stoi(temp);
            ss >>temp;
            x = std::stoi(temp);
            Building building{y,x};
            (Map_List[id]).addBuilding(building);
        }

        else if(line.find('I') != std::string::npos){
            std::stringstream ss;
            int id, y,x;
            ss << line;
            std::string temp;
            ss>> temp; ss>>temp;
            id = std::stoi(temp);
            ss>>temp;
            y = std::stoi(temp);
            ss>>temp;
            x = std::stoi(temp);
            Item item{y,x};
            (Map_List[id]).addItem(item);
            number_items++;
        }

        else if(line.find('P') != std::string::npos){
            std::stringstream ss;
            std::string s_dir, e_dir;
            int s_map, e_map, st, ed;
            ss << line;
            std::string temp;
            ss>> temp; ss>>temp;
            s_map = std::stoi(temp);
            ss >> temp;
            s_dir = temp;
            ss>>temp;
            e_map = std::stoi(temp);
            ss >> temp;
            e_dir = temp;
            if(s_dir == "left") st = 3;
            if(s_dir == "up") st = 0;
            if(s_dir == "right") st = 1;
            if(s_dir == "down") st = 2;
            if(e_dir == "left") ed = 3;
            if(e_dir == "up") ed = 0;
            if(e_dir == "right") ed = 1;
            if(e_dir == "down") ed = 2;
            Portal portal{s_map,e_map,st,ed};
            (Map_List[s_map]).addPortal(portal);
            (Map_List[e_map]).addPortal(portal);
        }

        else if(line.find('N') != std::string::npos){
            std::stringstream ss;
            int mm;
            ss << line;
            std::string temp;
            ss >> temp; ss>>temp;
            mm = std::stoi(temp);
            max_movements = mm;
        }

    }

}
Game::Game(const std::string& filename, InterfaceType interfaceType)
    : mView{nullptr}, mController{nullptr}, mInterfaceType{interfaceType}
{
    std::size_t found = filename.find_first_of("/\\");
    std::string path = filename.substr(0,found+1);
    mInterfaceType = interfaceType;
    std::string line;
    std::ifstream file{filename};
    //initial opening of file, get level list
    file >> screen_height >> screen_width >> num_levels;
    getline(file,line);
    for(int a=0; a<num_levels;a++) {
        getline(file, line);
        level_names.push_back(line);
    }
    //creating the levels from level list
    for(int a=0; a<num_levels;a++) {
        Level l{level_names[a],path};
        level_list.push_back(l);
    }
    if (mInterfaceType == InterfaceType::Print) {
        mView = new PrintView{screen_height,screen_width};
        mController = new PrintController{};
    } else {
        mView = new CursesView{screen_height,screen_width};
        mController = new CursesController{};
    }


}

Game::~Game()
{
    free(mView);
    free(mController);
}

void Game::run() {

    for (int i = 0; i < num_levels; i++) {
        posy = level_list[i].getStartY();
        posx = level_list[i].getStartX();
        if (level_list[i].getStartDir() == "left")
            direction = 3;
        if (level_list[i].getStartDir() == "up")
            direction = 0;
        if (level_list[i].getStartDir() == "right")
            direction = 1;
        if (level_list[i].getStartDir() == "down")
            direction = 2;
        moves = level_list[i].getMaxMoves();
        items = level_list[i].getNumItems();
        map_segment = level_list[i].getStartSeg();
        MapSegment currmap = (level_list[i].getMapList())[map_segment];

        while (moves) {

            if(mInterfaceType == InterfaceType::Print){
                std::cout << "Level: " << i + 1 << std::endl;
                std::cout << "Items remaining: " << items << std::endl;
                std::cout << "Moves remaining: " << moves << std::endl;
            }
            else{
                std::string string_level = std::to_string(i+1);
                std::string string_item = std::to_string(items);
                std::string string_moves = std::to_string(moves);
                if(string_moves.size() == 1){
                    move(2,18);
                    delch();}
                if(string_item.size() == 1){
                    move(1,18);
                    delch();}
                if(string_moves.size() == 2){
                    move(2,19);
                    delch();}
                if(string_item.size() == 2){
                    move(1,19);
                    delch();}
                if(string_moves.size() == 3){
                    move(2,20);
                    delch();}
                if(string_item.size() == 3){
                    move(1,20);
                    delch();}
                if(string_moves.size() == 4){
                    move(2,21);
                    delch();}
                if(string_moves.size() == 5){
                    move(2,22);
                    delch();}
                mvaddstr(0,0,"Level:");
                mvaddstr(0,7,string_level.c_str());
                mvaddstr(1,0,"Items remaining:");
                mvaddstr(1,17,string_item.c_str());
                mvaddstr(2,0,"Moves remaining:");
                mvaddstr(2,17,string_moves.c_str());
            }

            mView->draw(Game::draw((currmap)));
            if (items == 0)
                break;

            if(mInterfaceType == InterfaceType::Print)
                std::cout << "Enter input: ";

            Command in = mController->getInput();
            if (in == Command::Invalid)
                continue;
            else if (in == Command::Quit) {
                std::cout << "You quit the game. " << std::endl;
                return;
            } else if (in == Command::Left && direction == 0)
                direction = 3;
            else if (in == Command::Left && direction == 1)
                direction = 0;
            else if (in == Command::Left && direction == 2)
                direction = 1;
            else if (in == Command::Left && direction == 3)
                direction = 2;
            else if (in == Command::Right && direction == 0)
                direction = 1;
            else if (in == Command::Right && direction == 1)
                direction = 2;
            else if (in == Command::Right && direction == 2)
                direction = 3;
            else if (in == Command::Right && direction == 3)
                direction = 0;
            else if (in == Command::Forward) {
                if (noCollision(currmap) == 3) {
                    if (direction == 0)
                        posy--;
                    else if (direction == 1)
                        posx++;
                    else if (direction == 2)
                        posy++;
                    else if (direction == 3)
                        posx--;
                    moves--;
                    if(moves == 0) {
                        if(mInterfaceType == InterfaceType::Curses)
                            endwin();
                        std::cout << "You lost the game. " << std::endl;
                        return;
                    }
                } else if (noCollision(currmap) == 1) {
                    if (direction == 0)
                        posy--;
                    else if (direction == 1)
                        posx++;
                    else if (direction == 2)
                        posy++;
                    else if (direction == 3)
                        posx--;
                    moves--;
                    currmap.deleteItem(posy, posx);
                    items--;
                    if(items == 0)
                        break;
                    if(moves == 0) {
                        if(mInterfaceType == InterfaceType::Curses)
                            endwin();
                        std::cout << "You lost the game. " << std::endl;
                        return;
                    }
                }

                else if (noCollision(level_list[i].getMapList()[map_segment]) == 2) {
                    for (auto portal: currmap.getPortals()) {
                        if (portal.get_startmap() == map_segment) {
                            if (portal.get_startdir() == direction) {
                                moves--;
                                if(moves == 0) {
                                    if(mInterfaceType == InterfaceType::Curses)
                                        endwin();
                                    std::cout << "You lost the game. " << std::endl;
                                    return;
                                }
                                level_list[i].updateMapList(currmap, map_segment);
                                map_segment = portal.get_endmap();
                                currmap = level_list[i].getMapList()[map_segment];
                                if (portal.get_enddir() == 0) {
                                    posx = currmap.getPortalX();
                                    posy = 1;
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 2;
                                } else if (portal.get_enddir() == 1) {
                                    posx = currmap.getWidth() - 2;
                                    posy = currmap.getPortalY();
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 3;
                                } else if (portal.get_enddir() == 2) {
                                    posx = currmap.getPortalX();
                                    posy = currmap.getHeight() - 2;
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 0;
                                } else if (portal.get_enddir() == 3) {
                                    posx = 1;
                                    posy = currmap.getPortalY();
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 1;
                                }
                            }
                        } else if (portal.get_endmap() == map_segment) {
                            if (portal.get_enddir() == direction) {
                                moves--;
                                if(moves == 0) {
                                    if(mInterfaceType == InterfaceType::Curses)
                                        endwin();
                                    std::cout << "You lost the game. " << std::endl;
                                    return;
                                }
                                level_list[i].updateMapList(currmap, map_segment);
                                map_segment = portal.get_startmap();
                                currmap = level_list[i].getMapList()[map_segment];
                                if (portal.get_startdir() == 0) {
                                    posx = currmap.getPortalX();
                                    posy = 1;
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 2;
                                } else if (portal.get_startdir() == 1) {
                                    posx = currmap.getWidth() - 2;
                                    posy = currmap.getPortalY();
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 3;
                                } else if (portal.get_startdir() == 2) {
                                    posx = currmap.getPortalX();
                                    posy = currmap.getHeight() - 2;
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 0;
                                } else if (portal.get_startdir() == 3) {
                                    posx = 1;
                                    posy = currmap.getPortalY();
                                    if(currmap.deleteItem(posy,posx))
                                        items--;
                                    if(items == 0)
                                        break;
                                    direction = 1;

                                }
                            }
                        }
                    }


                }


            }

            }


        }

    if(mInterfaceType == InterfaceType::Print){
        std::cout << "Level: " << num_levels << std::endl;
        std::cout << "Items remaining: " << items << std::endl;
        std::cout << "Moves remaining: " << moves << std::endl;
        mView->draw(Game::draw((level_list[num_levels-1].getMapList()[map_segment])));
    }
    if(mInterfaceType == InterfaceType::Curses)
        endwin();
    std::cout << "You won the game. " << std::endl;
    return;

    }


    // TODO: Implement.


std::vector<std::string> Game::draw(MapSegment& map) {
    int top_view, bot_view, left_view, right_view,temp_int = 0;
    int centerx = (screen_width-1)/2;
    int centery = (screen_height-1)/2;
    std::string temp2;
    std::vector<std::string> GameMap;
    for(int i =0; i<screen_width;i++)
        temp2.push_back('~');
    for(int i=0; i<screen_height;i++)
        GameMap.push_back(temp2);
    //std::cout << "GAME MAP BEFORE" <<std::endl;
    //mView->draw(GameMap);
    for(int i=0; i<posy;i++) {
        if (i > centery-1)
            break;
        temp_int++;
    }
    top_view = temp_int;
    temp_int = 0;
    for(int i=0; i<((map.getHeight())-posy-1); i++) {
        if (i > (screen_height - centery))
            break;
        temp_int++;
    }
    bot_view = temp_int;
    temp_int = 0;
    for(int i=0; i<((map.getWidth())-posx-1); i++) {
        if (i > (screen_width - ((screen_width - 1) / 2)))
            break;
        temp_int++;
    }
    right_view = temp_int;
    temp_int = 0;
    for(int i=0; i<posx; i++) {
        if (i > centerx - 1)
            break;
        temp_int++;
    }
    //std::cerr << "heyo";
    left_view = temp_int;
    for(int i=0; i<=top_view+bot_view; i++)
        for(int j=0; j<=right_view + left_view; j++) {
            if(centery - top_view + i >= screen_height || centerx - left_view + j > screen_width )
                break;        
            GameMap[centery - top_view + i][centerx - left_view + j] = map.getAsLines()[posy - top_view + i][posx - left_view + j];        
            map.getAsLines();
        }

    if(direction == 2) GameMap[centery][centerx] = HERO_ICON_DOWN;
    else if(direction == 0) GameMap[centery][centerx] = HERO_ICON_UP;
    if(direction == 1) GameMap[centery][centerx] = HERO_ICON_RIGHT;
    if(direction == 3) GameMap[centery][centerx] = HERO_ICON_LEFT;
    
    std::string temp3;
    std::vector<std::string> realMap;
    for(int i=0; i<screen_width+2;i++)
        temp3.push_back('*');
    for(int i=0; i<screen_height+2; i++)
        realMap.push_back(temp3);
    for(int i=0; i<screen_height;i++)
        for(int j=0;j<screen_width; j++)
            realMap[1+i][j+1] = GameMap[i][j];
    GameMap.clear();

    return realMap;
}

int Game::noCollision( MapSegment& map) {
    
    char infront;
    if(direction == 0)
        infront = map.getAsLines()[posy-1][posx];
    else if(direction == 1)
        infront = map.getAsLines()[posy][posx+1];
    else if(direction == 2)
        infront = map.getAsLines()[posy+1][posx];
    else if(direction == 3)
        infront = map.getAsLines()[posy][posx-1];
    //std::cout << "THIS IS INFRONT OF US " << infront << std::endl;
    if (infront == '=' || infront == '|' || infront == '.' ||infront == '&')
        return 0;
    else if(infront == '$')
        return 1;
    else if(infront == '@')
        return 2;
    else
        return 3;


}



