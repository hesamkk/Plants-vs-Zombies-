#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Zombie{
public:
    Zombie(Vector2f given_pos , int h, int s, int d, const string file_path){
        health = h;
        speed = s;
        damage = d;
        pos = given_pos;
        if(!texture.loadFromFile(file_path))
            abort();
        //rect making
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
    }
    ~Zombie();
    void Render();
    void Update();

private:
    int health;
    int speed;
    int damage;
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
    int status = 0;
};

class NormalZombie : public Zombie{
public:
    NormalZombie(Vector2f given_pos) : Zombie(given_pos , HEALTH, SPEED ,DAMAGE, file_path){

    }
private:
    const int HEALTH = 10;
    const int SPEED = 10;
    const int DAMAGE = 10;
    const string file_path = "";
};

class Giant : public Zombie{
public:
    Giant(Vector2f given_pos) : Zombie(given_pos , HEALTH, SPEED ,DAMAGE ,  file_path){

    }
private:
    const int HEALTH = 10;
    const int SPEED = 10;
    const int DAMAGE = 10;
    const string file_path = "";
};