#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "Global.hpp"

using namespace std;
using namespace sf;
const int Window_hight = 425;
const int Window_lenght = 1000;

class System{
public:
    void Handler();
    void Music();
    void Run();
    void RenderBG();
    void MakeSun(int r);
    void Updater();
private:
    vector <Plant*> plants;
    vector <Zombie*> zombies;
    vector <Sun*> suns;
    int field_width;
    int field_hight;
    int money = 0;
    const string bg_file_path = "";
};