#ifndef __TRADES_H__
#define __TRADES_H__

#include "Team.h"
#include "Player.h"

class Trade {
public:
    Team* my_team;
    Team* other_team;

    Trade(Team* mine, Team* theirs) : my_team(mine), other_team(theirs) {}

    void trading(Player& player, int theirPlayerIndex, int yourPlayerIndex) {
        if (theirPlayerIndex >= 0 && theirPlayerIndex < 15 && other_team->roster[theirPlayerIndex] != nullptr &&
            yourPlayerIndex >= 0 && yourPlayerIndex < 15 && my_team->roster[yourPlayerIndex] != nullptr) {



            // Swap the players between the teams
            std::swap(other_team->roster[theirPlayerIndex], my_team->roster[yourPlayerIndex]);
        }
    }
};

#endif