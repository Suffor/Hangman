#include <iostream>
#include <vector>
#include <cctype>
#include "constants.h"
#include <time.h>       

using namespace std;


string getRandomHero() {
    auto count = size(HEROS);
    srand(time(NULL));
    auto random = rand() % count;
    
    return HEROS[random];
}

class TextImg {

    vector<string> lines = {};

    public: 
        TextImg() {

        }
        TextImg* addLine(string line) {
            this->lines.push_back(line);
            return this;
        }
        void render() {
            system("cls");

            for (auto i = 0; i < this->lines.size(); i++)
            {
                auto line = this->lines.at(i);
                cout << line << endl;
            }
        }
};






template<typename Type>
bool contians(const vector<Type>* vector, Type element) {
    for (size_t i = 0; i < vector->size(); i++)
    {
        if (element == vector->at(i)) {
            return true;
        }
    }
    return false;
}
bool contians(const string *str, char element) {
    for (auto i = 0; i < str->size(); i++)
    {
        if (element == str->at(i)) {
            return true;
        }
    }
    return false;
}

void printHero(string hero, vector<char> guesses, TextImg* img) {
   
    string output = "";

    for (auto i = 0; i < hero.size(); i++)
    {
        auto character = hero.at(i);
        char lower = tolower(character);
        

        if (lower == SPACE) {
            output.push_back(SPACE);
        }
        else if (contians(&guesses, lower)) {
            output.push_back(character);
        } else {
            output.push_back(PLACEHOLDER);
        }
    }
    img->addLine(output);
}


char getInput(const vector<char>* guesses, TextImg* img) {

    while(true) {
        char input;
        cin >> input;

        // if next char is not new line
        if (cin.peek() != '\n') {
            cout << "Bitte nur ein Buchstabe" << endl;
        }else if (contians(guesses, input)) {
            cout << "Doppelt" << endl;

        }else if (!isalpha(input)) {
            cout << "Keine Nummern du Huso" << endl;

        }else {
            char lower = tolower(input);
            return  lower;
        }     
    }
}

int getMisses(const string* hero, const vector<char>* guesses) {
    int misses = 0;
    
    for (auto i = 0; i < guesses->size(); i++)
    {
        char guess = guesses->at(i);
        if (!contians(hero, guess)) {
            misses++;
        }
    }
    return misses;
}

void printStatus(int misses, TextImg* img) {
    auto tries = to_string(LIVES - misses);
    string str = "Du hast noch ";
    str.append(tries);
    str.append(" Versuche");
    img->addLine(str);
}

bool winCondition(const string* hero, const vector<char>* guesses) {
    for (size_t i = 0; i < hero->size(); i++)
    {
        char character = hero->at(i);
        char lower = tolower(character);

        if (!contians(guesses, lower) && lower != SPACE) {
            return false;
        }
    }
    return true;
}

void awaitInput() {
    char input;
    cin >> input;
}

int main()
{    
    string hero = getRandomHero();
    vector<char> guesses = {};
    auto count = guesses.size();
    TextImg* img = new TextImg();

    printHero(hero, guesses, img);
    img->render();

    while (getMisses(&hero, &guesses) < LIVES) {

        auto input = getInput(&guesses, img);
        guesses.push_back(input);
        auto misses = getMisses(&hero, &guesses);
        img->render();
        delete img;
        img = new TextImg();

        printStatus(misses, img);
        printHero(hero, guesses, img);

        img->render();


        if (winCondition(&hero, &guesses)) {
            cout << "gz";
            auto frame = new TextImg();
            frame->addLine("gz")->addLine("lol")->addLine(to_string(misses) + " ist schon ziemlich sad");
            frame->render();
            delete frame;

            awaitInput();
            return 0;
        }

    }
    delete img;

    cout << "git gud";
    auto frame = new TextImg();
    frame->addLine("git gud")->addLine(hero);
    frame->render();
    delete frame;
    awaitInput();
    return 0;

}

