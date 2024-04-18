#ifndef __CALENDAR_H__
#define __CALENDAR_H__
#include"Game.h"

class Calendar {
    public:
        int year;
        int month;
        int day;
    Calendar() {
        year = 2023;
        month = 10;
        day = 1;
    }
    void update_calendar() {
        // go to the next day
        day++;
        // go to the next month if needed
        if (day > 31) {
            day = 1;
            month++;
            // go to the next year if needed
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
};

#endif