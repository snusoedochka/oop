#ifndef ARMOR_ITEM_H
#define ARMOR_ITEM_H

#include "../item_event.h"
#include "../../actions/action.h"



class armor_item : public item_event
{
	public:


	armor_item(size_t dt, double dr);

    virtual void onUsed(actor& on_who);

protected:

	bool worn;
    size_t dt; double dr;
};


#endif
