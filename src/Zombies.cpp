#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Zombies.hpp"

using namespace std;
using namespace sf;

Zombie::~Zombie(){

};

void Zombie::Mover()
{
    if (DeltaTime_Freeze <= Time::Zero)
    {
        pos.x -= speed;
        frame_changeTime = milliseconds(100);
    }
    else
    {
        pos.x -= speed / 3;
        DeltaTime_Freeze -= DeltaTime;
    }
}

Sprite Zombie::get_sprite()
{
    return sprite;
}

void Zombie::Update()
{
    sprite.setPosition(pos);
    DeltaTime = Time::Zero;
    DeltaTime += clock.restart();
}

void Zombie::NextFrame()
{

    DeltaTime_NextFrame += DeltaTime;
    if (DeltaTime_NextFrame >= frame_changeTime)
    {

        rect.left += rect.width;

        if (rect.left >= 2000)
            rect.left = 0;

        sprite.setTextureRect(rect);
        DeltaTime_NextFrame = Time::Zero;
    }
}

bool Zombie::Is_Shot(Vector2i pea_position)
{
    revealing_the_bounds();

    if (Sprite_Bounds.contains(static_cast<sf::Vector2f>(pea_position)))
    {

        return true;
    }
    else

        return false;
}

bool Zombie::Is_eating(Vector2f plant_position)
{
    revealing_the_bounds();

    if (Sprite_Bounds.contains(plant_position))
    {

        return true;
    }
    else

        return false;
}

void Zombie::Attack()
{
    pos.x += speed;
}

void Zombie::Damage(const int &d)
{
    health -= d;
}

void Zombie::Freeze()
{
    DeltaTime_Freeze = freeze_time;
    frame_changeTime = milliseconds(300);
}

bool Zombie::IsCross()
{
    if (pos.x <= 0)
        return true;
    return false;
}
