#ifndef __RANDOMPLAYER_H__
#define __RANDOMPLAYER_H__

#include "Player.h"
#include "Card.h"
#include "PRNG.h"
#include "Trick.h"
#include "CardPile.h"

class RandomPlayer : public Player
{
   public:
      RandomPlayer (string name, int seed);
      ~RandomPlayer ();
      void set_rpseed (int i);
    void lead(Trick &trick, Trick &trick2, int pos);
    void throwOff(Trick &trick, Trick &trick2, int pos);
       void followSuit (Card card, Trick &trick, Trick &trick2, int pos);
   protected:
      //bool firstround = true;
      PRNG prng;
};

#endif

