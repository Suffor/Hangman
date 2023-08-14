#include <iostream>
#include <vector>
#include <cctype>
#include "constants.h"
#include <time.h>       
#include <tuple>

using namespace std;

struct MenuStruct { int menuWahl; int schwierigkeit; };


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

void printStatus(int misses, TextImg* img, int lives) {
    auto tries = to_string(lives - misses);
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

bool playAgain(TextImg* frame) {
    bool replayAnswer = false;
    frame->addLine("moechtest du nochmal?(true/false)");
    frame->render();
    cin >> boolalpha >> replayAnswer;                       //boolapha wandelt bool in textform "true/false"
    if (replayAnswer) {
        return replayAnswer;
    }
    else {
        frame->addLine("ungültige Eingabe, Spiel wird beendet");
        return false;
    }
}

bool winMessage(int misses) {
    bool again = false;
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
    again = playAgain(frame);
    delete frame;
    return again;
}

void displayUsedLetters(const vector<char> guesses, TextImg* img) {
    img->addLine("bereits verwendete Buchstaben:");
    string letters(guesses.begin(), guesses.end());                             //(transforms char vector to string[string stringVAR(charVAR.begin(), charVAR.end())])
        img->addLine(letters);
        
}

int difficulty(int schwierigkeit) {
    int lives;
    if (schwierigkeit == 0) {
        lives = LIVESEZ;
    }
    else if (schwierigkeit == 1) {
        lives = LIVES;
    }
    else if (schwierigkeit == 2) {
        lives = LIVESHARD;
    }
    return lives;
}

MenuStruct mainMenu() {
    MenuStruct spielerwahl;
    int menuIn = 0;
    vector <string> schwierigk = { "leicht", "normal", "schwer" };
    int schwierigkcount=1;


    while (menuIn == 0 || menuIn== 2) {
        TextImg* menu = new TextImg();
        menu->addLine("Willkommen zu Dota2-Hangman!");
        menu->addLine("1-Starte das verdammte Spiel!");
        menu->addLine("2-Schwierigkeitsgrad: " + schwierigk[schwierigkcount%3]);
        menu->addLine("3-Optionen(inaktiv)");
        menu->addLine("4-Beenden");
        menu->render();
        cin >> menuIn;
        if (menuIn == 2) {
            schwierigkcount++;
        }
        delete menu;
    }
    spielerwahl.menuWahl = menuIn;
    spielerwahl.schwierigkeit = schwierigkcount % 3;
    return spielerwahl;
}

bool playGame(int schwierigkeit)
{
    bool again = false;
    string hero = getRandomHero();
    vector<char> guesses = {};
    auto count = guesses.size();
    TextImg* img = new TextImg();

    printHero(hero, guesses, img);
    img->render();
    
    int lives = difficulty(schwierigkeit);

    while (getMisses(&hero, &guesses) < lives) {

        auto input = getInput(&guesses, img);
        guesses.push_back(input);
        auto misses = getMisses(&hero, &guesses);
        img->render();
        delete img;
        img = new TextImg();

        printStatus(misses, img, lives);
        printHero(hero, guesses, img);
        displayUsedLetters(guesses, img);

        img->render();


        if (winCondition(&hero, &guesses)) {
            cout << "gz";
            again = winMessage(misses);
            //awaitInput();
            
            return again;
        }

    }
    delete img;

    cout << "git gud noob";
    auto frame = new TextImg();
    frame->addLine("git gud Herald noob")->addLine(hero);
    frame->render();
    again = playAgain(frame);
    delete frame;
    return again;
}

int main()
{   
    bool again = false;
    bool exit = false;
    MenuStruct spielerWahl;
    
    do {
        spielerWahl = mainMenu();
        if (spielerWahl.menuWahl == 1) {
            do {
                again = playGame(spielerWahl.schwierigkeit);
            } while (again == true);
        }
        else if (spielerWahl.menuWahl == 4) {
            exit = true;
            return 0;
        }
    } while (!exit);
    return 0;
}

