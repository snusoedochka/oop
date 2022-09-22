#include <iostream>

#include "field.h"
#include "field_view.h"

#include "player.h"

void clear_tscreen()
{
	std::cout << "\n";
}


int main()
{
    size_t size;
    std::cout << "Enter size:";
    std::cin >> size;
    field f;
    if (size > 1){
        f = field(size, size);
    }
    else{
        f = field();
    }

    field_view fv(f);

    cell_entrance* ce = f.generate_entrance_exit(5);
    {
        player* mainplr = new player();
        mainplr->setMaxHealth(30);
        mainplr->setHealth(30);
        ce->set_object(mainplr);
    }

    size_t x, y;
    do{
        x = std::rand() % size; y = std::rand() % size;
    } while(!f.get_cell(x, y).is_passable() || f.get_cell(x, y).has_object() );

    while(1){ //while ля проверки возможности перемещения
        clear_tscreen();
        fv.display();

        getc(stdin);

        f.tickActors();
        getc(stdin);
    }
}
