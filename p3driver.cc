//////////////////////////////////////////////////////////////
//                                                         //
//  Tahsin Mostafiz                                       //
//                                                       //
//////////////////////////////////////////////////////////

// Including files and libraries
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include "Player.h"
#include <vector>
#include "Deck.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
using namespace std;

vector<Player*> PlayerList;

int main(int argc, char* argv[])
{
   // Declaring necessary variables
   Deck deck;
   Trick trick;
   Trick trick2;
   trick.add_element(NULL);
   trick.add_element(NULL);
   trick.add_element(NULL);
   trick.add_element(NULL);
   int maxscore;
   string filename;
   bool seedgiven = false, maxscoregiven = false, filenamegiven = false, playersgiven = false;
   // Check for the respective options
   for(int i = 0; i < argc; i++)
   {
      if(strcmp(argv[i], "-r") == 0)
      {
         if(argc == i+1)
         {
            cerr << "Error, -r requires another argument.  Aborting." << endl;
            exit(1);
         }
         deck.setRandomSeed(atoi(argv[i+1]));
         seedgiven = true;
         i++;
      }
      else if((strcmp(argv[i],"-s") == 0) && (atoi(argv[i+1]) > 0))
      {
         if(argc == i+1)
         {
            cerr << "Error, -s requires another argument.  Aborting." << endl;
            exit(1);
         }
         maxscore = atoi(argv[i+1]);
         maxscoregiven = true;
         i++;
      }
      else if(strcmp(argv[i], "-d") == 0)
      {
         if(argc == i+1)
         {
            cerr << "Error, -d requires another argument.  Aborting." << endl;
            exit(1);
         }
         filename = argv[i+1];
         ifstream inputstream;
	 inputstream.open (filename.c_str());
         if(inputstream.good()){
         	inputstream >> deck;
		if(deck.playingWithAFullDeck())
		{
         		filenamegiven = true;
         		i++;
		}
		else
		{
			cerr << "Error, incomplete deck.  Aborting." << endl;
			cout << "  ";
			deck.print();
			exit(1);
		}
	 }
	 else
	 {
		cerr << "Error, couldn't open card deck input file \"" << filename << "\""<< endl;
		exit(1);
	 }
      }
      else if(strcmp(argv[i], "-p") == 0)
      {
         if(argc == i+1)
         {
            cerr << "Error, -p requires another argument.  Aborting." << endl;
            exit(1);
         }
         int j = 0, f = i + 2;
         while(j<4)
         {
            if(strcmp(argv[f], "R") == 0)
            {
                PlayerList.push_back(new RandomPlayer (argv[f-1], atoi(argv[f+1])));
                f = f + 3;
                j++;
            }
            else if(strcmp(argv[f],"S") == 0)
            {
               PlayerList.push_back(new SmartPlayer (argv[f-1]));
               f = f + 2;
               j++;
            }
            else if(strcmp(argv[f],"H") == 0)
            {
               PlayerList.push_back(new HumanPlayer (argv[f-1]));
               f = f + 2;
               j++;
            }
            else
            {
               if(j != 4)
               {
                  cerr << "Error, -p requires another argument.  Aborting." << endl;
                  exit(1);
               }
            }
         }
         i = f;
         playersgiven = true;
      }
   }
   if(!maxscoregiven)
   {
      maxscore = 40;
   }
   if(!filenamegiven)
   {
      deck.generate();
   }
   if(!playersgiven)
   {
      PlayerList.push_back(new SmartPlayer("Alice"));
      PlayerList.push_back(new SmartPlayer("Bob"));
      PlayerList.push_back(new SmartPlayer("Carole"));
      PlayerList.push_back(new SmartPlayer("Ted"));
   }
   (PlayerList[0])->set_player_points(0);
   (PlayerList[1])->set_player_points(0);
   (PlayerList[2])->set_player_points(0);
   (PlayerList[3])->set_player_points(0);

   // hand start
   for (int hand = 1; ; hand++)
   {
      if (hand == 1)
      {
	 cout << "\n\n";
         cout << "At the beginning of hand " << hand << ", here is the deck:" << endl;
         cout << "    ";
         deck.shuffle();
         deck.print();
         deck.deal(hand);
      }
      else
      {
         deck.generate();
	 cout << "\n\n";
         cout << "At the beginning of hand " << hand << ", here is the deck:" << endl;
         cout << "    ";
         deck.shuffle();
         deck.print();
         deck.deal(hand);
      }
      cout << "\n\n";
      cout << "Here are the hands for each player at the start of hand number " << hand << "\n" << endl;
      cout << (*PlayerList[0]).get_name() << " has these cards:" << endl;
      cout << "    ";
      (*PlayerList[0]).set_of_cards.print();
      cout << "\n";
      cout << (*PlayerList[1]).get_name() << " has these cards:" << endl;
      cout << "    ";
      (*PlayerList[1]).set_of_cards.print();
      cout << "\n";
      cout << (*PlayerList[2]).get_name() << " has these cards:" << endl;
      cout << "    ";
      (*PlayerList[2]).set_of_cards.print();
      cout << "\n";
      cout << (*PlayerList[3]).get_name() << " has these cards:" << endl;
      cout << "    ";
      (*PlayerList[3]).set_of_cards.print();
      cout << "\n" << endl;

      int leading_player = 0;

      // round start
      for (int round = 1; round < 14; round++)
      {
         cout << "Now starting round " << round << " of hand " << hand << endl;
         // Finds the leading player
         if (round == 1)
         {
            for(int i = 0; i < 4; i++)
            {
               for (int j = 0; j < 13; j++)
               {
                  if (PlayerList[i]->set_of_cards.give_card(j) == Card::TwoOfClubs)
                  {
                     leading_player = i;
                     PlayerList[i]->set_is_roundone(true);
                     break;
                  }
                  PlayerList[i]->set_is_roundone(false);
               }
            }
         }
         // Player plays his card
         for (int i = 0; i < 4; i++)
         {
            if (leading_player == 3)
            {
               (PlayerList[leading_player])->playCard(trick, trick2, leading_player, i);
               leading_player = 0;
            }
            else
            {
               (PlayerList[leading_player])->playCard(trick, trick2, leading_player, i);
               leading_player++;
            }
         }
         // Decide the winning card of the round
         Card win_card = Card((trick.get_leadcard()).getRank() , (trick.get_leadcard()).getSuit());
        int lead_suit = (trick.get_leadcard()).getSuit();
	int lead_rank = (trick.get_leadcard()).getRank();
	 for (int card = 0; card < trick.get_size(); card++)
         {
            //int lead_suit = (trick.get_leadcard()).getSuit();
            int suit_num = (trick.give_card(card)).getSuit();
            //int lead_rank = (trick.get_leadcard()).getRank();
            int rank_num = (trick.give_card(card)).getRank();
            if(lead_suit == suit_num)
            {
               if(lead_rank < rank_num)
               {
		  lead_rank = rank_num;
		  lead_suit = suit_num;
                  win_card = Card((trick.give_card(card)).getRank() , (trick.give_card(card)).getSuit());
              		//out << win_card << endl;
		 }
            }
         }
	//cout << win_card << endl;
         // Decide the winning player of the round
         int win_player_pos;
         for (int trick_pos = 0; trick_pos < trick.get_size(); trick_pos++)
         {
            if (win_card == trick.give_card(trick_pos))
            {
               win_player_pos = trick_pos;
               leading_player = win_player_pos;
            }
            else
            {}
         }
         cout <<"  " <<PlayerList[win_player_pos]->get_name() << " won the trick and added the following cards:" << endl;
         cout << "    ";
	 trick2.print();
         trick2.destroy();
	 cout << "\n";
         PlayerList[win_player_pos]->set_player_points((trick.heartsValue()) + PlayerList[win_player_pos]->get_player_points());
       }
       // round end
      cout << "At the end of hand " << hand << " the score is:" << endl;
      cout << "    "  <<(PlayerList[0]->get_name()) << " " <<  (PlayerList[0]->get_player_points())  << endl;
      cout << "    " << (PlayerList[1]->get_name()) << " " << (PlayerList[1]->get_player_points())  << endl;
      cout << "    " <<(PlayerList[2]->get_name()) << " " << (PlayerList[2]->get_player_points())  << endl;
      cout << "    " <<(PlayerList[3]->get_name()) << " " << (PlayerList[3]->get_player_points()) << endl;
      if ( (PlayerList[0]->get_player_points() > maxscore) || (PlayerList[1]->get_player_points() > maxscore)
			|| (PlayerList[2]->get_player_points() > maxscore) || (PlayerList[3]->get_player_points() > maxscore) )
		{
		  break;
		}
   }
      // hand end
      // Find the winner name
      int temp;
      string winner_name;
      for (int i = 0; i < 4; i++)
      {
		   if (i == 0)
		   {
			   temp = PlayerList[i]->get_player_points();
			   winner_name = PlayerList[i]->get_name();
		   }
		   else
		   {
			   if (temp > PlayerList[i]->get_player_points())
			   {
			      temp = PlayerList[i]->get_player_points();
				   winner_name = PlayerList[i]->get_name();
			   }
		   }
	   }
	   cout << "The game is over." << endl;
	   for (int i = 0; i < 4; i++)
	   {
		   if (PlayerList[i]->get_player_points() > maxscore)
		   {
			   cout << PlayerList[i]->get_name() << " has exceeded " << maxscore << " points." << endl;
		   }
	   }
	   cout << "The winner is " << winner_name << endl;

	   for(int i = 0; i < (int) PlayerList.size(); i++)
	   {
         delete PlayerList.at(i);
	   }
      return 0;
}



