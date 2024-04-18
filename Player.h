#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>

class Player {
    public:
        std::string player_name;
        int height_cm;
        int age;    
        std::string position;
        bool injured;
        double points_per_game;
        double rebounds_per_game;
        double assists_per_game;
        double field_goal_percentage;
        double free_throw_percentage;
        double three_point_percentage;
        double steals_per_game;
        double blocks_per_game;
        double turnovers_per_game;
        Player(std::string n, double hc, double a, std::string pos, bool inj, double ppg, double rpg, double apg, double fgp, double ftp, double tpg, double spg, double bpg, double tov) {
            player_name = n;
            height_cm = hc;
            age = a;
            position = pos;
            injured = inj;
            points_per_game = ppg;
            rebounds_per_game = rpg;
            assists_per_game = apg;
            field_goal_percentage = fgp;
            free_throw_percentage = ftp;
            three_point_percentage = tpg;
            steals_per_game = spg;
            blocks_per_game = bpg;
            turnovers_per_game = tov;
            // 14 statistical values
        }
        void display_stats() {
            std::cout << "Name: " << player_name << std::endl;
            std::cout << "Height: " << height_cm << " cm" << std::endl;
            std::cout << "Age: " << age << " years old" << std::endl;
            std::cout << "Position: " << position << std::endl;
            std::cout << "Injured: " << injured << std::endl;
            std::cout << "Points per game: " << points_per_game << std::endl;
            std::cout << "Rebounds per game: " << rebounds_per_game << std::endl;
            std::cout << "Assists per game: " << assists_per_game << std::endl;
            std::cout << "Field Goal Percentage: " << field_goal_percentage << std::endl;
            std::cout << "Free Throw Percentage: " << free_throw_percentage << std::endl;
            std::cout << "Three-Point Percentage: " << three_point_percentage << std::endl;
            std::cout << "Steals per game: " << steals_per_game << std::endl;
            std::cout << "Blocks per game: " << blocks_per_game << std::endl;
            std::cout << "Turnovers per game: " << turnovers_per_game << std::endl;
        }
};

#endif