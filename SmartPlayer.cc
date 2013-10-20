//////////////////////////////////////////////////////////////////
//
// Tahsin Mostafiz
//
///////////////////////////////////////////////////////////////

#include "SmartPlayer.h"
#include "Player.h"
#include "Card.h"

// Constructor
SmartPlayer::SmartPlayer (string name) : Player ( ('s' + name) )
{}

// Destructor
SmartPlayer::~SmartPlayer ()
{}

// Helper functions

// Check whether any Hearts suit exist in the pile of cards or not
bool checkHearts (CardPile& card_set)
{
   for (int i = 0; i < (int) card_set.get_size(); i++)
   {
      int suit_num = card_set.give_card(i).getSuit();
      if (suit_num == 3)
      {
         return true;
      }
   }
   return false;
}

// Implementation of functions

// the lead function
void SmartPlayer::lead (Trick &trick, Trick &trick2, int pos)
{
	if (get_is_roundone())
	{
		for (int i = 0; i < 13; i++)
		{
			if (set_of_cards.give_card(i) == Card::TwoOfClubs)
			{
				trick.replace_card((set_of_cards.give_card(i)), pos);
  // putting in trick
				trick2.add_element(new Card ((set_of_cards.give_card(i).getRank()), (set_of_cards.give_card(i).getSuit())));
 // Putting in trick2
				cout << "  " << get_name() << " has " << set_of_cards.give_card(i) << " and leads with it" << endl;
				trick.set_leadcard(set_of_cards.give_card(i));
				set_of_cards.delete_card(i);
				set_is_roundone (false);
				break;
			}
		}
	}
	else
	{
      // Finding the lowest card in the set of cards
      int lowest_rank_pos = 0;
      Card lowest_card = set_of_cards.give_card(0);
      for (int i = 1; i < (int)set_of_cards.get_size(); i++)
      {
          Card current_card = set_of_cards.give_card(i) ;
          if (current_card < lowest_card)
          {
              lowest_card = current_card;
              lowest_rank_pos = i;
          }
          else
          {
              continue;
          }
      }
      trick.replace_card((set_of_cards.give_card(lowest_rank_pos)), pos);
  // Putting in trick
      trick2.add_element(new Card ((set_of_cards.give_card(lowest_rank_pos).getRank()), (set_of_cards.give_card(lowest_rank_pos).getSuit())));
 // Putting in trick2
      trick.set_leadcard(set_of_cards.give_card(lowest_rank_pos));
   // Sets the leadcard
      cout << "  " << get_name() << " led " << set_of_cards.give_card(lowest_rank_pos) << endl;
      set_of_cards.delete_card(lowest_rank_pos);
	}
}

// The throwOff function
void SmartPlayer::throwOff (Trick &trick, Trick &trick2, int pos)
{
   for (int i = 0; i < (int) set_of_cards.get_size(); i++)
   {
      if ( set_of_cards.give_card(i) == Card::QueenOfSpades ) // Check for QS
      {
            set_of_cards.give_card(i);
            trick.replace_card((set_of_cards.give_card(i)), pos);
            trick2.add_element(new Card ((set_of_cards.give_card(i).getRank()), (set_of_cards.give_card(i).getSuit())));
            cout << "  " << get_name() << " threw off " << set_of_cards.give_card(i) << endl;
            set_of_cards.delete_card(i);
            break;
      }
      else if (checkHearts(set_of_cards)) // Check for hearts
      {
         // Finding the highest heart card
         int highest_rank = 0;
         int highest_rank_pos = 0;
         for (int i = 0; i < (int) set_of_cards.get_size(); i++)
         {
            int suit_num = (set_of_cards.give_card(i)).getSuit();
            int rank_num = ((set_of_cards.give_card(i)).getRank());
            if ((suit_num == 3) && (rank_num > highest_rank))
            {
               highest_rank = rank_num;
               highest_rank_pos = i;
            }
         }
         trick.replace_card((set_of_cards.give_card(highest_rank_pos)), pos);
  // Putting in trick
         trick2.add_element(new Card ((set_of_cards.give_card(highest_rank_pos).getRank()), (set_of_cards.give_card(highest_rank_pos).getSuit())));
 // Putting in trick2
         cout << "  " << get_name() << " threw off " << set_of_cards.give_card(highest_rank_pos) << endl;
         set_of_cards.delete_card(highest_rank_pos);
         break;
      }
      else   // Finding the highest card in the other suits
      {
         Card highest_card = set_of_cards.give_card(0);
         int highest_rank_pos = 0;
         for (int i = 1; i < (int) set_of_cards.get_size(); i++)
         {
            Card current_card = (set_of_cards.give_card(i));
            if ((highest_card < current_card))
            {
               highest_card = current_card;
               highest_rank_pos = i;
            }
         }
         trick.replace_card((set_of_cards.give_card(highest_rank_pos)), pos);
         trick2.add_element(new Card ((set_of_cards.give_card(highest_rank_pos).getRank()), (set_of_cards.give_card(highest_rank_pos).getSuit())));
         cout << "  " << get_name() << " threw off " << set_of_cards.give_card(highest_rank_pos) << endl;
         set_of_cards.delete_card(highest_rank_pos);
         break;
      }
   }
}

