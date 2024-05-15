#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include "Plants.hpp"
#include "Zombies.hpp"
#include "System.hpp"
#include "Global.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

const string bg_pic_path = "./src/pics/background.png";
const Vector2f PositonOfPeaCard = {10.0, 10.0};
const Vector2f PositonOfWalNutCard = {10.0, 100.0};
const Vector2f PositonOfSunFlowerCard = {10.0, 190.0};
const Vector2f PositonOfIcePeaCard = {10.0, 280.0};
const Vector2f PositonOfMelonCard = {75.0, 10.0};

void System::Run()
{
    vector<string> Settings = SettingsReader();
    sf::Music music;
    sf::Music victory_theme;
    sf::Music defeat_theme;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(100, 900);
    RenderWindow window(VideoMode(Window_lenght, Window_hight), "PlantsVsZombies");
    DeathScreen death_screen;
    CrazyDave crazy_bro;
    Pea_Card pea_card(PositonOfPeaCard);
    Walnut_Card wal_card(PositonOfWalNutCard);
    SunFlower_Card sunf_card(PositonOfSunFlowerCard);
    IcePea_Card ipe_card(PositonOfIcePeaCard);
    Melon_Card mel_card(PositonOfMelonCard);
    Texture bg_texture;
    Sprite bg_sprite;
    int random_number;
    if (!bg_texture.loadFromFile(bg_pic_path))
    {
        cout << "Cannot load the background picture";
        abort();
    }
    bg_sprite.setTexture(bg_texture);
    Font font;
    if (!font.loadFromFile("./Speedy.ttf"))
    {
        cout << "Cannot load font file";
        abort();
    }
    if (!music.openFromFile("./src/musics/music.flac"))
    {
        cout << "Cannot load music";
        abort();
    }
    if (!victory_theme.openFromFile("./src/musics/Victory.flac"))
    {
        cout << "Cannot load music";
        abort();
    }
    if (!defeat_theme.openFromFile("./src/musics/Defeat.flac"))
    {
        cout << "Cannot load music";
        abort();
    }
    music.setLoop(true);
    Clock clock;
    Text DaveText;
    Text MoneyText;
    const float NormalZombieSpeed = stof(Settings[8]);
    const float NormalZombieHealth = stof(Settings[9]);
    const float NormalZombieDamage = stof(Settings[10]);
    const float GiantSpeed = stof(Settings[11]);
    const float GiantHealth = stof(Settings[12]);
    const float GiantDamage = stof(Settings[13]);
    const int SunFlowerHealth = stoi(Settings[14]);
    const int WalnutHealth = stoi(Settings[15]);
    const int PeaHealth = stoi(Settings[16]);
    const int IcePeaHealth = stoi(Settings[17]);
    const Time SunfallingRate = milliseconds(stoi(Settings[0]));
    const Time NormalZombieSpawnRate = milliseconds(stoi(Settings[2]));
    const Time GiantSpawnRate = milliseconds(stoi(Settings[3]));
    const Time ShotRate = milliseconds(stoi(Settings[4]));
    const Time ZombieHitRate = milliseconds(stoi(Settings[7]));
    const Time SunSpawnRate = milliseconds(stoi(Settings[6]));
    const Time IceShotRate = milliseconds(stoi(Settings[5]));
    const Time win_time = milliseconds(stoi(Settings[1]));
    const Time MelonShotRate = milliseconds(stoi(Settings[18]));

    Time DeltaTime_SunDrop = Time::Zero;
    Time DeltaTime_ZombieSpawn = Time::Zero;
    Time DeltaTime_GiantSpawn = Time::Zero;
    Time DeltaTime_Shot = Time::Zero;
    Time DeltaTime_Shot_Saver = Time::Zero;
    Time DeltaTime_IceShot_Saver = Time::Zero;
    Time DeltaTime_ZombieHit = Time::Zero;
    Time DeltaTime_SunSpawn = Time::Zero;
    Time DeltaTime_IceShot = Time::Zero;
    Time DeltaTime_MelonShot = Time::Zero;
    Time DeltaTime_MelonShot_Saver = Time::Zero;
    Time DeltaTime_win = Time::Zero;
    Time DeltaTime = Time::Zero;
    bool mouseDown = false;
    bool taged_pea_card = false;
    bool taged_wal_card = false;
    bool taged_sunf_card = false;
    bool taged_ipe_card = false;
    bool taged_mel_card = false;
    bool flag = false;
    DaveText.setFont(font);
    MoneyText.setFont(font);
    DaveText.setString("You won my brother... Grrrr!");
    DaveText.setCharacterSize(24);
    DaveText.setFillColor(sf::Color::White);
    DaveText.setPosition(230, 150);
    MoneyText.setString("0");
    MoneyText.setCharacterSize(20);
    MoneyText.setFillColor(sf::Color::Black);
    MoneyText.setStyle(Text::Bold);
    MoneyText.setPosition(945, 70);
    music.play();
    while (window.isOpen())
    {
        window.clear();
        Event event;
        Vector2i Mouse_position = Mouse::getPosition(window);
        for (auto z : zombies)
        {
            if (z->IsCross())
            {
                music.stop();
                defeat_theme.play();
                Event event_;
                while (true)
                {
                    window.clear();
                    window.draw(bg_sprite);
                    window.draw(death_screen.get_sprite());
                    while (window.pollEvent(event_))
                    {
                        if (event_.type == Event::Closed)
                        {
                            window.close();
                            return;
                        }
                    }
                    window.display();
                }
            }
        }
        if (DeltaTime_win >= win_time)
        {
            Event event_;
            music.stop();
            victory_theme.play();
            while (true)
            {
                window.clear();
                window.draw(bg_sprite);
                window.draw(crazy_bro.get_sprite());
                window.draw(DaveText);
                while (window.pollEvent(event_))
                {
                    if (event_.type == Event::Closed)
                    {
                        window.close();
                        return;
                    }
                }
                window.display();
            }
        }
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                mouseDown = true;
                if (pea_card.is_tagged(Mouse_position))
                    taged_pea_card = true;
                else if (wal_card.is_tagged(Mouse_position))
                    taged_wal_card = true;
                else if (sunf_card.is_tagged(Mouse_position))
                    taged_sunf_card = true;
                else if (ipe_card.is_tagged(Mouse_position))
                    taged_ipe_card = true;
                else if (mel_card.is_tagged(Mouse_position))
                    taged_mel_card = true;
                for (auto s : suns)
                {
                    s->isClicked(Mouse_position);
                }
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                mouseDown = false;
                if (taged_pea_card && money >= 100 && pea_card.get_avalablity())
                {
                    if (NewPea(Mouse_position, PeaHealth))
                        pea_card.Used();
                }
                else if (taged_wal_card && money >= 50 && wal_card.get_avalablity())
                {
                    if (NewWalnut(Mouse_position, WalnutHealth))
                        wal_card.Used();
                }
                else if (taged_sunf_card && money >= 50 && sunf_card.get_avalablity())
                {
                    if (NewSunFlower(Mouse_position, SunFlowerHealth))
                        sunf_card.Used();
                }
                else if (taged_ipe_card && money >= 175 && ipe_card.get_avalablity())
                {
                    if (NewIcePea(Mouse_position, IcePeaHealth))
                        ipe_card.Used();
                }
                else if (taged_mel_card && money >= 100 && mel_card.get_avalablity())
                {
                    if (NewMelon(Mouse_position, IcePeaHealth))
                        mel_card.Used();
                }
                if (taged_pea_card)
                {
                    taged_pea_card = false;
                    pea_card.RePosition();
                }
                else if (taged_wal_card)
                {
                    taged_wal_card = false;
                    wal_card.RePosition();
                }
                else if (taged_sunf_card)
                {
                    taged_sunf_card = false;
                    sunf_card.RePosition();
                }
                else if (taged_ipe_card)
                {
                    taged_ipe_card = false;
                    ipe_card.RePosition();
                }
                else if (taged_mel_card)
                {
                    taged_mel_card = false;
                    mel_card.RePosition();
                }
            }
        }
        if (mouseDown && taged_pea_card)
            pea_card.Drag(Mouse_position);
        else if (mouseDown && taged_wal_card)
            wal_card.Drag(Mouse_position);
        else if (mouseDown && taged_sunf_card)
            sunf_card.Drag(Mouse_position);
        else if (mouseDown && taged_ipe_card)
            ipe_card.Drag(Mouse_position);
        else if (mouseDown && taged_mel_card)
            mel_card.Drag(Mouse_position);

        DeltaTime = clock.restart();
        DeltaTime_SunDrop += DeltaTime;
        DeltaTime_ZombieSpawn += DeltaTime;
        DeltaTime_GiantSpawn += DeltaTime;
        DeltaTime_Shot += DeltaTime;
        DeltaTime_ZombieHit += DeltaTime;
        DeltaTime_SunSpawn += DeltaTime;
        DeltaTime_IceShot += DeltaTime;
        DeltaTime_MelonShot += DeltaTime;
        DeltaTime_win += DeltaTime;
        random_number = dis(gen);
        if (DeltaTime_SunDrop >= SunfallingRate)
        {
            Vector2f random_pos = {random_number, -100};
            MakeSun(random_pos, true);
            DeltaTime_SunDrop -= SunfallingRate;
        }
        if (DeltaTime_ZombieSpawn >= NormalZombieSpawnRate)
        {
            MakeZombie(NormalZombieSpeed, NormalZombieHealth, NormalZombieDamage, random_number);
            DeltaTime_ZombieSpawn -= NormalZombieSpawnRate;
        }
        if (DeltaTime_GiantSpawn >= GiantSpawnRate)
        {
            MakeGiant(GiantSpeed, GiantHealth, GiantDamage, random_number);
            DeltaTime_GiantSpawn -= GiantSpawnRate;
        }

        MoneyText.setString(to_string(money));
        pea_card.Update();
        wal_card.Update();
        sunf_card.Update();
        ipe_card.Update();
        mel_card.Update();
        window.draw(bg_sprite);
        window.draw(MoneyText);
        window.draw(pea_card.get_sprite());
        window.draw(wal_card.get_sprite());
        window.draw(sunf_card.get_sprite());
        window.draw(ipe_card.get_sprite());
        window.draw(mel_card.get_sprite());
        vector<Plant *> attackingPlants;
        vector<Plant *> generatingPlants;
        vector<Plant *> attackingIcyPlants;
        vector<Plant *> attackingMelonPlants;

        for (auto p : plants)
        {
            if (Pea *pea = dynamic_cast<Pea *>(p))
                if (p->IsThereZombie(zombies))
                {
                    p->status_setter(1);

                    attackingPlants.push_back(p);
                }
                else
                {
                    p->status_setter(0);
                }
        }
        for (auto p : plants)
        {
            if (IcePea *icepea = dynamic_cast<IcePea *>(p))
                if (p->IsThereZombie(zombies))
                {
                    p->status_setter(1);

                    attackingIcyPlants.push_back(p);
                }
                else
                {
                    p->status_setter(0);
                }
        }
        for (auto p : plants)
        {
            if (Melon *pea = dynamic_cast<Melon *>(p))
                if (p->IsThereZombie(zombies))
                {
                    p->status_setter(1);

                    attackingMelonPlants.push_back(p);
                }
                else
                {
                    p->status_setter(0);
                }
        }

        for (auto p : plants)
        {
            if (SunFlower *sun = dynamic_cast<SunFlower *>(p))
                generatingPlants.push_back(p);
        }
        for (auto p : plants)
        {
            p->Updater();
            window.draw(p->sprite);
        }
        DeltaTime_Shot_Saver = DeltaTime_Shot;
        for (auto p : attackingPlants)
        {
            DeltaTime_Shot = DeltaTime_Shot_Saver;
            if (DeltaTime_Shot >= ShotRate)
            {
                MakeShot(p->sprite.getPosition());
                DeltaTime_Shot = Time::Zero;
            }
        }
        DeltaTime_IceShot_Saver = DeltaTime_IceShot;
        for (auto p : attackingIcyPlants)
        {
            DeltaTime_IceShot = DeltaTime_IceShot_Saver;
            if (DeltaTime_IceShot >= IceShotRate)
            {
                MakeIceShot(p->sprite.getPosition());
                DeltaTime_IceShot = Time::Zero;
            }
        }

        DeltaTime_MelonShot_Saver = DeltaTime_MelonShot;
        for (auto p : attackingMelonPlants)
        {
            DeltaTime_MelonShot = DeltaTime_MelonShot_Saver;
            if (DeltaTime_MelonShot >= MelonShotRate)
            {
                MakeMelonShot(p->sprite.getPosition(), (p->sprite.getPosition().y - 50));
                DeltaTime_MelonShot = Time::Zero;
            }
        }

        flag = 0;
        for (auto p : generatingPlants)
        {
            if (DeltaTime_SunSpawn >= SunSpawnRate)
            {
                flag = true;
                MakeSun(p->sprite.getPosition(), false);
            }
        }
        if (flag)
            DeltaTime_SunSpawn = Time::Zero;

        for (auto p : plants)
        {
            for (auto z : zombies)
            {
                Vector2f MiddlePosition = {p->sprite.getPosition().x + p->rect.width / 2, p->sprite.getPosition().y + p->rect.height / 2};
                if (z->Is_eating(MiddlePosition))
                {
                    z->Attack();
                    if (DeltaTime_ZombieHit >= ZombieHitRate)
                    {
                        p->Damage(z->get_damage());
                    }
                }
            }
        }
        if (DeltaTime_ZombieHit >= ZombieHitRate)
            DeltaTime_ZombieHit = Time::Zero;

        Handler();
        Updater();

        for (auto z : zombies)
        {
            z->Mover();
            z->Update();
            z->NextFrame();
            window.draw(z->get_sprite());
        }
        for (auto sh : shots)
        {
            sh->Move();
            window.draw(sh->get_sprite());
        }
        for (auto is : iceShots)
        {
            is->Move();
            window.draw(is->get_sprite());
        }
        for (auto ms : melonshots)
        {
            ms->Move();
            window.draw(ms->get_sprite());
        }

        for (auto s : suns)
        {
            s->MoveUpDown();
            s->Update();
            window.draw(s->get_sprite());
        }

        window.display();
    }
}

