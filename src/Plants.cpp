#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"

using namespace std;
using namespace sf;

void Pea::rectMaker(){
    rect.left = 3;
    rect.top = 0;
    rect.height = 33;
    rect.width = 31;
    sprite.setTextureRect(rect);
}

void Walnut::rectMaker(){
    rect.left = 3;
    rect.top = 0;
    rect.height = 33;
    rect.width = 31;
    sprite.setTextureRect(rect);   
}

void SunFlower::rectMaker(){
    rect.left = 3;
    rect.top = 0;
    rect.height = 33;
    rect.width = 31;
    sprite.setTextureRect(rect);   
}

void IcePea::rectMaker(){
    rect.left = 3;
    rect.top = 0;
    rect.height = 33;
    rect.width = 31;
    sprite.setTextureRect(rect);   
}

void Melon::rectMaker(){
    rect.left = 3;
    rect.top = 0;
    rect.height = 33;
    rect.width = 31;
}

bool Plant::IsThereZombie(const vector<Zombie*> zombies){
    for(auto z: zombies){
        if(z->get_x() >= pos.x && (z->get_y()+50 == pos.y || z->get_y() + 60 == pos.y))
            return true;
    }
    return false;
}

Plant::~Plant(){

}

void Plant::Updater(){
    if(status == 1){                  // Attacking status
        NextFrame();
    }
    else{
        NextFrame();
        rect.left = 0;
        sprite.setTextureRect(rect);        
    }
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

void Pea::NextFrame(){
    DeltaTime_NextFrame += clock.restart();
    if(DeltaTime_NextFrame >= frame_changeTime){
    rect.left += 31.2; // needs a magic valeu or something
    if (rect.left >= 200 )
        rect.left =0;
    sprite.setTextureRect(rect);
    DeltaTime_NextFrame = Time::Zero;
    }
}

void IcePea::NextFrame(){
    DeltaTime_NextFrame += clock.restart();
    if(DeltaTime_NextFrame >= frame_changeTime){
    rect.left += 30; // needs a magic valeu or something
    if (rect.left >= 90 )
        rect.left =0;
    sprite.setTextureRect(rect);
    DeltaTime_NextFrame = Time::Zero;
    }
}

void Melon::NextFrame(){
    
}


