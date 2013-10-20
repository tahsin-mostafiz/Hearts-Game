#include "Trick.h"
//#include "CardPile.h"
//#include "Card.h"

Trick::Trick ()
{
   CardPile();
}

Trick::~Trick()
{}

void Trick::set_leadcard (Card leadcard)
{
   lead_card = Card(leadcard.getRank() , leadcard.getSuit());
}

Card Trick::get_leadcard ()
{
   return lead_card;
}


