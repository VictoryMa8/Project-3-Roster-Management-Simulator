#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include"Player.h"
#include"Team.h"
#include"Game.h"
#include"Trades.h"
#include"Calendar.h"
#include"Coach.h"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

// NBA simulator 
// Created by Jimmy, Victor, & Ian

// state class used in conjunction with screen_num
class State {
    int screen_num;
  public:
    State(istream &is) { is >> screen_num; }

    int get_screen_num() const { return screen_num; }

    void write_to(ostream &os) const { os << screen_num << endl; }

    void update(string input, istream &is);

};

// global variables
Team* nba_teams = Team::initialize_NBA();
Team* selected_team;
int screen_num = 0;
const int limit = 26; 
string text[limit];
bool react = false;
int selectedTeamIndex;
int selectedPlayerIndex;
const int input_index = 2, prompt_index = 26;
Calendar nba_calendar = Calendar();
Team* nair;
int selected_player = -1;
Coach coach_list[10] = { {"Bob", 1.0}, {"Joe", 1.2}, {"James", 1.1}, {"Charlie", 1.3}, {"Ronald", 1.0}, {"Michael", 0.9},
        {"Jimmy", 1.2}, {"Ian", 1.4}, {"Hank", 1.1}, {"Victor", 1.5} };
int selected_coach;
int training_counter = 0;
int view_roster_index;
string mySelectedTraded;
string yourSelectedTraded;
int xx;
int yy;

// read text data from new_nba_sim.txt
void read_text_data() {
  for (int i = 0; i < 30; ++i) {
  nba_teams[i].initialize_roster();
  }
  ifstream fs("new_nba_sim.txt");
  string comment;
  for (int i = 0; i < limit; ++i) {
	  getline(fs, text[i], '#');
	  text[i].pop_back();
	  getline(fs, comment);
  }
}

