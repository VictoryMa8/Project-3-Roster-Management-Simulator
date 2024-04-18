# default

Members: Ian, Jimmy, & Victor

In order to run the latest version, type:

g++ -g -Wall -c new_nba_sim.cpp
g++ -g -Wall new_nba_sim.o /usr/local/cs/cs251/react.o -lcurl
./a.out

There will be a welcome screen, where the user presses enter to start the game.
The first part of the game is selecting the user's team.
The user can browse the teams according to their conference and division.
There is a option to go back on each screen for convenience.
After the user selects their team, they have an option to confirm or go back to the start.
Once they confirm and go to the main menu, there will be eight options for them to choose from in order to manage their team.

1) Your Team Summary
2) View Rosters & Player Statistics
3) Trade For Players
4) Check The Standings
5) Simulate The Next Game
6) Player Development 
7) Find A New Coach
8) Save / Load Game

Input the numbers to choose the options.

The first option allows the user to see their team's name, head coach, arena, and names of their players.
There is an option to go back to the main screen by inputting 2.

The second option goes to a screen that has all 30 teams of the NBA.
The user may input the number shown next to the team's name to view their statistics, or input 31 to go back.
The screen of each team shows the name, head coach, arena, player names, and player statistics which include:
Height, age, position, points, rebounds, assists field goal percentage, free throw percentage, 
three point percentage, steals per game, blocks per game, and turnovers per game.
One thing to note is that these statistics are randomly generated at the start, and are realistic numbers compared to NBA averages.
There is an option to go back by inputting 1.

The third option allows the user to trade for a player on another team, there is an option to go back by inputting 31.
The first screen shows all 30 teams of the NBA, and the user may select one by inputting a number from 1 to 30.
The second screen shows the names of all 15 players on the selected team, the user may select a player by inputting a number from 1 to 15.
The third screen shows the names of all 15 players on the user's team, the user may select a player in order to switch for the other team's player.
The fourth screen shows that the trade was successful, and allows the user to go back to the main menu.

The fourth option allows the user to view the standings. 
They are able to see all the wins and losses of each team.
The statistics are updated after each game is played.

The fifth option allows the user to simulate a game for their team and another game for two other random teams.
The screen allows the user to go back by inputting 2.
The screen shows the date, where the game is held, and the user's opponent.
After that, it also shows the win probability for each of the teams, and then the result.
Finally, it also shows the result of the random non-user game and the probability of the winning team's chance to win.

The sixth option allows the user to develop one of their players or go back by inputting 16.
When the user selects a player by inputting a number from 1 to 15, that player starts their training.
There will be a confirmation screen where the user can input 1 to go back to the main menu.
Their training lasts for 5 days, and in the 'simulate game' screen, it will display whether their training is still ongoing or completed.
Once their training is completed, the 'simulate game' screen will show the difference in their statistical values.
Training allows for a player to increase their statistical values, this can be done multiple times for multiple players.

The seventh option allows the user to find a new coach to start coaching their team.
The user can select from 10 different coaches who have different 'modifiers'
The modifiers multiply the statistical values of all players on the user's roster.
The user can replace their coach however many times they want.

The eighth option allows the user to save their game, or load a previous save file.

This NBA simulator aims to give the user a fun experience with trading players, simulating games, training players, hiring new coaches, 
and finding ways to optimize one's own NBA team.