#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"

using namespace std;
using namespace sf;

void Pea::rectMaker(){
    rect.left = 0;
    rect.top = 0;
    rect.height = 35;
    rect.width = 32;
    sprite.setTextureRect(rect);
}

bool Plant::IsThereZombie(const vector<Zombie*> zombies){
    for(auto z: zombies){
        if(z->get_x() >= pos.x && z->get_y() == pos.y)
            return true;
    }
    return false;
}

Plant::~Plant(){

}

void Plant::Updater(){
    
}

bool Plant::IsTouchingMouse(Vector2i Mouse_position){
    revealing_the_bounds();
    
    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(Mouse_position)))
    {
        return true;        
    }
    else
        return false;
}