// display screen number and screen specific text
void display_text(const State &state, ostream &os) {
    int n = state.get_screen_num();
    if (react) {
	    _add_yaml("story.yaml", {{"prompt_index", prompt_index},
   	          	{"input_index", input_index}});
	  os << "~~~~~~~~~~~~~~~~~~~~~~~~~";  // 25 bytes of filler
    } else os << "\033c";

    os << "               	"
        << "[screen " << n << "]" << endl
 	      << text[n];

    if (state.get_screen_num() == 11) { // welcome screen
      os << "You selected the: " << selected_team->name << endl;
    }

    if (state.get_screen_num() == 13) { // user's team summary
      os << "Your Team Name: " << selected_team->name << endl;
      os << "Your Current Head Coach: " << selected_team->coach.coach_name << endl;
      os << "Your Team's Arena: " << selected_team->arena << endl;
      os << "Your Players: " << endl;
            for (int i = 0; i < 15; ++i) {
                if (selected_team->roster[i] != nullptr) {
                    os << i+1 << ") " << selected_team->roster[i]->player_name << endl;
                }
                else {
                    os << "No player at index " << i << endl;
                }
            }
    }

    if (state.get_screen_num() == 14) { // view the rosters of all 30 teams
    for (int i = 0; i < 30; ++i) {
        os << i + 1 << ")" << " " << nba_teams[i].name << endl;
        }
    }

    if (state.get_screen_num() == 15) { // trading screen
    for (int i = 0; i < 30; ++i) {
       os << i + 1 << ")" << " " << nba_teams[i].name << endl;
       }
    os << "Select a team to trade with (1-30): ";
    }

    if (state.get_screen_num() == 16) { // check the current team standings
      for (int i = 0; i < 30; ++i) {
        os << i+1 << ")" << " " << nba_teams[i].name << " " << "..." << " " << "Wins: " << nba_teams[i].wins << " " << "|" << " " << "Losses: " << nba_teams[i].losses << endl;
      }
    }

    if (state.get_screen_num() == 17) { // 17 game simulation screen, displays a user game and another random game
    int r, r1, r2; // initialize numbers
    if (selected_player != -1) {
    if (training_counter < 5) {
      os << "Your player " << selected_team->roster[selected_player-1]->player_name << " is still training!" << endl;
    } else {
      os << "Your player " << selected_team->roster[selected_player-1]->player_name << " has completed training!" << endl;
      training_counter = 0;
      os << "Your player's stats increased!" << endl;
      os << "Old points per game: " << selected_team->roster[selected_player-1]->points_per_game << endl;
      os << "Old rebounds per game: " << selected_team->roster[selected_player-1]->rebounds_per_game << endl;
      os << "Old assists per game: " << selected_team->roster[selected_player-1]->assists_per_game << endl;
      selected_team->roster[selected_player-1]->points_per_game *= 1.5;
      selected_team->roster[selected_player-1]->rebounds_per_game *= 1.5;
      selected_team->roster[selected_player-1]->assists_per_game *= 1.5;
      os << "New statistics: " << selected_team->roster[selected_player-1]->points_per_game << ", " << selected_team->roster[selected_player-1]->rebounds_per_game << ", " << selected_team->roster[selected_player-1]->assists_per_game << endl;
      selected_player = -1;
    }
    }
    training_counter++;
    // user vs bot
    do {
      r = Team::random_num();
    } while (&nba_teams[r] == selected_team); // repeat if team plays itself

      Game user_vs_other(*selected_team, nba_teams[r]);
      user_vs_other.play_game(nba_calendar); 

    os << "          < < < Another game that was played today: > > >         " << endl;

    // bot game 1
    r1 = Team::random_num();
    do {
      r2 = Team::random_num();
    } while (r1 == r2);
      Game game1(nba_teams[r1], nba_teams[r2]);
      game1.non_user_play_game();
    }

    if (state.get_screen_num() == 18) { // 2nd part of the trading screen
      os << "Pick the player you want to get" << endl;
      for (int i = 0; i < 15; ++i) {
        os << i + 1 << ")" << " " << nair->roster[i]->player_name << endl;
   }
      // get the user's choice of player to trade
   
       os << "Select a player to trade (1-15): ";
     


    }

    if (state.get_screen_num() == 19){
      for (int i = 0; i < 15; ++i) {
        os << i+1 << ") " << selected_team->roster[i]->player_name << endl;
   }
      // get the user's choice of player to trade

      os << "Select a player on your team to trade (1-15): ";

      if (selectedPlayerIndex >= 1 && selectedPlayerIndex <= 15) {
           // perform the trade using the trade class
        Trade trade(nair, &nba_teams[selectedTeamIndex - 1]);
        trade.trading(*nair->roster[selectedPlayerIndex - 1], -1, selectedPlayerIndex - 1);
       }
    }

  if (state.get_screen_num() == 20) { // 3rd part of the trade screen
    os << endl;
    os << endl;
    swap(nair->roster[selectedPlayerIndex + xx], selected_team->roster[selectedPlayerIndex + yy]);
    os << "Trade was successful" << endl;

   

 








  }

  if (state.get_screen_num() == 21) { // player development
      os << "Player Name" << " " << "Position" << " " << "Points" << " " << "Rebounds" << " " << "Assists" << " " << "FG%" << " " << "FT%" << " " << "3P%" << " " << "Steals" << " " << "Blocks" << " " << "Turnovers" << endl;
      for (int i = 0; i < 15; ++i) {
        Player* x = selected_team->roster[i];
        os << i+1 << ") " << x->player_name << " " << x->position << " " << x->points_per_game << " " << x->rebounds_per_game << " " << x->assists_per_game << " " << x->field_goal_percentage << " " << x->free_throw_percentage << " " << x->three_point_percentage << " " << x->steals_per_game << " " << x->blocks_per_game << " " << x->turnovers_per_game << endl;
      }
  }

  if (state.get_screen_num() == 22) { // find a new coach
        for (int i = 0; i < 10; ++i) {
          os << i+1 << ") " << coach_list[i].coach_name << " ... " << "Modifier: " << coach_list[i].modifier << endl;
        }
  }
  if (state.get_screen_num() == 23) { // 2nd part of player development
      os << "You successfully selected " << selected_team->roster[selected_player-1]->player_name << " to start training." << endl;
  }

  if (state.get_screen_num() == 24) { // 2nd part of finding a new coach
      selected_team->coach = coach_list[selected_coach-1];
      for (int i = 0; i < 15; ++i) {
        Player* x = selected_team->roster[i];
        x->points_per_game *= selected_team->coach.modifier;
        x->rebounds_per_game *= selected_team->coach.modifier;
        x->assists_per_game *= selected_team->coach.modifier;
      }
      os << "You successfully selected " << coach_list[selected_coach-1].coach_name << " to start coaching your team." << endl;
      os << "Check your roster to see the updated stats from your coach's modifier!" << endl;
  }

if (state.get_screen_num() == 25) {
      os << "Showing team information for the: " << nba_teams[view_roster_index-1].name << endl;
      os << "Head Coach: " << nba_teams[view_roster_index-1].coach.coach_name << endl;
      os << "Arena: " << nba_teams[view_roster_index-1].arena << endl;
      os << "Roster: " << endl;
      os << " " << endl;
      os << "Player Name " << "Height " << "Age " << "Position " << "Points " << "Rebounds " << "Assists " << "FG% " << "FT% " << "3P% " << "Steals " << "Blocks " << "Turnovers " << endl;
            for (int i = 0; i < 15; ++i) {
                if (nba_teams[view_roster_index-1].roster[i] != nullptr) {
                    os << i+1 << ") " << nba_teams[view_roster_index-1].roster[i]->player_name << " " << nba_teams[view_roster_index-1].roster[i]->height_cm << " " << nba_teams[view_roster_index-1].roster[i]->age 
                    << " " << nba_teams[view_roster_index-1].roster[i]->position << " " 
                    << nba_teams[view_roster_index-1].roster[i]->points_per_game << " " << nba_teams[view_roster_index-1].roster[i]->assists_per_game << " " 
                    << nba_teams[view_roster_index-1].roster[i]->field_goal_percentage << " " << nba_teams[view_roster_index-1].roster[i]->free_throw_percentage << " " << nba_teams[view_roster_index-1].roster[i]->three_point_percentage << " " 
                    << nba_teams[view_roster_index-1].roster[i]->steals_per_game << " " << nba_teams[view_roster_index-1].roster[i]->blocks_per_game << " " << nba_teams[view_roster_index-1].roster[i]->turnovers_per_game << endl;
                }
                else {
                    os << "No player at index " << i << endl;
                }
            }
}
if (state.get_screen_num() == 26){
  os << "loos here" << endl;
}

    if (react) os << '\0';  // provide ending null-byte
    else if (n >= limit) exit(0);
}
// used to be called update_screen_num
void State::update(string input, istream &is) {
  if (react && _received_event()) {
  	// get input from the stream
	  is.get(); is.get();  // skip first two characters
  	if ('~' != is.peek()) getline(is, input, '\0');
  }

  if (0 == screen_num) {
    screen_num = 1;
    }
  else if (1 == screen_num) screen_num = 2;
  else {
	int input_num = stoi(input);
	if (2 == screen_num) { // user chooses conference
  	  if (1 == input_num) screen_num = 3; 
  	  else screen_num = 4;
	} 
	else if (3 == screen_num) { // eastern conference screen
  	  if (1 == input_num) screen_num = 5; 
  	  else if (2 == input_num) screen_num = 6; 
	  else if (3 == input_num) screen_num = 7; 
    else if (4 == input_num) screen_num = 2;
	} 

	else if (4 == screen_num){ // western conference screen
  	  if (1 == input_num) screen_num = 8;
	    else if (2 == input_num) screen_num = 9;
  	  else if (3 == input_num) screen_num = 10;
      else if (4 == input_num) screen_num = 2; 
	}  
  else if (screen_num >= 5 && screen_num <= 7){
    if (6 == input_num) screen_num = 3; 
    else { // nba_team[] corresponds to each of the 30 nba teams
      if (screen_num == 5 && input_num == 1) {
        selected_team = &nba_teams[1];
      }
      if (screen_num == 5 && input_num == 2) {
        selected_team = &nba_teams[2];
      }
      if (screen_num == 5 && input_num == 3) {
        selected_team = &nba_teams[22];
      }
      if (screen_num == 5 && input_num == 4) {
        selected_team = &nba_teams[19];
      }
      if (screen_num == 5 && input_num == 5) {
        selected_team = &nba_teams[27];
      }
      if (screen_num == 6 && input_num == 1) {
        selected_team = &nba_teams[4];
      }
      if (screen_num == 6 && input_num == 2) {
        selected_team = &nba_teams[5];
      }
      if (screen_num == 6 && input_num == 3) {
        selected_team = &nba_teams[8];
      }
      if (screen_num == 6 && input_num == 4) {
        selected_team = &nba_teams[11];
      }
      if (screen_num == 6 && input_num == 5) {
        selected_team = &nba_teams[16];
      }
      if (screen_num == 7 && input_num == 1) {
        selected_team = &nba_teams[0];
      }
      if (screen_num == 7 && input_num == 2) {
        selected_team = &nba_teams[3];
      }
      if (screen_num == 7 && input_num == 3) {
        selected_team = &nba_teams[15];
      }
      if (screen_num == 7 && input_num == 4) {
        selected_team = &nba_teams[21];
      }
      if (screen_num == 7 && input_num == 5) {
        selected_team = &nba_teams[29];
      }
      screen_num = 11;
      }
  }
    else if (screen_num >= 7 && screen_num <= 10){
    if (6 == input_num) screen_num = 4;
    else {
      if (screen_num == 8 && input_num == 1) {
        selected_team = &nba_teams[7];
      }
      if (screen_num == 8 && input_num == 2) {
        selected_team = &nba_teams[17];
      }
      if (screen_num == 8 && input_num == 3) {
        selected_team = &nba_teams[20];
      }
      if (screen_num == 8 && input_num == 4) {
        selected_team = &nba_teams[24];
      }
      if (screen_num == 8 && input_num == 5) {
        selected_team = &nba_teams[28];
      }
      if (screen_num == 9 && input_num == 1) {
        selected_team = &nba_teams[9];
      }
      if (screen_num == 9 && input_num == 2) {
        selected_team = &nba_teams[12];
      }
      if (screen_num == 9 && input_num == 3) {
        selected_team = &nba_teams[13];
      }
      if (screen_num == 9 && input_num == 4) {
        selected_team = &nba_teams[23];
      }
      if (screen_num == 9 && input_num == 5) {
        selected_team = &nba_teams[25];
      }
      if (screen_num == 10 && input_num == 1) {
        selected_team = &nba_teams[6];
      }
      if (screen_num == 10 && input_num == 2) {
        selected_team = &nba_teams[10];
      }
      if (screen_num == 10 && input_num == 3) {
        selected_team = &nba_teams[14];
      }
      if (screen_num == 10 && input_num == 4) {
        selected_team = &nba_teams[18];
      }
      if (screen_num == 10 && input_num == 5) {
        selected_team = &nba_teams[26];
      }
      screen_num = 11;
      }
  }
  else if(screen_num == 11){
    if (input_num == 1) screen_num = 12;
    if (input_num == 2) screen_num = 2;
    
  }
    else if (12 == screen_num){
      if (1 == input_num) screen_num = 13;
      else if(2 == input_num) screen_num = 14;
      else if(3 == input_num) screen_num = 15;
      else if(4 == input_num) screen_num = 16;
      else if (5 == input_num) screen_num = 17;
      else if (6 == input_num) screen_num = 21;
      else if (7 == input_num) screen_num = 22;
      else if (8 == input_num) screen_num = 25;
      else if (9 == input_num) screen_num = 26;
    
    }
    else if(screen_num >= 13 && screen_num <= 17) {
      if (screen_num == 13 && input_num ==2){
        screen_num = 12;
      }
      if (screen_num == 16 && input_num == 2){
        screen_num = 12;
      }
      if (screen_num == 17 && input_num == 2){
        screen_num = 12;
      }
      if (screen_num == 14) {
        if (input_num == 31) {
          screen_num = 12;
        }
        if (input_num >= 1 && input_num <= 30) {
        view_roster_index = input_num;
        screen_num = 25;
      }
      }




      if (screen_num == 15) {
        if (input_num >= 1 && input_num <= 30) {
          nair = &nba_teams[input_num - 1];
        }
      
      
      switch(screen_num){
        case 1:
          switch(input_num){
            case 1:  if (input_num == 1) {nair = &nba_teams[input_num - 1];} break;
            case 2:  if (input_num == 2) {nair = &nba_teams[input_num - 1];} break;
            case 3:  if (input_num == 3) {nair = &nba_teams[input_num - 1];} break;
            case 4:  if (input_num == 4) {nair = &nba_teams[input_num - 1];} break;
            case 5:  if (input_num == 5) {nair = &nba_teams[input_num - 1];} break;
            case 6:  if (input_num == 6) {nair = &nba_teams[input_num - 1];} break;
            case 7:  if (input_num == 7) {nair = &nba_teams[input_num - 1];} break;
            case 8:  if (input_num == 8) {nair = &nba_teams[input_num - 1];} break;
            case 9:  if (input_num == 9) {nair = &nba_teams[input_num - 1];} break;
            case 10:  if (input_num == 10) {nair = &nba_teams[input_num - 1];} break;
            case 11:  if (input_num == 11) {nair = &nba_teams[input_num - 1];} break;
            case 12:  if (input_num == 12) {nair = &nba_teams[input_num - 1];} break;
            case 13:  if (input_num == 13) {nair = &nba_teams[input_num - 1];} break;
            case 14:  if (input_num == 14) {nair = &nba_teams[input_num - 1];} break;
            case 15:  if (input_num == 15) {nair = &nba_teams[input_num - 1];} break;
            case 16:  if (input_num == 16) {nair = &nba_teams[input_num - 1];} break;
            case 17:  if (input_num == 17) {nair = &nba_teams[input_num - 1];} break;
            case 18:  if (input_num == 18) {nair = &nba_teams[input_num - 1];} break;
            case 19:  if (input_num == 19) {nair = &nba_teams[input_num - 1];} break;
            case 20:  if (input_num == 20) {nair = &nba_teams[input_num - 1];} break;
            case 21:  if (input_num == 21) {nair = &nba_teams[input_num - 1];} break;
            case 22:  if (input_num == 22) {nair = &nba_teams[input_num - 1];} break;
            case 23:  if (input_num == 23) {nair = &nba_teams[input_num - 1];} break;
            case 24:  if (input_num == 24) {nair = &nba_teams[input_num - 1];} break;
            case 25:  if (input_num == 25) {nair = &nba_teams[input_num - 1];} break;
            case 26:  if (input_num == 26) {nair = &nba_teams[input_num - 1];} break;
            case 27:  if (input_num == 27) {nair = &nba_teams[input_num - 1];} break;
            case 28:  if (input_num == 28) {nair = &nba_teams[input_num - 1];} break;
            case 29:  if (input_num == 29) {nair = &nba_teams[input_num - 1];} break;
            case 30:  if (input_num == 30) {nair = &nba_teams[input_num - 1];} break;
            break;
          }
      }
      screen_num = 18;
      if (input_num == 31){
        screen_num = 12;
      }
      }











    }
    else if (screen_num == 18) {
          if (input_num == 16) {
            screen_num = 12;
          }
          if (input_num == 1){
            xx +=0;
            mySelectedTraded = nair->roster[0]->player_name;
          }
                    if (input_num == 2){
                      xx +=1;
            mySelectedTraded = nair->roster[1]->player_name;
          }
                    if (input_num == 3){
                      xx += 2;
            mySelectedTraded = nair->roster[2]->player_name;
          }
                    if (input_num == 4){
                      xx += 3;
            mySelectedTraded = nair->roster[3]->player_name;
          }
                    if (input_num == 5){
                      xx +=4;
            mySelectedTraded = nair->roster[4]->player_name;
          }
                    if (input_num == 6){
                      xx += 5;
            mySelectedTraded = nair->roster[5]->player_name;
          }
                    if (input_num == 7){
                      xx += 6;
            mySelectedTraded = nair->roster[6]->player_name;
          }
                    if (input_num == 8){
                      xx +=7;
            mySelectedTraded = nair->roster[7]->player_name;
          }
                    if (input_num == 9){
                      xx += 8;
            mySelectedTraded = nair->roster[8]->player_name;
          }
                    if (input_num == 10){
                      xx += 9;
            mySelectedTraded = nair->roster[9]->player_name;
          }
                    if (input_num == 11){
                      xx += 10;
            mySelectedTraded = nair->roster[10]->player_name;
          }
                    if (input_num == 12){
                      xx += 11;
            mySelectedTraded = nair->roster[11]->player_name;
          }
                    if (input_num == 13){
                      xx += 12;
            mySelectedTraded = nair->roster[12]->player_name;
          }
                    if (input_num == 14){
                      xx += 13;
            mySelectedTraded = nair->roster[13]->player_name;
          }
                    if (input_num == 15){
                      xx += 14;
            mySelectedTraded = nair->roster[14]->player_name;
          }
      

            screen_num = 19;
          }
        





else if (screen_num == 19) {
          if (input_num == 16) {
            screen_num = 12;
          }
          if (input_num == 1){
            yy += 0;
            yourSelectedTraded = selected_team->roster[0]->player_name;
          }
                    if (input_num == 2){
                      yy += 1;
            yourSelectedTraded = selected_team->roster[1]->player_name;
          }
                    if (input_num == 3){
                      yy += 2;
            yourSelectedTraded = selected_team->roster[2]->player_name;
          }
                    if (input_num == 4){
                      yy += 3;
            yourSelectedTraded = selected_team->roster[3]->player_name;
          }
                    if (input_num == 5){
                      yy += 4;
            yourSelectedTraded = selected_team->roster[4]->player_name;
          }
                    if (input_num == 6){
                      yy += 5;
            yourSelectedTraded = selected_team->roster[5]->player_name;
          }
                    if (input_num == 7){
                      yy += 6;
            yourSelectedTraded = selected_team->roster[6]->player_name;
          }
                    if (input_num == 8){
                      yy += 7;
            yourSelectedTraded = selected_team->roster[7]->player_name;
          }
                    if (input_num == 9){
                      yy += 8;
            yourSelectedTraded = selected_team->roster[8]->player_name;
          }
                    if (input_num == 10){
                      yy +=9;
            yourSelectedTraded = selected_team->roster[9]->player_name;
          }
                    if (input_num == 11){
                      yy += 10;
            yourSelectedTraded = selected_team->roster[10]->player_name;
          }
                    if (input_num == 12){
                      yy += 11;
            yourSelectedTraded = selected_team->roster[11]->player_name;
          }
                    if (input_num == 13){
                      yy += 12;
            yourSelectedTraded = selected_team->roster[12]->player_name;
          }
                    if (input_num == 14){
                      yy += 13;
            yourSelectedTraded = selected_team->roster[13]->player_name;
          }
                    if (input_num == 15){
                      yy += 14;
            yourSelectedTraded = selected_team->roster[14]->player_name;
          }
      

            screen_num = 20;
          }
    else if (screen_num == 20){
      if (input_num == 1){
        screen_num = 12;
      }
    }
    else if (screen_num == 21) {
      if (input_num >= 1 && input_num <= 15) {
        selected_player = input_num;
        screen_num = 23;
      }
      if (input_num == 16) {
        screen_num = 12;
      }
    }
    else if (screen_num == 22) {
      if (input_num == 11) {
        screen_num = 12;
      }
      if (input_num >= 1 && input_num <= 10) {
        selected_coach = input_num;
        screen_num = 24;
      }
    }
    else if (screen_num == 23) {
      if (input_num == 1) {
        screen_num = 12;
      }
    }
    else if (screen_num == 24) {
      if (input_num == 1) {
        screen_num = 12;
      }
    }
    else if (screen_num == 24) {
      if (input_num == 1) {
        screen_num = 12;
      }
    }
    else if (screen_num == 25) {
      if (input_num == 1) {
        screen_num = 14;
      }
    }
  }
}

int main(int argc, char **argv) {

  react = (argc > 1);
  read_text_data();

  bool just_starting = react ? _read_event_info() : true;
  while (1) {
        ifstream fs1(just_starting ? "initial_state" : "curr_state");
        State state(fs1);
        fs1.close();

        string input;
        if (just_starting) just_starting = false;
        else if (!react) getline(cin, input);

        ifstream fs2("incoming_text");
        state.update(input, fs2);

        ofstream fs3("outgoing_text"), fs4(react ? "end_state" : "curr_state");
        display_text(state, react ? fs3 : cout);
        state.write_to(fs4);

        if (react) {
  	      _write_react_yaml();
  	      break;
        }
    }
}