#include "my_game.h"

#include <iostream>

#include "enemy_event/enemies/acolyte.h"
#include "item_event/items/armor_item.h"



static void clear_tscreen()
{
    std::cout << "\n";
}
std::vector<actor_spawner_func> game::enemy_spawn_funcs;

game::game(game_condition& win_cond, game_condition& lose_cond) : win_cond(win_cond), lose_cond(lose_cond)
{}

void game::init()
{
    size_t size;
    std::cout << "Enter size:";
    std::cin >> size;
    //field f;
    if (size > 1){
        mainfield = new field(size, size);
    }
    else{
        mainfield = new field(15, 15);;
    }
    mainfield_view = new field_view(*mainfield);

    cell_entrance* ce = mainfield->generate_entrance_exit(3);

    mainplr = new player();
    {
        mainplr->setMaxHealth(30);
        mainplr->setHealth(30);
        mainplr->setTeamID(10);
        ce->set_object(mainplr);
        mainplr->addItemToInventory(new armor_item(2, 0.2));
    }

    {
        enemy_spawn_funcs.emplace_back([](const cell& pc){return new acolyte();});
        actor_spawner<enemy_spawn_funcs> enemy_spawner;
        const std::vector<actor*>& enemies_spawned = enemy_spawner.doSpawn(*mainfield);
        actors_spawned.insert(actors_spawned.end(), enemies_spawned.begin(), enemies_spawned.end());
    }

}


void game::run()
{
    clear_tscreen();
    //mainfield_view->display();
    getc(stdin);
    while(1){
        clear_tscreen();
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

        std::cout << '\n' << "Where r u ganna be: ";
        cell* cur = &mainplr->getParentCell();
        switch(getchar()){
            case '8':
                cur->set_object(nullptr);
                cur = &cur->get_parent_field().get_cell(cur->get_x()-1, cur->get_y());
                cur->set_object(mainplr);

                //mainfield_view->display();
                break;
            case '2':
                cur->set_object(nullptr);
                cur = &cur->get_parent_field().get_cell(cur->get_x() +1 , cur->get_y());
                cur->set_object(mainplr);
                break;
            case '4':
                cur->set_object(nullptr);
                cur = &cur->get_parent_field().get_cell(cur->get_x(), cur->get_y()-1);
                cur->set_object(mainplr);
                break;
            case '6':
                cur->set_object(nullptr);
                cur = &cur->get_parent_field().get_cell(cur->get_x()  , cur->get_y()+1);
                cur->set_object(mainplr);
                break;
            default:
                std::cout << "u cant move";
                break;
        }

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