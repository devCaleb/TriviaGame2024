#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

class Game {
public:
	Game(); //constructor
	~Game(); //desctructor
	void init();
	vector<vector<string>>* getPlayer(string name);
	vector<vector<string>>* parsePlayerFile(string filelocation);

	string plrName = ""; //The player's name, used for record keeping for high scores
	bool gameStarted = false; //Are we currently playing the game?
	int plrScore = 0;
};

#endif