////////////////////////////////////////////////////////
//                                                   // 
// Tahsin Mostafiz                                  //
//                                                 //
////////////////////////////////////////////////////


#include "Player.h"
#include "Trick.h"

/**Player**/

// Constructor
Player::Player(string name)
{
   player_name = name;
}

// Name getter
string Player::get_name ()
{
   return player_name;
}

// Destructor
Player::~Player ()
{}

// Player points setter
void Player::set_player_points (int points)
{
   player_points = points;
}

// Player points getter
int Player::get_player_points ()
{
   return player_points;
}

// set whether we are playing round one or not
void Player::set_is_roundone (bool first_round)
{
	is_roundone = first_round;
}

// returns a bool saying whether it is round one or not
bool Player::get_is_roundone ()
{
	return is_roundone;
}

