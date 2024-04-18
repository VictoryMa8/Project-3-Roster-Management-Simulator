#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include"Player.h"
#include"Team.h"
#include"Calendar.h"

class Game {
    public:
        Team* home_team;
        Team* away_team;

    Game(Team& home, Team& away) {
        home_team = &home;
        away_team = &away;

    }
    void play_game(Calendar& calendar) {
        std::cout << "The date is: " << calendar.month << "-" << calendar.day << "-" << calendar.year << std::endl;
        std::cout << "Game at: " << home_team->arena<< std::endl;
        std::cout << home_team->name << " vs. " << away_team->name << std::endl;
        double home_team_rating = home_team->calculate_team_rating();
        double away_team_rating = away_team->calculate_team_rating();
        // probability calculations
        double home_win_probability = home_team_rating / (home_team_rating + away_team_rating);
        double away_win_probability = 1.0 - home_win_probability;
        srand(static_cast<unsigned int>(time(nullptr)));
        double random_value = static_cast<double>(rand()) / RAND_MAX; // random value
        std::cout << home_team->name << " win probability: " << home_win_probability * 100 << "%" << std::endl;
        std::cout << away_team->name << " win probability: " << away_win_probability * 100 << "%" << std::endl;
        // winner and loser
        if (random_value < home_win_probability) {
            home_team->wins++;
            away_team->losses++;
            std::cout << home_team->name << " wins against the " << away_team->name << " at home." << std::endl;
        }
        else {
            home_team->losses++;
            away_team->wins++;
            std::cout << away_team->name << " wins against the " << home_team->name << " on the road." << std::endl;
        }

        static int game_count = 0;
        game_count++;

        if (game_count % 5 == 0) {
            calendar.update_calendar();
        }
    }
    void non_user_play_game() {
        double home_team_rating = home_team->calculate_team_rating();
        double away_team_rating = away_team->calculate_team_rating();
        // probability calculations
        double home_win_probability = home_team_rating / (home_team_rating + away_team_rating);
        srand(static_cast<unsigned int>(time(nullptr)));
        double random_value = static_cast<double>(rand()) / RAND_MAX; // random value
        // winner and loser
        if (random_value < home_win_probability) {
            home_team->wins++;
            away_team->losses++;
            std::cout << home_team->name << " wins against the " << away_team->name << " at home with a " << home_win_probability * 100 << "% " << "chance to win." << std::endl;
        }
        else {
            home_team->losses++;
            away_team->wins++;
            std::cout << away_team->name << " wins against the " << home_team->name << " on the road with a " << (1.0 - home_win_probability) * 100 << "% " << "chance to win." << std::endl;
        }
    }
};

// in main write: Calendar season_calendar;
// use the play_game function like this: play_game(season_start);

#endif