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

Shot::~Shot(){
}
bool Sun::isClicked(Vector2i Mouse_position){
    
    revealing_the_bounds();
    
    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(Mouse_position)))
    {
        (*money) = (*money) + 25;
        cout << *money << endl;
        dSpeed = -(2.5);
        return true;
        
    }
    else
        return false;
    
}

bool Pea_Card::is_tagged(Vector2i Mouse_position){

    revealing_the_bounds();

    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(Mouse_position)))
    {
        return true;
    }
    else 
        return false;
}

void Card::Drag(Vector2i Mouse_position){
    pos.x = Mouse_position.x - 1.5*get_sprite().getTextureRect().width ;
    pos.y = Mouse_position.y - 1.5*get_sprite().getTextureRect().height ;
}

void Card::Update(){
    sprite.setPosition(pos);
    DeltaTime_NextFrame += clock.restart();
    if(DeltaTime_NextFrame >= cool_down_time && !Avalablity){
        Avalablity = true;
        rect.left = 0;
        sprite.setTextureRect(rect);
        DeltaTime_NextFrame = Time::Zero;
    }
}

void Pea_Card::RePosition() {
    pos.x = 10;
    pos.y = 10;
}

void Card::Used(){
    DeltaTime_NextFrame = Time::Zero;
    Avalablity = false;
    rect.left += rect.width;
    sprite.setTextureRect(rect);
}

void Shot::Move(){
    pos.x += 1;
    sprite.setPosition(pos);
}