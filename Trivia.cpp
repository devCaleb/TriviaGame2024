#include "Trivia.h"

Trivia::Trivia() { //Default Class Contructor
    if (!this->init()) {
        cout << "ERROR: TRIVIA FILE FAILED TO LOAD" << endl;
    }
    else {
        cout << "Questions loaded successfully!" << endl;
    }
}

Trivia::~Trivia() { //Default Class Destructor

}

//Initialize the trivia controller
bool Trivia::init() {
	cout << "Loading trivia data...." << endl;

    this->questions = parseTriviaFile("D:/Alert5Studios/TriviaGame/questions.txt");

    if (this->questions->size() > 0) {
        return true;
    }

	return false;
}

//Load the trivia file into the game
vector<vector<string>>* Trivia::parseTriviaFile(string fileLocation) {
    path path = fileLocation;

    ifstream f(path, ios::in | ios::binary);
    const auto sz = file_size(path);
    string result(sz, '\0');
    f.read(result.data(), sz);

    vector<vector<string>>* data = new vector<vector<string>>();
    vector<string> question = vector<string>();

    for (int i = 0; i < result.size() - 1; i++) {
        if (result.substr(i, 5) == "<EOF>")
        {
            if (question.size() > 0) {
                data->push_back(question);
                break;
            }
        }

        if (result.substr(i, 3) == "<Q>") { //Start of a question
            if (question.size() > 0) {
                data->push_back(question);
                question.clear();
            }

            string nextBlock = string();
            string val = string();

            i += 3;
            while (nextBlock != (string)"</>") {
                val.append(result.substr(i, 1));

                nextBlock = result.substr(i + 1, 3);
                i++;
            }

            i += 3; //Skip to the next block
            question.push_back(val);
        }
        else if (result.substr(i, 3) == "[A]" || result.substr(i, 3) == "[E]" || result.substr(i, 3) == "[V]" || result.substr(i, 1) == "[") {
            string nextBlock = string();
            string val = string();
            
            i += 3;
            while (nextBlock != (string)"[/]") {
                val.append(result.substr(i, 1));

                nextBlock = result.substr(i + 1, 3);
                i++;
            }

            i += 3; //Skip to the next block
            question.push_back(val);
        }
    }

    return data;
}

//Gets a question from the controller
vector<string>* Trivia::getQuestion() {
    vector<string>* q = &this->questions[0][this->lastAsked + 1];
    this->lastAsked++;
    return q;
}