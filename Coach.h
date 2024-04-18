#ifndef __COACH_H__
#define __COACH_H__
#include <string>
#include"Player.h"

class Coach : public Player {
    public:
        std::string coach_name;
        double modifier;

        Coach(std::string cn, double mod) : 
            Player("", 0, 0, "Coach", false, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), coach_name(cn), modifier(mod)
        {
        }
        double get_modifier() const {
            return modifier;
        }
        void display_stats() { // virtual function
            std::cout << "Name: " << coach_name << std::endl;
            std::cout << "Coach Modifier: " << modifier << std::endl;
        }
};

#endif