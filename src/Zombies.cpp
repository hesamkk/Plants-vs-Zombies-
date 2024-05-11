#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Zombies.hpp"

using namespace std;
using namespace sf;

Zombie::~Zombie(){
    
};

void Zombie::Mover(){
    pos.x -= speed;
}

Sprite Zombie::get_sprite(){
    return sprite; 
}

void Zombie::Update(){
    sprite.setPosition(pos);
    if (pos.x < 0)
    {
        cout << "kk"<<endl;
    }
}

void Zombie::NextFrame(){
    DeltaTime_NextFrame += clock.restart();
    if(DeltaTime_NextFrame >= frame_changeTime){
    rect.left += rect.width;
    if (rect.left >= 1000 )
        rect.left =0;
    sprite.setTextureRect(rect);
    DeltaTime_NextFrame = Time::Zero;
    }
}

bool Zombie::Is_Shot(Vector2i pea_position){
    revealing_the_bounds();
    
    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(pea_position)))
    {
            
        return true;
        
    }
    else
        
        return false;

}