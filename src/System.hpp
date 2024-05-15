#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "Global.hpp"

using namespace std;
using namespace sf;
const int Window_hight = 425;
const int Window_lenght = 1000;
const int Y_array_of_zombies[5] = {0 , 70 , 140 , 210 , 280};
const int Possible_Plant_x[9] = {180 , 240 , 295 , 355 , 405 , 470 , 530 , 580 , 635};
const int Possible_Plant_Y[5] = {50 , 120, 190, 260 , 330};


class System{
public:
    void Handler();
    void Music();
    void Run();
    void RenderBG();
    void MakeZombie(const float& s, const float& b, const float& c, const int r);
    void MakeGiant(const float& s , const float& b , const float& c , const int r);
    void Updater();
    void MakeSun(const Vector2f& p,bool IsFalling);
    bool IsInTheWindow(const Vector2i& position);
    bool NewPea(const Vector2i& m_p, const int health);
    bool NewWalnut(const Vector2i& m_p, const int health);
    bool NewSunFlower(const Vector2i& m_p, const int health);
    bool NewIcePea(const Vector2i& m_p, const int health);
    bool NewMelon(const Vector2i& m_p, const int health);
    void MakeShot(const Vector2f& p_p);
    void MakeIceShot(const Vector2f& m_p);
    void MakeMelonShot(const Vector2f& m_p , int l);
    vector<string> SettingsReader();
private:
    vector <Plant*> plants;
    vector <Zombie*> zombies;
    vector <Sun*> suns;
    vector <Shot*> shots;
    vector <IceShot*> iceShots;
    vector <MelonShot*> melonshots;
    int field_width;
    int field_hight;
    int money = 0;
    const string bg_file_path = "";
};