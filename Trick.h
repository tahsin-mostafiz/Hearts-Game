#ifndef _TRICK_H_
#define _TRICK_H_

#include "CardPile.h"
#include "Card.h"

using namespace std;

class Trick : public CardPile {
   public :
   Trick();
   virtual ~Trick();
   void set_leadcard (Card leadcard);
   Card get_leadcard ();
   protected:
   Card lead_card;
};

#endif

