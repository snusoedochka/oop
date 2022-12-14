#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "action_move.h"

class player : public actor
{
	public:

	player();

	// Properites
	size_t& getAP();


	// Events
	virtual void onAdd(cell& holder);

	virtual void onTurn();
	virtual void onDeath();

	virtual void onWalkedIn(actor& by_who);
	virtual void onWalkOn(cell& to_where);


	protected:

	virtual void initView();

	size_t ap, max_ap;

	action_move* mv_action;
};

#endif
