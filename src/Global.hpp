#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Sun{
public:
    Sun(Vector2f p){
        if(!texture.loadFromFile(file_path))
            abort();
        // rect making
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        pos = p;
    }
    ~Sun();
    void Render();
private:
    const string file_path = "";
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
};

class Card{
public:
    Card(Vector2f given_pos ,  string file_path){
        if(!texture.loadFromFile(file_path))
            abort();
        // rect making
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        pos = given_pos;
    }
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
};

class SunFlower_Card : public Card {
public:
    SunFlower_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_toggle();
    void Update();
private:
    const string file_path = "";
};

class Walnut_Card : public Card {
public:
    Walnut_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_toggle();
    void Update();
private:
    const string file_path = "";
};

class Pea_Card : public Card {
public:
    Pea_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_toggle();
    void Update();
private:
    const string file_path = "";
};

class IcePea_Card : public Card {
public:
    IcePea_Card(Vector2f given_pos) : Card(given_pos , file_path){

    }
    void is_toggle();
    void Update();
private:
    const string file_path = "";
};