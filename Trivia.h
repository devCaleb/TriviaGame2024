#pragma once

#ifndef __TRIVIA_H__
#define __TRIVIA_H__

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

class Trivia {
public:
	Trivia(); //constructor
	~Trivia(); //destructor
	bool init();
	vector<vector<string>>* parseTriviaFile(string fileLocation);
	vector<string>* getQuestion();

	vector<vector<string>>* questions;
	int lastAsked = -1;
};

#endif