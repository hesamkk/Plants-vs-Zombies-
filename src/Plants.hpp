#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Zombies.hpp"

using namespace std;
using namespace sf;

class Plant{
public:
    Plant(Vector2f given_pos, int h, const string texture_adr){
        pos = given_pos;
        health = h;
        if(!texture.loadFromFile(texture_adr))
        {
            abort();
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setScale(1.7, 1.7);
        sprite.setPosition(pos);
        cout << "MADE yohooo!" << endl;
    }
    ~Plant();
    void Render();
    void Updater();
    bool IsThereZombie(const vector<Zombie*> zombies);
    bool IsTouchingMouse(Vector2i m_p);
    void revealing_the_bounds(){Sprite_Bounds = sprite.getGlobalBounds();};
    void status_setter(int given_status ){ status = given_status; }
    int get_status(){ return status; }
    float get_health() { return health; }
    void Damage(float dam) { health -= dam; }
    virtual void NextFrame(){ };
    void ChangeTheAnimation(string new_file_path){
        cout << "Texture changed to: " << new_file_path << endl;
        if(!texture.loadFromFile(new_file_path))
            abort();
    };
    IntRect rect;
    Sprite sprite;
private:
    Texture texture;
    FloatRect Sprite_Bounds;
    Vector2f pos;
    int health;
    int status = 0; //0 for Normal  -   1 for Attack
};


class SunFlower : public Plant{
public:
    SunFlower(Vector2f given_pos, int h) : Plant(given_pos , h , file_path){
        HEALTH = h;
    }
    const string file_path = "";
    void NextFrame();
private:
    const int drop_rate = -1;     //default value
    int HEALTH = -1;       //default value
    
};


class Pea : public Plant{
public:
    Pea(Vector2f given_pos , int h, int s, string file_path = "./src/pics/Pea-Attack-NBG.png" ) : Plant(given_pos , h , file_path){
        HEALTH = h;
        SHOT_RATE = s;
        rectMaker();
        this -> file_path = file_path;
    };
    
    void rectMaker();
    void NextFrame();

private:
    Clock clock;
    Time frame_changeTime = milliseconds(200);
    Time DeltaTime_NextFrame = Time::Zero;
    int HEALTH = -1;
    int SHOT_RATE = -1;
    string file_path;
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
    Walnut(Vector2f given_pos , int h) : Plant(given_pos , h , "./src/pics/Pea-Attack-NBG.png" ){
        HEALTH = h;
        rectMaker();
    };
    void rectMaker();
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


