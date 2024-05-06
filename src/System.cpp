#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "System.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string bg_pic_path = "./src/pics/background.png";

void System::Run(){
    RenderWindow window(VideoMode(1000 , 425), "PlantsVsZombies");
    Texture bg_texture;
    Sprite bg_sprite;
    if(!bg_texture.loadFromFile(bg_pic_path))
    {
        cout << "Cannot load the background picture";
        abort();
    }
    bg_sprite.setTexture(bg_texture);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(bg_sprite);
        window.display();        
    }
}


