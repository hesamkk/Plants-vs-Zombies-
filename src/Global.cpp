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

void Sun::vanish(){

    pos.y -= Window_hight;
    cout << "kk";
    Update();

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
        return true;
        
    }
    else
        return false;
    
}
