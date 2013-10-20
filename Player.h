#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "CardPile.h"
#include "Card.h"
#include <string>
#include "PRNG.h"
#include "Trick.h"
class Player
{
   public:
   Player(string name);
   ~Player();
   virtual string get_name();
   virtual void lead(Trick &trick,Trick &trick2, int pos) = 0;
   virtual void followSuit(Card card, Trick &trick, Trick &trick2, int pos) = 0;
   virtual void throwOff(Trick &trick, Trick &trick2, int pos) = 0;
   CardPile set_of_cards;
   // PlayCard implementation used as a template method design pattern
   void playCard (Trick &tricks, Trick &trick2, int pos, int begin)
   {
        if ( begin == 0 )
        {
            lead(tricks, trick2, pos);
        }
        else if( ((int) tricks.get_size()) != 0 )
        {
            bool has_leadingsuit = false;
            for (int i = 0; i < (int) set_of_cards.get_size(); i++)
            {
                int suit_num1 = (tricks.get_leadcard()).getSuit();
                int suit_num2 = (set_of_cards.give_card(i)).getSuit();
                if (suit_num1 == suit_num2)
                {
                    has_leadingsuit = true;
                    break;
                }
            }
            if (has_leadingsuit)
            {
                followSuit(tricks.get_leadcard(), tricks, trick2, pos);
            }
            else
            {
                throwOff(tricks, trick2, pos);
            }
        }
   }

   void set_player_points (int points);
   int get_player_points ();
   void set_is_roundone (bool first_round);
   bool get_is_roundone ();
   protected:
   bool is_roundone;
   string player_name;
   int player_points;
};

#endif

