#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "System.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string bg_pic_path = "./src/pics/background.png";


void System::Run(){
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<int> dis(100, 900);
    RenderWindow window(VideoMode(Window_lenght , Window_hight), "PlantsVsZombies");
    Texture bg_texture;
    Sprite bg_sprite;
    int random_number;
    if(!bg_texture.loadFromFile(bg_pic_path))
    {
        cout << "Cannot load the background picture";
        abort();
    }
    bg_sprite.setTexture(bg_texture);

    Clock clock;
    Time interval = milliseconds(2000); 
    Time elapsedTime = Time::Zero;

    while(window.isOpen()){
        window.clear();
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed){
                
                for (auto s : suns)
                {
                    
                    Vector2i Mouse_position = sf::Mouse::getPosition(window);
                    // sf::Vector2f worldMousePos = window.mapPixelToCoords(Mouse_position);
                    s->isClicked(Mouse_position);
                }
            
            }
        }
        elapsedTime += clock.restart();
        if (elapsedTime >= interval)
        {
            random_number = dis(gen);
            MakeSun(random_number);
            elapsedTime = Time::Zero;
        }
        window.draw(bg_sprite);
        for (auto s : suns){
            s->MoveDown();
            s->Update();
            window.draw(s->get_sprite());
        }
        
        
        
        Updater();
        
        window.display();        
    }
}


void System:: MakeSun(int random_number){
        Vector2f p = {random_number , 0} ;
        Sun* new_sun = new Sun(p , &money);
        suns.push_back(new_sun);    
}

void System::Updater(){
    vector<Sun*> trashs;
    for(auto s : suns){
        if((s->get_sprite().getPosition().y >= Window_hight) || (s->get_sprite().getPosition().y <= 0) )
            trashs.push_back(s);
    }
    for (auto z : trashs){
        suns.erase(remove(suns.begin() , suns.end() , z),suns.end());
        delete z;
    }   
}




