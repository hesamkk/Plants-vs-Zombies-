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
private:
    const string file_path = "./src/pics/Sun.png";
    Texture texture;
    Sprite sprite;
    Vector2f pos;
    int *money;
    FloatRect Sprite_Bounds ;
    float dSpeed = 0.3;
};

class Card{
public:
    Card(Vector2f given_pos ,  string file_path){
        if(!texture.loadFromFile(file_path))
            abort();
        rect.left = 0;
        rect.top = 0;
        rect.height = 27;
        rect.width = 36;
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setScale(3, 3);
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
    SunFlower_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_tagged();
private:
    const string file_path = "";
};

class Walnut_Card : public Card {
public:
    Walnut_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_tagged(Vector2i m_p);
private:
    const string file_path = "";
};

class Pea_Card : public Card {
public:
    Pea_Card(Vector2f given_pos) : Card(given_pos ,"./src/pics/PeaCard.png"){

    }
    void RePosition();
    bool is_tagged(Vector2i m_p);
    const string file_path = "./src/pics/Card-Pea.jpeg";
private:
    
};

class IcePea_Card : public Card {
public:
    IcePea_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_tagged();
private:
    const string file_path = "";
};

class Shot{
public:
    Shot(Vector2f given_pos){
        pos = given_pos;
    }
    void Move();
    void Render();
private:
    const string file_path = "";
    Vector2f pos;
};

class IceShot{
public:
    IceShot(Vector2f given_pos){
        pos = given_pos;
    }
    void Move();
    void Render();
private:
    const string file_path = "";
    Vector2f pos;
};

class MelonShot{
public:
    MelonShot(Vector2f given_pos){
        pos = given_pos;
    }
    void Move();
    void Render();
private:
    const string file_path = "";
    Vector2f pos;
};