// Helper function to find the highest card position
int get_highest_card_position(Trick &trick, Card lead_card)
{
   int position;
   int lead_card_suit = lead_card.getSuit();
   int lead_card_rank = lead_card.getRank();
   bool got_higher = false;

 for(int i = 0; i < trick.get_size(); i++)
   {
      int current_card_suit = (trick.give_card(i)).getSuit();
      int current_card_rank = (trick.give_card(i)).getRank();
      if(lead_card_suit == current_card_suit)
      {
         if(lead_card_rank < current_card_rank)
         {
            lead_card_rank = current_card_rank;
            position = i;
            got_higher = true;
         }
         if(!got_higher)
         {
            if(lead_card_rank == current_card_rank)
            {
               position = i;
            }
         }
      }
   }
   return position;
}

// The followSuit function
void SmartPlayer::followSuit (Card lead_card, Trick &trick, Trick &trick2, int pos)
{
    int highest_card_position = get_highest_card_position(trick2, lead_card);
    Card highest_card = Card((trick2.give_card(highest_card_position)).getRank(),(trick2.give_card(highest_card_position)).getSuit());
    int highest_card_rank = highest_card.getRank();
    int highest_card_suit = highest_card.getSuit();
    Card temp;
    Card highest_card_now;
    int card_gone = 0;
    int position;
    bool has_low_card = false;
    // Finds the lower card compared to trump 
    for (int i = 0; i < (int) set_of_cards.get_size(); i++)
    {
        int current_card_rank = (set_of_cards.give_card(i)).getRank();
        int current_card_suit = (set_of_cards.give_card(i)).getSuit();
        int highest_card_now_rank = highest_card_now.getRank();
        if(card_gone == 0)
        {
            if(highest_card_suit == current_card_suit)
            {
                if(current_card_rank < highest_card_rank)
                {
                    highest_card_now = Card(((set_of_cards.give_card(i)).getRank()), (set_of_cards.give_card(i)).getSuit());
                    card_gone++;
                    has_low_card = true;
                    position = i;
                }
            }
        }
        else
        {
            if(highest_card_suit == current_card_suit)
            {
                if(current_card_rank > highest_card_now_rank && current_card_rank < highest_card_rank)
                {
                    highest_card_now = Card(((set_of_cards.give_card(i)).getRank()), (set_of_cards.give_card(i)).getSuit());
                    has_low_card = true;
                    position = i;
                }
            }
        }
    }

   // Check for higher card
    if(!has_low_card)
    {
        for (int i = 0; i < (int) set_of_cards.get_size(); i++)
        {
            int current_card_rank = (set_of_cards.give_card(i)).getRank();
            int highest_card_now_rank = highest_card_now.getRank();
            int current_card_suit = (set_of_cards.give_card(i)).getSuit();
            if(card_gone == 0)
            {

                if(highest_card_suit == current_card_suit)
                {
                    if(current_card_rank > highest_card_rank)
                    {
                        highest_card_now = Card(((set_of_cards.give_card(i)).getRank()), (set_of_cards.give_card(i)).getSuit());
                        card_gone++;
                        position = i;
                    }
                }
            }
            else
            {
                    if(highest_card_suit == current_card_suit)
                    {
                        if(current_card_rank < highest_card_now_rank)
                        {
                            highest_card_now = Card(((set_of_cards.give_card(i)).getRank()), (set_of_cards.give_card(i)).getSuit());
                            position = i;
                        }
                    }
            }
        }
    }
   trick.replace_card(highest_card_now, pos);
   // Add to trick
   trick2.add_element(new Card ((highest_card_now.getRank()), (highest_card_now.getSuit())));
 // add to trick2
   cout << "  " << get_name() << " followed suit with " << highest_card_now << endl;
   set_of_cards.delete_card(position);
}

