/////////////////////////////////////////////////////////
//                                                    //
// Tahsin Mostafiz                                   //
//                                                  //
/////////////////////////////////////////////////////

// Included files and libraries
#include "HumanPlayer.h"
#include "Card.h"
#include "Trick.h"
#include <string>
#include <iostream>

using namespace std;
extern string cardin;
// Constructor
HumanPlayer::HumanPlayer (string name) : Player ( ('h' + name) )
{}

// Destructor
HumanPlayer::~HumanPlayer ()
{}

// Check whether the card is present in the set of cards
bool HumanPlayer::IsCardPresent (Card card)
{
   for (int i = 0; i < (int) set_of_cards.get_size(); i++)
   {
      if (card == set_of_cards.give_card(i))
      {
         return true;
      }
      else
      {
      }
   }
   return false;
}


// A helper function for deleting
void delete_helper (CardPile &set_of_cards, Card card)
{
   for (int i = 0; i < (int) set_of_cards.get_size(); i++)
   {
      if (card == set_of_cards.give_card(i))
      {
         set_of_cards.delete_card(i);
         break;
      }
      else
      {
      }
   }
}

// Return the position of the card in the pile of cards
int return_cardpos (CardPile &setofcards)
{
   int position;
   for (int i = 0; i < (int) setofcards.get_size(); i++)
   {
      if (Card::TwoOfClubs == setofcards.give_card(i))
      {
         position = i;
         break;
      }
   }
   return position;
}


Card read_card;

// Implementing the virtual functions


// The trick (pile of cards) is used to have a one to one correspondence
// with the player and the card that th eplayer plays

// The trick2 (pile of cards) is used to just push back the card that
// the player plays into this pile of cards 

// The lead function
void HumanPlayer::lead (Trick &trick, Trick &trick2, int pos)
{
   if (get_is_roundone()) // check whether it is round one or not
	{
	   
	   int position = return_cardpos(set_of_cards);
	   
		trick.replace_card((set_of_cards.give_card(position)), pos);
		trick2.add_element(new Card ((set_of_cards.give_card(position).getRank()), (set_of_cards.give_card(position).getSuit())));
		cout << "  " << get_name() << " has 2C and leads with it" << endl;
		set_is_roundone (false);
		trick.set_leadcard(set_of_cards.give_card(position));
		set_of_cards.delete_card(position);
		return;
   }
   else
   {
      int i = 0;
      cout << "Human Player " << get_name() << " has these cards:" << endl;
      cout << "    ";
      set_of_cards.print();
      cout << "What card would you like to play, " << get_name() <<"? ";
      while(1)
      {
          if(i > 0)
          {
             cout << "What card would you like to play, " << get_name() <<"? ";
          }
          else
          {
             i++;
          }
	  cin >> read_card;
	  
	  if(Card::stringIsALegalCard(cardin)){
		if (IsCardPresent (read_card))
          	{
             		trick.replace_card(read_card, pos);
             		trick.set_leadcard(read_card);
             		trick2.add_element(new Card (read_card.getRank(), read_card.getSuit()));
             		delete_helper(set_of_cards, read_card);
             		break;
          	}
          	else
          	{
             		cout << read_card << " is not in your hand" << endl;
          	}
	  }
	  else{
		cout << cardin << " is not a card" << endl;
	  }
      }
   }
}

// The throwOff function. Do respective checks
void HumanPlayer::throwOff (Trick &trick,Trick &trick2, int pos)
{
    int i = 0;
    cout << "Human Player " << get_name() << " has these cards:" << endl;
    cout << "    ";
    set_of_cards.print();
    cout << "What card would you like to play, " << get_name() <<"? ";
    while(1)
    {
        if(i > 0)
        {
            cout << "What card would you like to play, " << get_name() <<"? ";
        }
        else
        {
            i++;
        }
	cin >> read_card;

	if(Card::stringIsALegalCard(cardin)){
                if (IsCardPresent (read_card))
                {
                        trick.replace_card(read_card, pos);
                        //trick.set_leadcard(read_card);
                        trick2.add_element(new Card (read_card.getRank(), read_card.getSuit()));
                        cout << "  " << get_name() << " threw off " << read_card << endl;
			delete_helper(set_of_cards, read_card);
                        break;
                }
                else
                {
                        cout << read_card << " is not in your hand" << endl;
                }
          }
          else{
                cout << cardin << " is not a card" << endl;
          }

    }
}

// The followSuit implementation. Do respective checks
void HumanPlayer::followSuit (Card lead_card, Trick &trick, Trick &trick2, int pos)
{
    int i = 0;
    cout << "Human Player " << get_name() << " has these cards:" << endl;
    cout << "    ";
    set_of_cards.print();
    cout << "What card would you like to play, " << get_name() <<"? ";
    while(1)
    {
        
	if(i > 0)
        {
            cout << "What card would you like to play, " << get_name() <<"? ";
        }
        i++;
	cin >> read_card;
        Card::Suit input_suit = read_card.getSuit();
        int suit_num1 = input_suit;
        int suit_num2 = lead_card.getSuit();

        if (suit_num1 == suit_num2)
        {
            if (IsCardPresent (read_card))
            {
                trick.replace_card(read_card, pos);
                trick2.add_element(new Card (read_card.getRank(), read_card.getSuit()));
                delete_helper(set_of_cards, read_card);
                cout << "  " << get_name() << " followed suit with " << read_card << endl;
                break;
            }
            else
            {
                cout << "Card is not present in your hand" << endl;
            }
        }
        else
        {  
	    if(Card::stringIsALegalCard(cardin)){	
            	cout << "You have at least one";
	    	int lead_card_suit = lead_card.getSuit();
	    	if(lead_card_suit == 0)
	    	{
			cout << " S; you must follow suit!" << endl;
	    	}
	    	else if(lead_card_suit == 1)
            	{
                	cout << " D; you must follow suit!" << endl;
            	}
	    	else if(lead_card_suit == 2)
            	{
                	cout << " C; you must follow suit!" << endl;
            	}
	    	else if(lead_card_suit == 3)
            	{
                	cout << " H; you must follow suit!" << endl;
            	}
	    }
	    	
	     else
	     {
	   	cout << cardin << " is not a card" << endl;
		
	     }
	  

        }
    }
}


