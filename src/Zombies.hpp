#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Zombie{
public:
    Zombie(Vector2f given_pos , float h, float s, float d , int t){
        health = h;
        speed = s;
        damage = d;
        type = t;
        pos = given_pos;
        if (type == 0){
            if(!texture.loadFromFile(nz_file_path)){
                cout << nz_file_path << endl;
                cout << "I cannot open the file!" << endl;
                abort();
            }
            rect.top =0;
            rect.left =0;
            rect.height = 250;
            rect.width = 200;
        }
        else{
            if(!texture.loadFromFile(giant_file_path)){
                cout << giant_file_path << endl;
                cout << "I cannot open the file!" << endl;
                abort();
            } 
            rect.top =0;
            rect.left =0;
            rect.height = 250;
            rect.width = 242;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setScale(0.5 , 0.5);
        clock.restart();
    }
    Zombie(){};
    ~Zombie();
    void Render();
    void Update();
    void Mover();
    void NextFrame();
    void Damage(const int& d);
    Sprite get_sprite();
    IntRect get_rect(){ return rect; }
    float get_y(){ return sprite.getPosition().y; }
    float get_x(){ return sprite.getPosition().x; }
    bool Is_Shot(Vector2i pea_position);
    bool Is_eating(Vector2f pea_position);
    void revealing_the_bounds(){Sprite_Bounds = sprite.getGlobalBounds();};
    void Attack();
    void Freeze();
    bool IsCross();
    float get_damage() { return damage; }
    float get_health() { return health; }
    int get_status() { return status; }
private:
    float health;
    float speed;
    float damage;
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f pos;
    Clock clock;
    Time frame_changeTime = milliseconds(100);
    Time freeze_time = milliseconds(3000);
    Time DeltaTime = Time::Zero;
    Time DeltaTime_NextFrame = Time::Zero;
    Time DeltaTime_Freeze = Time::Zero;
    int status = 0;      // 0 is idle 1 is attacking
    int type;
    const string nz_file_path = "./src/pics/ZombieSP.png";
    const string giant_file_path ="./src/pics/GiantSP.png";
    FloatRect Sprite_Bounds ;
};

