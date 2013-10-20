////////////////////////////////////////////////
// Tahsin Mostafiz                            /
//////////////////////////////////////////////

//included libraries and files
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "Card.h"

using namespace std;
string cardin;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

//helper functions

//Input: char
//Output: card suit
//Purpose: This function returns a card suit depending on a char.
Card::Suit stringconvertSuit(char s)
{
    if(s == 'S')
    {
        return Card::Spades;
    }
    else if(s == 'D')
    {
        return Card::Diamonds;
    }
    else if(s == 'C')
    {
        return Card::Clubs;
    }
    else
    {
        return Card::Hearts;
    }
}

//Input: card suit
//Output: string
//Purpose: This function returns a shorthand notation for card suit.
string stringconvertSuitshorthand(Card::Suit s)
{
    if(s == Card::Spades)
    {
        return "S";
    }
    else if(s == Card::Diamonds)
    {
        return "D";
    }
    else if(s == Card::Clubs)
    {
        return "C";
    }
    else
    {
        return "H";
    }
}

//Input: char
//Output: car rank
//Purpose: This function returns a card rank depending on char
Card::Rank stringconvertRank(char s)
{
    switch(s)
    {
        case '2': return Card::Two;
        case '3': return Card::Three;
        case '4': return Card::Four;
        case '5': return Card::Five;
        case '6': return Card::Six;
        case '7': return Card::Seven;
        case '8': return Card::Eight;
        case '9': return Card::Nine;
        case 'T': return Card::Ten;
        case 'J': return Card::Jack;
        case 'Q': return Card::Queen;
        case 'K': return Card::King;
        case 'A': return Card::Ace;
    }
}
//helper function

Card::Card() : rank(Ace), suit(Spades) {}

// Now you do the rest.

Card::Card(Rank r, Suit s) : rank(r), suit(s){}

Card::Card(string sCard)
{
    bool isvalid = stringIsALegalCard(sCard);
    if(isvalid)
    {
        rank = stringconvertRank(sCard[0]);
        suit = stringconvertSuit(sCard[1]);
    }
    else
    {
        cerr << "ERROR: You have entered wrong values for Card" << endl;
        exit (1);
    }

}

Card::~Card(){}

// Rank setter
Card::Rank Card::getRank() const
{
    return rank;
}

// Rank getter
Card::Suit Card::getSuit () const
{
    return this->suit;
}

// Get value of cards (for hearts and QS only)
int Card::getHeartsValue () const
{
    if(suit == Card::Hearts)
    {
            return 1;
    }
    else if(suit == Card::Spades && rank == Card::Queen)
    {
            return 13;
    }
    else
    {
            return 0;
    }
}


// Check whether the card is a legal playing card or not
bool Card::stringIsALegalCard (string s)
{
    bool result1 = false, result2 = false;
    for(int i = 0; i < numRanks; i++)
    {
        if(s[0] == RankName[i])
        {
            result1 = true;
            break;
        }
    }
    for(int i = 0; i < numSuits; i++)
    {
        if(s[1] == SuitName[i])
        {
            result2 = true;
            break;
        }
    }
    if(result1 == true && result2 == true)
    {
        return true;
    }
    else
    {
        return false;
    }



}


// Respective Operator overloading 

bool operator==(const Card& c1, const Card& c2)
{
     if(c1.getRank() == c2.getRank() && c1.getSuit() == c2.getSuit())
     {
            return true;
     }
     else
     {
            return false;
     }
}

bool operator< (const Card& c1, const Card& c2)
{
    int rank1 = c1.getRank();
    int suit1 = c1.getSuit();
    int rank2 = c2.getRank();
    int suit2 = c2.getSuit();

    if(rank1 < rank2)
    {
        return true;
    }
    else if(rank1 == rank2 && suit1 < suit2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream& operator<< (ostream &out, const Card &c)
{
        int rankout = c.getRank() + 2;
        string suitout = stringconvertSuitshorthand(c.getSuit());
        if(rankout == 10)
        {
            out << "T";
        }
        else if(rankout == 11)
        {
            out << "J";
        }
        else if(rankout == 12)
        {
            out << "Q";
        }
        else if(rankout == 13)
        {
            out << "K";
        }
        else if(rankout == 14)
        {
            out << "A";
        }
        else
        {
            out << rankout;
        }
        out << suitout;
        return out;
}

std::istream& operator>> (istream& in, Card& c)
{
       // string cardin;
        in >> cardin;
        if(c.stringIsALegalCard(cardin)){
            c = Card(stringconvertRank(cardin[0]),stringconvertSuit(cardin[1]));
        }
        else
        {
		//cout << cardin << " is not a card" << endl;
	}
        return in;
}

