#include "my_game.h"

#include <iostream>

#include "actors/enemies/acolyte.h"
#include "actors/items/armor_item.h"



static void clear_tscreen()
{
    std::cout << "\n";
}
std::vector<actor_spawner_func> game::enemy_spawn_funcs;

game::game(game_condition& win_cond, game_condition& lose_cond) : win_cond(win_cond), lose_cond(lose_cond)
{}

void game::init()
{
    mainfield = new field(15, 15);
    mainfield_view = new field_view(*mainfield);

    cell_entrance* ce = mainfield->generate_entrance_exit(3);

    mainplr = new player();
    {
        mainplr->setMaxHealth(30);
        mainplr->setHealth(30);
        mainplr->setTeamID(10);
        ce->set_object(mainplr);
        //mainplr->addItemToInventory(new armor_item(2, 0.2));
    }

    {
        enemy_spawn_funcs.push_back([](const cell& pc){return new acolyte();});
        actor_spawner<enemy_spawn_funcs> enemy_spawner;
        const std::vector<actor*>& enemies_spawned = enemy_spawner.doSpawn(*mainfield);
        actors_spawned.insert(actors_spawned.end(), enemies_spawned.begin(), enemies_spawned.end());
    }
}


void game::run()
{
    clear_tscreen();
    mainfield_view->display();
    getc(stdin);
    while(1){
        //clear_tscreen();
        mainfield->tickActors();
        if(win_cond.isMet()){
            std::cout << "VICTORY!\n";
            break;
        }
        if(lose_cond.isMet()){
            std::cout << "You LOOSE!\n";
            break;
        }
        mainfield_view->display();
        getc(stdin);
    }
}

game::~game()
{
    delete mainplr;
    for(size_t i = 0; i < actors_spawned.size(); ++i)
        delete actors_spawned[i];
}


// public getters
const player* game::getMainPlayer() { return mainplr; }