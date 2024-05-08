#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.hpp"

using namespace std;
using namespace sf;

const int Window_hight = 425;
const int Window_lenght = 1000;

void Sun::MoveUpDown(){
    pos.y += dSpeed;
}

void Sun::Update(){
    sprite.setPosition(pos);
}

Sun::~Sun(){
    
}
bool Sun::isClicked(Vector2i Mouse_position){
    
    revealing_the_bounds();
    
    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(Mouse_position)))
    {
        // MoveUp();
        (*money) = (*money) + 25;
        cout << *money << endl;
        dSpeed = -(2.5);
        return true;
        
    }
    else
        return false;
    
}
//test for git.
