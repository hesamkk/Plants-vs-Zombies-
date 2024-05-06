#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Plant{
public:
    Plant(Vector2f given_pos, int h, const string texture_adr){
        pos = given_pos;
        health = h;
        if(!texture.loadFromFile(texture_adr))
            abort();
        //rect making
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
    }
    ~Plant();
    void Render();
    void Updater();
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int health;
    Vector2f pos;
    int status = 0 ;
};


class SunFlower : public Plant{
public:
    SunFlower(Vector2f given_pos) : Plant(given_pos , HEALTH , file_path){
        
    }
private:
    const int drop_rate = 10;     //default value
    const int HEALTH = 10;       //default value
    const string file_path = "";
};


class Pea : public Plant{
public:
    Pea(Vector2f given_pos) : Plant(given_pos , HEALTH , file_path){};
private:
    const int HEALTH = 10;
    const string file_path = "";
};

class IcePea : public Plant{
public:
    IcePea(Vector2f given_pos) : Plant(given_pos , HEALTH , file_path){};
private:
    const int HEALTH = 10;
    const string file_path = "";
};

class Walnut : public Plant{
public:
    Walnut(Vector2f given_pos) : Plant(given_pos , HEALTH , file_path){};
private:
    const int HEALTH = 10;
    const string file_path = "";
};


