#ifndef __TEAM_H__
#define __TEAM_H__
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include"Player.h"
#include"Coach.h"

class Team {
    public:
        std::string name;
        Coach coach;
        std::string arena;
        int wins;
        int losses;
        int total_games;
        Player* roster[15];
        Team() : coach("", 1.0) {
            name = "";
            arena = "";
            wins = 0;
            losses = 0;
            total_games = 0;
            for (int i = 0; i < 15; ++i) {
                roster[i] = nullptr;
            }
        
        }
        Team(const std::string tn, const Coach& tc, const std::string ta) : coach(tc) {
            name = tn;
            arena = ta;
            wins = 0;
            losses = 0;
            total_games = 0;
            for (int i = 0; i < 15; ++i) {
                roster[i] = nullptr;
            }
        }
        ~Team() {
            for (int i = 0; i < 15; ++i) {
                delete roster[i];
            }
        }
        static int random_num() {
            static bool initialized = false;
            if (!initialized) {
            srand(static_cast<unsigned int>(time(nullptr)));
            initialized = true;
            }       
            return rand() % 30;
        }
        void add_player(int i, std::string n, int hc, int a, std::string pos, bool inj, double ppg, double rpg, double apg, double fpg, double ftp, double tpg, double spg, double bpg, double tov) {
            if (roster[i] == nullptr) {
                roster[i] = new Player(n, hc, a, pos, inj, ppg, rpg, apg, fpg, ftp, tpg, spg, bpg, tov);
            }
            else {
                std::cout << "Player already exists at roster position" << std::endl;
            }
        }
        
        static Team* initialize_NBA() {
            std::string team_names[30] = {
                "Atlanta Hawks", "Boston Celtics", "Brooklyn Nets", "Charlotte Hornets", "Chicago Bulls",
                "Cleveland Cavaliers", "Dallas Mavericks", "Denver Nuggets", "Detroit Pistons", "Golden State Warriors", "Houston Rockets",
                "Indiana Pacers", "Los Angeles Clippers", "Los Angeles Lakers", "Memphis Grizzlies", "Miami Heat", "Milwaukee Bucks", "Minnesota Timberwolves",
                "New Orleans Pelicans", "New York Knicks", "Oklahoma City Thunder", "Orlando Magic", "Philadelphia 76ers", "Phoenix Suns",
                "Portland Trail Blazers", "Sacramento Kings", "San Antonio Spurs", "Toronto Raptors", "Utah Jazz", "Washington Wizards"};
            std::string arena_names[30] = {
                "State Farm Arena", "TD Garden", "Barclays Center", "Spectrum Center", "United Center",
                "Rocket Mortgage FieldHouse", "American Airlines Center", "Ball Arena", "Little Caesars Arena", "Chase Center", "Toyota Center",
                "Bankers Life Fieldhouse", "Staples Center", "Crypto.com Arena", "FedExForum", "FTX Arena", "Fiserv Forum", "Target Center",
                "Smoothie King Center", "Madison Square Garden", "Paycom Center", "Amway Center", "Wells Fargo Center", "Footprint Center",
                "Moda Center", "Golden 1 Center", "AT&T Center", "Scotiabank Arena", "Vivint Arena", "Capital One Arena"};
            std::string coach_names[30] = {
                "Nate McMillan", "Ime Udoka", "Steve Nash", "James Borrego", "Billy Donovan",
                "J.B. Bickerstaff", "Jason Kidd", "Michael Malone", "Dwane Casey", "Steve Kerr", "Stephen Silas",
                "Rick Carlisle", "Tyronn Lue", "Frank Vogel", "Taylor Jenkins", "Erik Spoelstra", "Mike Budenholzer", "Chris Finch",
                "Willie Green", "Tom Thibodeau", "Mark Daigneault", "Jamahl Mosley", "Doc Rivers", "Monty Williams",
                "Chauncey Billups", "Alvin Gentry", "Gregg Popovich", "Nick Nurse", "Quin Snyder", "Wes Unseld Jr."};               
                Team* team_list = new Team[30];
                for (int i = 0; i < 30; ++i) {
                    std::string coach_name = coach_names[i];
                    Coach coach(coach_name, 1.0);
                    team_list[i] = Team(team_names[i], coach, arena_names[i]); // placeholders for coach and arena
                }
                return team_list;
            }
        static void delete_teams(Team* teams) {
            delete [] teams;
        }
        // new initialize_roster()
        void initialize_roster() {
            std::random_device rd; // random device to seed the generator
            std::mt19937 gen(rd()); // generator
            std::string positions[] = {"PG", "SG", "SF", "PF", "C"};
            std::string player_names[15] = {"Player1", "Player2", "Player3", "Player4", "Player5", "Player6", "Player7",
            "Player8", "Player9", "Player10", "Player11", "Player12", "Player13", "Player14", "Player15"};
            for (int i = 0; i < 15; ++i) {
                if (roster[i] == nullptr) {
                std::string unique_player_name = name + "_" + player_names[i];
                // generate random stats
                double ht = 180 + static_cast<int>(gen() % 20);
                int ag = 20 + static_cast<int>(gen() % 10);
                std::string po = positions[gen() % 5];
                bool ij = false;
                double pp = 15.0 + (gen() % 100) / 10.0;
                double rp = 5.0 + (gen() % 50) / 10.0;
                double ap = 5.0 + (gen() % 50) / 10.0;
                double fg = 40.0 + (gen() % 200) / 10.0;
                double ft = 70.0 + (gen() % 200) / 10.0;
                double th = 30.0 + (gen() % 100) / 10.0;
                double st = 1.0 + (gen() % 20) / 10.0;
                double bp = 1.0 + (gen() % 20) / 10.0;
                double tp = 1.0 + (gen() % 20) / 10.0;
                add_player(i, unique_player_name, ht, ag, po, ij, pp, rp, ap, fg, ft, th, st, bp, tp);
                }
            }
        } 
        void display_team_info() {
            std::cout << "Team Name: " << name << std::endl;
            std::cout << "Coach: " << coach.coach_name << std::endl;
            std::cout << "Arena: " << arena << std::endl;
            std::cout << "Players: " << std::endl;
            for (int i = 0; i < 15; ++i) {
                if (roster[i] != nullptr) {
                    std::cout << "Player Name: " << roster[i]->player_name << std::endl;
                }
                else {
                    std::cout << "No player at index " << i << std::endl;
                }
            }
        }
        double calculate_team_rating() {
            double total_rating = 0.0;
            for (int i = 0; i < 15; ++i) {
                if (roster[i] != nullptr) {
                    total_rating += roster[i]->points_per_game;
                    total_rating += roster[i]->rebounds_per_game;
                    total_rating += roster[i]->assists_per_game;
                    total_rating += roster[i]->steals_per_game;
                    total_rating += roster[i]->blocks_per_game;
                }
            }
            return total_rating;
        }
        void apply_modifier() {
            double coach_modifier = coach.modifier;
            for (int i = 0; i < 15; ++i) {
                if (roster[i] != nullptr) {
                    roster[i]->points_per_game *= coach_modifier;
                    roster[i]->rebounds_per_game *= coach_modifier;
                    roster[i]->assists_per_game *= coach_modifier;
                }
            }
        }
        
};

#endif