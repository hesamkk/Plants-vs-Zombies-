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
    Time NormalZombieSpawnRate = milliseconds(5000);
    Time GiantSpawnRate = milliseconds(7000);
    
    Time DeltaTime_SunDrop = Time::Zero;
    Time DeltaTime_ZombieSpawn = Time::Zero;
    Time DeltaTime_GiantSpawn = Time::Zero;
    Time DeltaTime= Time::Zero;

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
                    s->isClicked(Mouse_position);
                    
                }
            
            }
        }

        DeltaTime = clock.restart();
        DeltaTime_SunDrop += DeltaTime;
        DeltaTime_ZombieSpawn += DeltaTime;
        DeltaTime_GiantSpawn += DeltaTime;
        if (DeltaTime_SunDrop >= interval)
        {
            random_number = dis(gen);
            MakeSun(random_number);
            DeltaTime_SunDrop -= interval;
        }
        if (DeltaTime_ZombieSpawn >= NormalZombieSpawnRate){
            MakeZombie(0.05, 10 , 10 , random_number);    //Needs to be changed...
            DeltaTime_ZombieSpawn -= NormalZombieSpawnRate;
        }
        if (DeltaTime_GiantSpawn >= GiantSpawnRate){
            MakeGiant(0.15 , 100 , 100 , random_number);
            DeltaTime_GiantSpawn -= GiantSpawnRate;
        }

        

        window.draw(bg_sprite);

        for (auto z : zombies){
            z->Mover();
            z->Update();
            z->NextFrame();
            window.draw(z->get_sprite());
        }
        for (auto s : suns){
            s->MoveUpDown();
            s->Update();
            window.draw(s->get_sprite());
        }
        
        
        
        Updater();
        
        window.display();        
    }
}


void System:: MakeSun(int random_number){
        Vector2f p = {random_number , -100} ;
        Sun* new_sun = new Sun(p , &money);
        suns.push_back(new_sun);    
}

void System::Updater(){
    vector<Sun*> trashs;
    for(auto s : suns){
        if((s->get_sprite().getPosition().y >= Window_hight) || (s->get_sprite().getPosition().y <= -120) )
            trashs.push_back(s);
    }
    for (auto s_ : trashs){
        suns.erase(remove(suns.begin() , suns.end() , s_),suns.end());
        delete s_;
    } 
}

void System::MakeZombie(float speed_, float health_, float damage_,int random_number){
    Vector2f p_ = {1000 , Y_array_of_zombies[random_number%5]};
    Zombie* new_zombie = new Zombie(p_ , health_ , speed_ , damage_ , 0);
    zombies.push_back(new_zombie);
}

void System::MakeGiant(float speed_, float health_, float damage_,int random_number){
    Vector2f p_ = {1000 , Y_array_of_zombies[random_number%5]};
    Zombie* new_zombie = new Zombie(p_ , health_ , speed_ , damage_ , 1);
    zombies.push_back(new_zombie);
}


