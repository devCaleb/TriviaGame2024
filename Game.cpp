#include "Game.h"

Game::Game() { //Class Default Constructor
    //TODO: Load player stats

    this->init(); //Get the game rolling
}

Game::~Game() { //Class Destructor

}

//Load the players.txt file
vector<vector<string>>* Game::parsePlayerFile(string filelocation) {
    path path = filelocation;

    ifstream f(path, ios::in | ios::binary);
    const auto sz = file_size(path);
    string result(sz, '\0');
    f.read(result.data(), sz);

    vector<vector<string>>* data = new vector<vector<string>>();


    if (result.size() > 0) { //If the file isn't empty
        for (int i = 0; i < result.size() - 1; i++) {

        }
    }

    return data;
}

//Load the players profile, or create a new one
vector<vector<string>>* Game::getPlayer(string name) {
    vector<vector<string>>* plrList = this->parsePlayerFile("D:/Alert5Studios/TriviaGame/players.txt");


}

//Initialize the game controller instance
void Game::init() {
    cout << "Welcome to this game of trivia!\n";
    cout << "Please enter your name so we know who to attribute your score to:\n";

    //Get the player's Name
    while (cin >> this->plrName)
    {
        if (this->plrName == "" || empty(this->plrName)) {
            cout << "Please enter valid data...\n";
            cout << "Please enter your name so we know who to attribute your score to:\n";
        }
        else {
            this->getPlayer(this->plrName);
            break;
        }
    }

    cout << "Thanks for playing " << this->plrName << endl;

    cout << "Please read these instructions carefully:\n\n";
    cout << "Each round I will ask you a multiple choice trivia question.\n";
    cout << "Answer with the number of your answer and nothing else.\n";
    cout << "Each question will have a value, if you get the question correct the value is added to your score.\n";
    cout << "Here is an example question:\n\n";
    cout << "Value: 100\n";
    cout << "WWII ended in which year?\n\n";
    cout << "1) 1943\n";
    cout << "2) 1944\n";
    cout << "3) 1945\n";
    cout << "4) 1946\n\n";

    cout << "In this example you would answer with: 2\n\n";

    cout << "Are you ready to begin?\n";
    cout << "1) Yes!\n";
    cout << "2) No :(\n";
}