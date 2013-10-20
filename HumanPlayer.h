#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include "Player.h"
#include "Card.h"
#include "Trick.h"

class HumanPlayer : public Player
{
   public:
   HumanPlayer (string name);
   ~HumanPlayer();
   bool IsCardPresent (Card card);
   void lead(Trick &trick, Trick &trick2, int pos);
   void throwOff(Trick &trick, Trick &trick2, int pos);
   void followSuit (Card card, Trick &trick, Trick &trick2, int pos);
};

#endif