void System::MakeSun(const Vector2f &p, bool IsFalling)
{
    Sun *new_sun = new Sun(p, &money);
    new_sun->set_falling(IsFalling);
    suns.push_back(new_sun);
}

void System::Updater()
{
    vector<Sun *> trashs;
    vector<Shot *> trashot;
    vector<Plant *> trashp;
    vector<Zombie *> trashz;
    vector<MelonShot *> trashm;
    for (auto s : suns)
    {
        if ((s->get_sprite().getPosition().y >= Window_hight) || (s->get_sprite().getPosition().y <= -120))
            trashs.push_back(s);
    }
    for (auto s_ : trashs)
    {
        suns.erase(remove(suns.begin(), suns.end(), s_), suns.end());
        delete s_;
    }
    for (auto sh : shots)
    {
        if (sh->get_sprite().getPosition().x >= Window_lenght)
            trashot.push_back(sh);
    }
    for (auto sh_ : trashot)
    {
        shots.erase(remove(shots.begin(), shots.end(), sh_), shots.end());
        delete sh_;
    }
    for (auto p : plants)
    {
        if (p->get_health() <= 0)
            trashp.push_back(p);
    }
    for (auto p_ : trashp)
    {
        plants.erase(remove(plants.begin(), plants.end(), p_), plants.end());
        delete p_;
    }
    for (auto z : zombies)
    {
        if (z->get_health() <= 0)
            trashz.push_back(z);
    }
    for (auto z_ : trashz)
    {
        zombies.erase(remove(zombies.begin(), zombies.end(), z_), zombies.end());
        delete z_;
    }
    for (auto ms : melonshots)
    {
        if ((ms->get_sprite().getPosition().y >= Window_hight) || (ms->get_sprite().getPosition().y <= -120) || (ms->get_sprite().getPosition().x >= Window_lenght))
            trashm.push_back(ms);
    }
    for (auto ms_ : trashm)
    {
        melonshots.erase(remove(melonshots.begin(), melonshots.end(), ms_), melonshots.end());
        delete ms_;
    }
}

