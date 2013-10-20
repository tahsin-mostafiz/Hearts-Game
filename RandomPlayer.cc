#include "RandomPlayer.h"
#include  "CardPile.h"
#include "Card.h"

// Constructor
RandomPlayer::RandomPlayer (string name, int seed) : Player ( ('r' + name) ), prng(seed)
{

}

// Destructor
RandomPlayer::~RandomPlayer ()
{}

// Implementation of functions

void RandomPlayer::set_rpseed (int i)
{
   prng.seed(i);
}

// The lead function
void RandomPlayer::lead (Trick &trick, Trick &trick2, int pos)
{
	if (get_is_roundone())  // Check whether it is round one or not
	{
		for (int i = 0; i < (int) set_of_cards.get_size(); i++)
		{
			if (set_of_cards.give_card(i) == Card::TwoOfClubs)
			{
				trick.replace_card((set_of_cards.give_card(i)), pos);  // Putting in trick 
				trick.set_leadcard(set_of_cards.give_card(i));  
				trick2.add_element(new Card(set_of_cards.give_card(i).getRank(), set_of_cards.give_card(i).getSuit())); // Putting in trick2
				cout << "  " << get_name() << " has " << set_of_cards.give_card(i) << " and leads with it" << endl;
				set_of_cards.delete_card(i);
				set_is_roundone (false);
				break;
			}
		}
	}
	else
	{
      int choose_card = (int) prng (0, (set_of_cards.get_size()-1));
      trick.replace_card((set_of_cards.give_card(choose_card)), pos);
      trick2.add_element(new Card(set_of_cards.give_card(choose_card).getRank(), set_of_cards.give_card(choose_card).getSuit()));
      cout << "  " << get_name() << " led " << set_of_cards.give_card(choose_card) << endl;
      trick.set_leadcard(set_of_cards.give_card(choose_card));
      set_of_cards.delete_card(choose_card);
	}
}

// The throwOff function
void RandomPlayer::throwOff (Trick &trick, Trick &trick2, int pos)
{
   int choose_card = prng (0, (set_of_cards.get_size()-1));
   trick.replace_card((set_of_cards.give_card(choose_card)), pos);
  // Putting in trick
   trick2.add_element(new Card(set_of_cards.give_card(choose_card).getRank(), set_of_cards.give_card(choose_card).getSuit()));
 // Putting in trick2
   cout << "  " << get_name() << " threw off " << set_of_cards.give_card(choose_card) << endl;
   set_of_cards.delete_card(choose_card);
}


// Helper function that pushes card to CardPile
void push_to_cardpile (CardPile &setofcards, CardPile &temp, Card lead_card)
{
    int temp_suit = lead_card.getSuit();
    for(int i = 0; i < (int) setofcards.get_size(); i++)
    {
        int suit_num1 = (setofcards.give_card(i)).getSuit();
        if ( suit_num1 == temp_suit )
        {
            temp.add_element(new Card(setofcards.give_card(i).getRank(), setofcards.give_card(i).getSuit()));
        }
    }
}


// Returns the card position in the pile of cards vector
int return_cardpos (CardPile &setofcards, Card to_find)
{
   int position;
   for (int i = 0; i < (int) setofcards.get_size(); i++)
   {
      if (to_find == setofcards.give_card(i))
      {
         position = i;
         break;
      }
   }
   return position;
}



// The followSuit implementation
void RandomPlayer::followSuit (Card lead_card, Trick &trick,Trick &trick2, int pos)
{
   int choose_card;
   CardPile temp;
   push_to_cardpile(set_of_cards, temp, lead_card);
   choose_card = prng(0, ((int)temp.get_size()-1));
   // Choosing a random card
   trick.replace_card((temp.give_card(choose_card)), pos);
 // Placing in trick
   trick2.add_element(new Card(temp.give_card(choose_card).getRank(), temp.give_card(choose_card).getSuit()));
   cout << "  " << get_name() << " followed suit with " << (temp.give_card(choose_card)) << endl;
   int delete_pos = return_cardpos(set_of_cards, (temp.give_card(choose_card)));
   set_of_cards.delete_card(delete_pos);
   temp.destroy();
}

