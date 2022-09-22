#include "player.h"

#include "cell_object_view.h"
#include "cell_exit.h"
#include "field.h"
player::player()
{
	initView();
    max_ap = 10;
    mv_action = new action_move(1.0);
}

// Properties

void player::initView() { vw = new cell_object_view('@', *this); }

size_t& player::getAP() { return ap; }

// Events

void player::onAdd(cell& holder) {}

void player::onTurn()
{
	ap = max_ap;
/*
    if(mv_action->canExecute(ap, this, nullptr, getParentCell().get_neighbour_cells(1)[0]))
        mv_action->execute(ap, this, nullptr, getParentCell().get_neighbour_cells(1)[0]);
 */
    if (mv_action->canExecute(ap, this, nullptr, &getParentCell().get_parent_field().get_cell(0,0)))
        (mv_action->execute(ap, this, nullptr, &getParentCell().get_parent_field().get_cell(0,0)));

}
void player::onDeath() {}

void player::onWalkedIn(actor& by_who) {}
void player::onWalkOn(cell& to_where)
{
	cell_exit* ce = dynamic_cast<cell_exit*>(&to_where);

	if(ce){
		
	}
}