void System::MakeZombie(const float &speed_, const float &health_, const float &damage_, const int random_number)
{
    Vector2f p_ = {1000, Y_array_of_zombies[random_number % 5]};
    Zombie *new_zombie = new Zombie(p_, health_, speed_, damage_, 0);
    zombies.push_back(new_zombie);
}

void System::MakeGiant(const float &speed_, const float &health_, const float &damage_, const int random_number)
{
    Vector2f p_ = {1000, Y_array_of_zombies[random_number % 5]};
    Zombie *new_zombie = new Zombie(p_, health_, speed_, damage_, 1);
    zombies.push_back(new_zombie);
}

bool System::IsInTheWindow(const Vector2i &position)
{
    if ((position.x < 0) || (position.y < 0) || (position.x > Window_lenght) || (position.y > Window_hight))
    {
        return false;
    }
    else
        return true;
}

bool System::NewPea(const Vector2i &Mouse_position, const int health)
{
    int xP = -1;
    int yP = -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x)
    {
        if (Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y)
    {
        if (Mouse_position.y > j)
            yP = j;
    }
    for (auto p : plants)
    {
        if (p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1)
    {
        Vector2f position = {xP, yP};
        Pea *new_pea = new Pea(position, 100, 100);
        plants.push_back(new_pea);
        money -= 100;
        return true;
    }
    else
        return false;
}

void System::MakeShot(const Vector2f &Plant_position)
{
    Vector2f p_ = {Plant_position.x + 20, Plant_position.y + 5};
    Shot *new_shot = new Shot(p_);
    shots.push_back(new_shot);
}

void System::Handler()
{
    vector<Shot *> trashot;
    vector<IceShot *> trashi;
    vector<MelonShot *> trashm;
    for (auto s : shots)
    {
        for (auto z : zombies)
        {
            if (z->Is_Shot(Vector2i(s->get_sprite().getPosition())))
            {
                z->Damage(20);
                trashot.push_back(s);
                break;
            }
        }
    }
    for (auto s : iceShots)
    {
        for (auto z : zombies)
        {
            if (z->Is_Shot(Vector2i(s->get_sprite().getPosition())))
            {
                z->Damage(20);
                z->Freeze();
                trashi.push_back(s);
                break;
            }
        }
    }
    for (auto s : melonshots)
    {
        for (auto z : zombies)
        {
            if (z->Is_Shot(Vector2i(s->get_sprite().getPosition())) && z->get_y() == s->get_lineY())
            {
                z->Damage(40);
                trashm.push_back(s);
                break;
            }
        }
    }

    for (auto s_ : trashot)
    {
        shots.erase(remove(shots.begin(), shots.end(), s_), shots.end());
        delete s_;
    }
    for (auto s_ : trashi)
    {
        iceShots.erase(remove(iceShots.begin(), iceShots.end(), s_), iceShots.end());
        delete s_;
    }
    for (auto s_ : trashm)
    {
        melonshots.erase(remove(melonshots.begin(), melonshots.end(), s_), melonshots.end());
        delete s_;
    }
}

bool System::NewWalnut(const Vector2i &Mouse_position, const int health)
{
    int xP = -1;
    int yP = -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x)
    {
        if (Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y)
    {
        if (Mouse_position.y > j)
            yP = j;
    }
    for (auto p : plants)
    {
        if (p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1)
    {
        Vector2f position = {xP, yP};
        Walnut *new_walnut = new Walnut(position, 500);
        plants.push_back(new_walnut);
        money -= 50;
        return true;
    }
    else
        return false;
}

bool System::NewSunFlower(const Vector2i &Mouse_position, const int health)
{
    int xP = -1;
    int yP = -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x)
    {
        if (Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y)
    {
        if (Mouse_position.y > j)
            yP = j;
    }
    for (auto p : plants)
    {
        if (p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1)
    {
        Vector2f position = {xP, yP};
        SunFlower *new_sunflower = new SunFlower(position, 500);
        plants.push_back(new_sunflower);
        money -= 50;
        return true;
    }
    else
        return false;
}

bool System::NewIcePea(const Vector2i &Mouse_position, const int health)
{
    int xP = -1;
    int yP = -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x)
    {
        if (Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y)
    {
        if (Mouse_position.y > j)
            yP = j;
    }
    for (auto p : plants)
    {
        if (p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1)
    {
        Vector2f position = {xP, yP};
        IcePea *new_icepea = new IcePea(position, 500);
        plants.push_back(new_icepea);
        money -= 175;
        return true;
    }
    else
        return false;
}

bool System::NewMelon(const Vector2i &Mouse_position, const int health)
{
    int xP = -1;
    int yP = -1;
    const int area_X_border = 710;
    for (int i : Possible_Plant_x)
    {
        if (Mouse_position.x > i && Mouse_position.x < area_X_border)
            xP = i;
    }
    for (int j : Possible_Plant_Y)
    {
        if (Mouse_position.y > j)
            yP = j;
    }
    for (auto p : plants)
    {
        if (p->IsTouchingMouse(Mouse_position))
            return false;
    }
    if (xP != -1 && yP != -1)
    {
        Vector2f position = {xP, yP};
        Melon *new_melon = new Melon(position, 500);
        plants.push_back(new_melon);
        money -= 100;
        return true;
    }
    else
        return false;
}

void System::MakeMelonShot(const Vector2f &Plant_position, int l_num)
{
    Zombie *target = front(l_num);
    int target_x;
    if (target == NULL)
        return;
    else
    {
        target_x = target->get_x();
    }
    Vector2f p_ = {Plant_position.x + 20, Plant_position.y};
    MelonShot *new_melon_shot = new MelonShot(p_, l_num, target_x);
    melonshots.push_back(new_melon_shot);
}

void System::MakeIceShot(const Vector2f &Plant_position)
{
    Vector2f p_ = {Plant_position.x + 20, Plant_position.y + 5};
    IceShot *new_ice_shot = new IceShot(p_);
    iceShots.push_back(new_ice_shot);
}

vector<string> System::SettingsReader()
{
    ifstream settingsFile;
    settingsFile.open("./settings.txt", ios::in);
    vector<string> Settings;
    int currentLine = 1;
    string line;
    while (getline(settingsFile, line))
    {
        if (currentLine % 2 == 0)
        {
            Settings.push_back(line);
        }
        currentLine++;
    }
    return Settings;
}

Zombie *System::front(int y)
{
    Zombie *result = zombies[0];
    int count = 0;
    for (auto z : zombies)
    {
        if (z->get_y() == y)
        {
            if (result->get_x() <= z->get_x())
            {
                count++;
                result = z;
            }
        }
    }
    if (count == 0)
        return NULL;
    return result;
}