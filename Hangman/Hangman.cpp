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

            for (auto i = 0; i < this->lines.size(); i++)               //Konflikt signed unsigned untersuchen
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
        char lower = tolower(input);
        // if next char is not new line
        if (cin.peek() != '\n') {
            cout << "Bitte nur ein Buchstabe" << endl;
        }else if (contians(guesses, lower)) {
            cout << "Doppelt" << endl;

        }else if (!isalpha(lower)) {
            cout << "Keine Nummern du Huso" << endl;

        }else {
            
            return  lower;
        }     
    }
}

string str_lower(const string* upper) {
    string lower = "";
    for (auto i = 0; i < upper->size(); i++)
    {
        char charakter = tolower(upper->at(i));
        lower.push_back(charakter);
    }
    return lower;
}

int getMisses(const string* hero, const vector<char>* guesses) {
    int misses = 0;
    
    string herolower = str_lower(hero);
    for (auto i = 0; i < guesses->size(); i++)
    {
        char guess = guesses->at(i);
        if (!contians(&herolower, guess)) {
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

void winMessage(int misses) {    
    auto frame = new TextImg();
    if (misses == 0) {
        frame->addLine("gz")->addLine("Bruder!")->addLine(to_string(misses) + " Fehler?! Macher! das nenn ich n Immortal gamer!");
        frame->render();
    }
    else if (misses == 1) {
        frame->addLine("gz")->addLine("guter gamer")->addLine(to_string(misses) + " Fehler? Du spielst save auf Ancient Level.");
        frame->render();
    }
    else if (misses == 2) {
        frame->addLine("gz")->addLine("not bad.")->addLine(to_string(misses) + " Fehler... so kommst du nie aus Archon raus...");
        frame->render();
    }
    else if (misses == 3) {
        frame->addLine("gz")->addLine("naja, ")->addLine(to_string(misses) + " Fehler. So wie du hier raetst bist du save n pos 4 undying OTP... ");
        frame->render();
    }
    else if (misses == 4) {
        frame->addLine("gz")->addLine("gerade so... ")->addLine(to_string(misses) + " Fehler. Also entweder du hast nur 2-3 mal Dota gespielt, oder du bist in bre der Wraith King doomt. Wie isses so in Guardian? ");
        frame->render();
    }
    delete frame;
}

void displayUsedLetters(const vector<char> guesses, TextImg* img) {
    img->addLine("bereits verwendete Buchstaben:");
    string letters(guesses.begin(), guesses.end());                             //(transforms char vector to string[string stringVAR(charVAR.begin(), charVAR.end())])
        img->addLine(letters);
        
}

/*bool playAgain() {
    bool replayAnswer;
    auto frame = new TextImg();
    frame->addLine("möchtest du nochmal?(true/false)");
    frame->render();
    cin >> replayAnswer;
    delete frame;
    return replayAnswer;
}*/

int main()
{   
    bool again;
    do{                                         //zu "playGame" funktion machen
        again = false;
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
            displayUsedLetters(guesses, img);

            img->render();


            if (winCondition(&hero, &guesses)) {
                cout << "gz";
                winMessage(misses);
                awaitInput();

                return 0;
            }

        }
        delete img;

        cout << "git gud noob";
        auto frame = new TextImg();
        frame->addLine("git gud Herald noob")->addLine(hero);
        frame->render();
        delete frame;
       // playAgain();
    } while (again == true);
    awaitInput();
    return 0;

}

