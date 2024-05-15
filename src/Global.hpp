#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Sun{
public:
    Sun(Vector2f p , int* m){
        if(!texture.loadFromFile(file_path))
            abort();
        sprite.setTexture(texture);
        sprite.setScale(0.2 , 0.2);
        pos = p;
        sprite.setPosition(pos);
        money = m;
    }
    void revealing_the_bounds(){Sprite_Bounds = sprite.getGlobalBounds();};
    ~Sun();
    void MoveUpDown();
    bool isClicked(Vector2i Mouse_position);
    void Update();
    Sprite get_sprite() { return sprite; }
    void set_falling(bool given){falling = given;}
private:
    const string file_path = "./src/pics/Sun.png";
    Texture texture;
    Sprite sprite;
    Vector2f pos;
    int *money;
    FloatRect Sprite_Bounds ;
    float dSpeed = 0.3;
    bool falling = true;
    int falling_count = 0;
};

class Card{
public:
    Card(Vector2f given_pos ,  string file_path){
        if(!texture.loadFromFile(file_path))
            abort();
        rect.left = 0;
        rect.top = 0;
        rect.height = 90;
        rect.width = 63;
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setScale(1, 1);
        pos = given_pos;

    }
    Sprite get_sprite() { return sprite; }
    Vector2f pos;
    void Update();
    void Drag(Vector2i m_p);
    FloatRect Sprite_Bounds ;
    void revealing_the_bounds(){Sprite_Bounds = sprite.getGlobalBounds();};
    bool get_avalablity() { return Avalablity; }
    void Used();
    bool is_tagged(Vector2i m_p);
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    bool Avalablity = true;
    Clock clock;
    Time cool_down_time = milliseconds(7000); //needs to be changed
    Time DeltaTime_NextFrame = Time::Zero;
};

class SunFlower_Card : public Card {
public:
    SunFlower_Card(Vector2f given_pos) : Card(given_pos , "./src/pics/SunFlower-Card-New.png"){

    }
    void RePosition();
private:
};

class Walnut_Card : public Card {
public:
    Walnut_Card(Vector2f given_pos) : Card(given_pos , "./src/pics/Walnut-Car-New.png"){

    }
    void RePosition();
private:
    
};

class Pea_Card : public Card {
public:
    Pea_Card(Vector2f given_pos) : Card(given_pos ,"./src/pics/Pea-Car-New.png"){

    }
    void RePosition();
private:
    
};

class IcePea_Card : public Card {
public:
    IcePea_Card(Vector2f given_pos) : Card(given_pos , "./src/pics/IcePea-Card-New.png"){

    }
    void RePosition();
private:
};

class Melon_Card : public Card {
public:
    Melon_Card(Vector2f given_pos) : Card(given_pos , "./src/pics/Melon-Card-New.png"){

    }
    void RePosition();
private:
};

class Shot{
public:
    Shot(Vector2f given_pos){
        pos = given_pos;
        if(!texture.loadFromFile(file_path))
            abort();
        rect.left = 0;
        rect.top = 0;
        rect.height = 29;
        rect.width = 29;
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
    }
    ~Shot();
    void Move();
    Sprite get_sprite(){ return sprite; }
    IntRect get_rect(){ return rect; }
private:
    const string file_path = "./src/pics/Pea-Shot-NBG.png";
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    IntRect rect;
};

class IceShot{
public:
    IceShot(Vector2f given_pos){//?
        pos = given_pos;
        if(!texture.loadFromFile(file_path))
            abort();
        rect.left = 0;
        rect.top = 0;
        rect.height = 29;
        rect.width = 29;
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
    }
    ~IceShot();
    void Move();
    Sprite get_sprite(){ return sprite; }
    IntRect get_rect(){ return rect; }
private:
    const string file_path = "./src/pics/IcePea-Shot.png";
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    IntRect rect;
};

class MelonShot{
public:
    MelonShot(Vector2f given_pos , int l){
        pos = given_pos;
        if(!texture.loadFromFile(file_path))
            abort();
        rect.left = 0;
        rect.top = 0;
        rect.height = 29;
        rect.width = 29;
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
        line_Y = l;
    }
    ~MelonShot();
    void Move();
    
    // void Render();
    Sprite get_sprite(){ return sprite; }
    IntRect get_rect(){ return rect; }
private:
    const string file_path = "./src/pics/melon_shot-removebg-preview.png";
    Vector2f pos;
    Sprite sprite;
    Texture texture;
    IntRect rect;
    int line_Y ;
    
};

class DeathScreen{
public:
    DeathScreen(){
        if(!texture.loadFromFile(file_path))
            abort();
        sprite.setTexture(texture);
        rect.top = 0 ;
        rect.left = 0 ;
        rect.height = 455;
        rect.width = 548;
        sprite.setTextureRect(rect);
        sprite.setScale(0.9 , 0.9);
        sprite.setPosition(pos);
        }
    ~DeathScreen(){}
    Sprite get_sprite(){ return sprite; }
private:
    const string file_path = "./src/pics/DS.png";
    Sprite sprite;
    Vector2f pos = {300 , 0};
    Texture texture;
    IntRect rect;
};

class CrazyDave{
public:
    CrazyDave(){
        if(!texture.loadFromFile(file_path))
            abort();
        sprite.setTexture(texture);
        rect.top = 0 ;
        rect.left = 0 ;
        rect.height = 400;
        rect.width = 248;
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
        }
    ~CrazyDave(){}
    Sprite get_sprite(){ return sprite; }
private:
    const string file_path = "./src/pics/CrazyDave.png";
    Sprite sprite;
    Vector2f pos = {10 , 50};
    Texture texture;
    IntRect rect;
};
