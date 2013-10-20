////////////////////////////////////////////////////////////////
//                                                           //
// Tahsin Mostafiz                                          //
//                                                         //
////////////////////////////////////////////////////////////


#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"
#include "Player.h"

extern vector<Player*> PlayerList;

const uint32_t CardPile::DefaultRandomSeed = 37;

// Constructor
CardPile::CardPile() : prng(DefaultRandomSeed) {}

// Set random seed
void CardPile::setRandomSeed(uint32_t randomSeed) {
	prng.seed(randomSeed);
}

// Destructor
CardPile::~CardPile ()
{
	for(int i=0; i < (int) size(); i++)
	{
			 delete at(i);
	}
}

// Shuffle the pile of cards 
void CardPile::shuffle() {
	for (int i = size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

// Method for adding elements (i.e. push backing)
void CardPile::add_element(Card* card){
    //Card * ptr = card;
    push_back(card);
}

// Method for getting the size of the pile of cards 
// i.e return size of vector
int CardPile::get_size() const{
    return (int) size();
}

// Printing the pile of cards
void CardPile::print(){
    for(int i = 0; i < (int) size(); i++){

        cout << *(at(i)) << " ";
    }
    cout << endl;
}

// Finding the value(points) of pile of cards that each
// player will possess to determine score
int CardPile::heartsValue() const
{   int total = 0;
    for(int i = 0; i < (int) size(); i++){

        total = total + (at(i))->getHeartsValue();
    }
    //cout << "total" << total << endl;
    return total;

}


// Method for returning a card (using at() in vector library)
Card CardPile::give_card (int i) const
{
   return *(at(i));
}

// Method for returning a pointer to the card in the
// pile of cards
Card* CardPile::give_cardptr (int i)
{
   return at(i);
}

// Deal cards to the players
void CardPile::deal(int hand)
{   
   bool p1turn;
	bool p2turn;
	bool p3turn;
	bool p4turn;

   // To determine which player to give the card first
   // in the next four if statements
   if(hand % 4 == 1)
   {
	   p1turn = true;
		p2turn = false;
		p3turn = false;
		p4turn = false;
   }
   else if(hand % 4 == 2)
   {

		p1turn = false;
		p2turn = true;
      p3turn = false;
      p4turn = false;

   }

   else if(hand % 4 == 3)
   {
      p1turn = false;
		p2turn = false;
		p3turn = true;
		p4turn = false;
   }
	else if( hand % 4 == 0)
	{
		p1turn = false;
		p2turn = false;
		p3turn = false;
		p4turn = true;
	}

	for (int i = 51; i >= 0; i--)
	{
	   if (p1turn)
	   {
         Card p1card = give_card (i);
         ((*PlayerList[0]).set_of_cards).add_element(new Card( p1card.getRank(), p1card.getSuit() ));
         p1turn = false;
         p2turn = true;
         delete at(i);
         erase(begin() + i);
      }

      else if (p2turn)
      {  
         Card p2card = give_card (i);
         ((*PlayerList[1]).set_of_cards).add_element(new Card( p2card.getRank(), p2card.getSuit() ));
         p2turn = false;
         p3turn = true;
         delete at(i);
         erase(begin() + i);
      }

      else if (p3turn)
      {
         Card p3card = give_card (i);
         ((*PlayerList[2]).set_of_cards).add_element(new Card( p3card.getRank(), p3card.getSuit() ));
         p3turn = false;
         p4turn = true;
         delete at(i);
         erase(begin() + i);
      }

      else if (p4turn)
      {
         Card p4card = give_card (i);
         ((*PlayerList[3]).set_of_cards).add_element(new Card( p4card.getRank(), p4card.getSuit() ));
         p4turn = false;
         p1turn = true;
         delete at(i);
         erase(begin() + i);
      }
   }
}

// Destroy the pile of cards
void CardPile::destroy ()
{
   for(int i=0; i < (int) size(); i++)
   {
	    delete at(i);
	}
   clear();
}

// Delete a card
void CardPile::delete_card (int pos)
{
  delete at(pos);
  erase(begin() + pos);
}


// Replace a card in the pile of cards (in the trick)
// the position number of the pile of cards represent the
// respective player who played the card
void CardPile::replace_card (Card card, int pos)
{
    if(at(pos) == NULL)
    {

    }
    else
    {
        delete at(pos);
    }
  at(pos) = new Card(card.getRank(), card.getSuit());
}


