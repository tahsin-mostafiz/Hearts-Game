////////////////////////////////////////////////////////////
//                                                       //
//  Tahsin Mostafiz                                     // 
//                                                     //
////////////////////////////////////////////////////////

// Libraries and files included
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Card.h"
#include "Deck.h"

// Constructor
Deck::Deck(){
    CardPile();
}

// Destructor
Deck::~Deck(){
}


// Generate a deck of cards
void Deck::generate()
{
  add_element (new Card("2S"));
  add_element (new Card("3S"));
  add_element (new Card("4S"));
  add_element (new Card("5S"));
  add_element (new Card("6S"));
  add_element (new Card("7S"));
  add_element (new Card("8S"));
  add_element (new Card("9S"));
  add_element (new Card("TS"));
  add_element (new Card("JS"));
  add_element (new Card("QS"));
  add_element (new Card("KS"));
  add_element (new Card("AS"));

  add_element (new Card("2D"));
  add_element (new Card("3D"));
  add_element (new Card("4D"));
  add_element (new Card("5D"));
  add_element (new Card("6D"));
  add_element (new Card("7D"));
  add_element (new Card("8D"));
  add_element (new Card("9D"));
  add_element (new Card("TD"));
  add_element (new Card("JD"));
  add_element (new Card("QD"));
  add_element (new Card("KD"));
  add_element (new Card("AD"));

  add_element (new Card("2C"));
  add_element (new Card("3C"));
  add_element (new Card("4C"));
  add_element (new Card("5C"));
  add_element (new Card("6C"));
  add_element (new Card("7C"));
  add_element (new Card("8C"));
  add_element (new Card("9C"));
  add_element (new Card("TC"));
  add_element (new Card("JC"));
  add_element (new Card("QC"));
  add_element (new Card("KC"));
  add_element (new Card("AC"));

  add_element (new Card("2H"));
  add_element (new Card("3H"));
  add_element (new Card("4H"));
  add_element (new Card("5H"));
  add_element (new Card("6H"));
  add_element (new Card("7H"));
  add_element (new Card("8H"));
  add_element (new Card("9H"));
  add_element (new Card("TH"));
  add_element (new Card("JH"));
  add_element (new Card("QH"));
  add_element (new Card("KH"));
  add_element (new Card("AH"));
}


// Check whether the deck has 52 cards
bool Deck::playingWithAFullDeck () const
{
   if(get_size() == 52)
   {
      for(int i = 0; i < get_size(); i++)
      {
         Card temp = give_card(i);
         for(int j = i+1; j < get_size() - i; j++)
         {
            if(temp == give_card(j))
            {
               return false;
            }
         }
      }
      return true;
   }
   else
   {
      return false;
   }
}


// Operating overloading
std::istream &operator>> (istream& in, Deck& deck)
{
   string card_name;
   while ( (in >> card_name) && (deck.get_size() < 52))
   {
      //in >> card_name;
      deck.add_element(new Card(card_name));
   }
   return in;
}


