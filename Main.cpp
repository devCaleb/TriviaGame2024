
/*
Author: Caleb Watson

Possible future improvements:

Different game modes, like a short game (10 questions), medium game (20 question), etc. or a challenge mode where it goes through all of the questions in the file
Better player tracking, like having an "account" for each player name that can keep track of their game history and past scores
    This would probably just be something like a txt file with an array of names and scores where each unique name has
    its own array of scores associated with it. To "login" the player would just use the unique name at the beginning of the game
*/

#include <iostream>
#include <string>
#include <Windows.h>

#include "Game.h"
#include "Trivia.h"

using namespace std;

Trivia* trivia;
Game* game;

vector<string>* question;
bool qActive = false;

bool quitter = false;

//Clears the terminal
void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

//Reset the stats for a new game
void resetGame() {
    trivia->lastAsked = -1;
    game->gameStarted = false;
    game->plrScore = 0;
}

//Ask the player a question
void askQuestion() {
    ClearScreen();
    if (trivia->lastAsked != trivia->questions->size() - 1) {
        question = trivia->getQuestion();
        qActive = true; //Signal the main loop to expect a response from the user

        //Display the players current score
        cout << game->plrName << "'s Score: " << to_string(game->plrScore) << "\n\n";

        //Display the question to the user
        cout << "Value: " << question[0][1] << endl;
        cout << question[0][0] << endl << endl;
        int n = 1;
        for (int i = 4; i < question[0].size(); i++) {
            cout << to_string(n) << ") " << question[0][i] << endl;
            n++;
        }
    }
    else {
        cout << "GAME OVER" << endl;
        cout << "Thanks for playing!\n\n";
        cout << "Your final score was: " << to_string(game->plrScore) << endl << endl;

        cout << "Do you want to play again?\n\n";
        cout << "1) Yes!\n";
        cout << "2) No :(\n";

        resetGame();
    }
}

int main()
{
    //Create the trivia controller instance, used to handle questions
    trivia = new Trivia();

    //Create the game instance. We will use this to store basic information about this game session.
    game = new Game(); //Calling the constructor for this class also sets up this game session.

    //game main loop
    string data;
    while (cin >> data) {
        if (game->gameStarted == false) {
            if (data == "1") {
                game->gameStarted = true;
                askQuestion(); //Start the game
            }
            else {
                if (!quitter) {
                    cout << "When you are ready, respond with 1\n";
                }
                else {
                    break;
                }
            }
        }
        else {
            if (qActive == true) {
                if (data == question[0][2]) { //If it is the correct answer
                    cout << "\nCorrect!" << endl;
                    cout << question[0][3] << endl << endl; //Explaination
                    cout << "Are you ready for the next question?\n\n1) Yes!\n2) No I want to quit :(" << endl;
                    game->plrScore += stoi(question[0][1]); //Add the value to the players score
                    qActive = false;
                }
                else {
                    cout << "\nUh-oh, looks like you got that one wrong!" << endl;
                    cout << "The correct answer was: " << question[0][2] << endl;
                    cout << question[0][3] << endl << endl; //Explaination
                    cout << "Are you ready for the next question?\n\n1) Yes!\n2) No I want to quit :(" << endl;
                    qActive = false;
                }
            }
            else {
                if (data == "1") {
                    askQuestion();
                }
                else {
                    resetGame();
                    quitter = true;

                    ClearScreen();

                    cout << "Wow, I didn't realize I was dealing with such a quitter!" << endl;
                    cout << "Do you want to try again?\n\n";
                    cout << "1) Yes, I want to redeem myself!\n";
                    cout << "2) No, I want to quit like a loser :(\n";
                }
            }
        }
    }

    return 0;
}