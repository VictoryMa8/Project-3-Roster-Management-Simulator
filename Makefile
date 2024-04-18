new_nba_sim: new_nba_sim.o
	g++ -Wall new_nba_sim.o -o new_nba_sim

new_nba_sim.o: new_nba_sim.cpp Player.h Team.h
	g++ -Wall -c new_nba_sim.cpp