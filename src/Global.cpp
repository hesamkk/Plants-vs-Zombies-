#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.hpp"

using namespace std;
using namespace sf;

const int Window_hight = 425;
const int Window_lenght = 1000;

void Sun::MoveDown(){
    pos.y += 0.3;
}

void Sun::Update(){
    sprite.setPosition(pos);
}

