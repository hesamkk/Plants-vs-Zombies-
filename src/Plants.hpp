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
    SunFlower(Vector2f given_pos, int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    }
private:
    const int drop_rate = -1;     //default value
    int HEALTH = -1;       //default value
    const string file_path = "";
};


class Pea : public Plant{
public:
    Pea(Vector2f given_pos , int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    };
private:
    int HEALTH = -1;
    const string file_path = "";
};

class IcePea : public Plant{
public:
    IcePea(Vector2f given_pos , int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    };
private:
    int HEALTH = -1;
    const string file_path = "";
};

class Walnut : public Plant{
public:
    Walnut(Vector2f given_pos , int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    };
private:
    int HEALTH = -1;
    const string file_path = "";
};

class Melon : public Plant{
public:
    Melon(Vector2f given_pos , int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    };
private:
    int HEALTH = -1;
    const string file_path = "";
};


