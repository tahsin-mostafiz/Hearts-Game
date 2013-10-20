#ifndef __SMARTPLAYER_H__
#define __SMARTPLAYER_H__

#include "Player.h"
#include "Card.h"
#include "Trick.h"

class SmartPlayer : public Player
{
   public:
      SmartPlayer (string name);
      ~SmartPlayer ();
      void lead(Trick &trick, Trick &trick2, int pos);
      void throwOff(Trick &trick, Trick &trick2, int pos);
      void followSuit (Card card, Trick &trick, Trick &trick2, int pos);
};

#endif

