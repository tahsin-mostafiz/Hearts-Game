#ifndef _CARDPILE_H_
#define _CARDPILE_H_


#include <vector>
#include "Card.h"
#include "PRNG.h"
#include <iostream>

using namespace std;

class CardPile : private vector<Card*> {
    public:
	// Constructors and destructor
	CardPile ();
	virtual ~CardPile ();

   void shuffle();
	void setRandomSeed(uint32_t randomSeed);
	// Other stuff needed

   int heartsValue() const;
	int get_size() const;
	void add_element(Card* card);
   void print();
   Card give_card (int i) const;
   Card* give_cardptr(int i);
   void deal (int hand);
   void replace_card(Card card, int pos);
   void delete_card (int pos);
   void destroy();
    private:
	PRNG prng;
	static const uint32_t DefaultRandomSeed;
};

#endif

