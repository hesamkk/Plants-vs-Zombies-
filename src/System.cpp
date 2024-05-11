#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "System.hpp"
#include "Global.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string bg_pic_path = "./src/pics/background.png";


void System::Run(){
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<int> dis(100, 900);
    RenderWindow window(VideoMode(Window_lenght , Window_hight), "PlantsVsZombies");
    Vector2f PositonOfPeaCard = {10.0 , 10.0};
    Pea_Card pea_card (PositonOfPeaCard);
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
    Time ShotRate = milliseconds(1000);
    Time DeltaTime_SunDrop = Time::Zero;
    Time DeltaTime_ZombieSpawn = Time::Zero;
    Time DeltaTime_GiantSpawn = Time::Zero;
    Time DeltaTime_Shot = Time::Zero;
    Time DeltaTime_Shot_Saver = Time::Zero;
    Time DeltaTime= Time::Zero;
    bool mouseDown = false;
    bool taged_pea_card = false;
    while(window.isOpen()){
        window.clear();
        Event event;
        Vector2i Mouse_position = Mouse::getPosition(window);
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed){
                mouseDown = true;
                if (pea_card.is_tagged(Mouse_position))
                    taged_pea_card = true;
                for (auto s : suns)
                {
                    s->isClicked(Mouse_position);
                }
            }
            else if (event.type == Event::MouseButtonReleased){
                mouseDown = false;
                if(taged_pea_card && money >= 100 && pea_card.get_avalablity())
                    if(NewPlant(Mouse_position))
                        pea_card.Used();
                taged_pea_card = false;
                pea_card.RePosition();
            }
                
        }
        if (mouseDown && taged_pea_card)
            pea_card.Drag(Mouse_position);    
        DeltaTime = clock.restart();
        DeltaTime_SunDrop += DeltaTime;
        DeltaTime_ZombieSpawn += DeltaTime;
        DeltaTime_GiantSpawn += DeltaTime;
        DeltaTime_Shot += DeltaTime;
        random_number = dis(gen);
        if (DeltaTime_SunDrop >= interval)
        {
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

        
        pea_card.Update();
        window.draw(bg_sprite);
        window.draw(pea_card.get_sprite());
        vector<Plant*> attackingPlants;

        for (auto p : plants){
            if(p->IsThereZombie(zombies))
            {
                p->status_setter(1);
                attackingPlants.push_back(p);
            }
            else
                p->status_setter(0);
            p->Updater();
            window.draw(p->sprite);
        }

        DeltaTime_Shot_Saver = DeltaTime_Shot;
        for (auto p : attackingPlants){
            DeltaTime_Shot = DeltaTime_Shot_Saver;
            if(DeltaTime_Shot >= ShotRate){
                MakeShot(p->sprite.getPosition());
                DeltaTime_Shot = Time::Zero;
            }
        }

        for (auto z : zombies){
            z->Mover();
            z->Update();
            z->NextFrame();
            window.draw(z->get_sprite());
        }
        for(auto sh : shots){
            sh->Move();
            window.draw(sh->get_sprite());
        }
        for (auto s : suns){
            s->MoveUpDown();
            s->Update();
            window.draw(s->get_sprite());
        }

        
        
        // cout << "MousePosition: " << Mouse_position.x << ' ' << Mouse_position.y << endl;
        Updater();
        Handler();
        
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
    vector<Shot*> trashot;
    for(auto s : suns){
        if((s->get_sprite().getPosition().y >= Window_hight) || (s->get_sprite().getPosition().y <= -120) )
            trashs.push_back(s);
    }
    for (auto s_ : trashs){
        suns.erase(remove(suns.begin() , suns.end() , s_),suns.end());
        delete s_;
    } 
    for (auto sh : shots){
        if(sh->get_sprite().getPosition().x >= Window_lenght)
            trashot.push_back(sh);
    }
    for (auto sh_ : trashot){
        shots.erase(remove(shots.begin() , shots.end() , sh_),shots.end());
        delete sh_;
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

bool System::IsInTheWindow(Vector2i position){
    if ((position.x < 0)||(position.y < 0)||(position.x > Window_lenght)||(position.y > Window_hight))
    {
        return false;
    }
    else
        return true;
}

bool System::NewPlant(Vector2i Mouse_position){
    int xP = -1;
    int yP= -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x){
        if(Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y){
        if(Mouse_position.y > j)
            yP = j;
    }
    cout << "X: " << xP << " Y: " << yP << endl;
    for (auto p : plants){
        if(p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1){
        Vector2f position = {xP , yP};
        Pea* new_pea = new Pea(position , 10 , 10 );
        plants.push_back(new_pea);
        money -= 100;
        return true;
    }
    else 
        return false;
}

void System::MakeShot(Vector2f Plant_position){
    Vector2f p_ = {Plant_position.x+20 , Plant_position.y};
    Shot* new_shot = new Shot(p_);
    shots.push_back(new_shot);    
}

void System::Handler(){
    vector<Zombie*> trashz;
    vector<Shot*> trashot;
    for(auto z : zombies){
        for(auto s: shots){
            if((int)s->get_sprite().getPosition().x == (int)z->get_x() &&  (s->get_sprite().getPosition().y == z->get_y()+60 || s->get_sprite().getPosition().y == z->get_y()+50))
            {
                trashz.push_back(z);
                trashot.push_back(s);
            }
        }
    }
    for (auto z_ : trashz){
        zombies.erase(remove(zombies.begin() , zombies.end() , z_),zombies.end());
        delete z_;        
    }
    for (auto s_ : trashot){
        shots.erase(remove(shots.begin() , shots.end() , s_),shots.end());
        delete s_;
    }
}

