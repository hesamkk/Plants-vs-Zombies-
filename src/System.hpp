#pragma one

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"

using namespace std;
using namespace sf;

class System{
public:
    void Handler();
    void Music();
    void Run();
    void RenderBG();
private:
    vector <Plant*> plants;
    vector <Zombie*> zombies;
    int field_width;
    int field_hight;
    int money;
    const string bg_file_path = "";
};