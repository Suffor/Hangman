#include <vector>

#include <time.h>       
#include <tuple>
#include <memory>
#include <iostream>
#include <conio.h>
#include <optional>
#include <cctype>

#include "constants.h"
#include "renderer.h"


using namespace std;


char toLower(char input) {
	if (input > 64 && input < 91) {
		input=input + 32;
		return input;
	}
	return input;
}

string getRandomHero() {
	auto count = size(HEROS);
	srand(time(NULL));
	auto random = rand() % count;

	return HEROS[random];
}


template<typename Type>
bool contains(const vector<Type>* vector, Type element) {
	for (size_t i = 0; i < vector->size(); i++)
	{
		if (element == vector->at(i)) {
			return true;
		}
	}
	return false;
}
bool contians(const string* str, char element) {
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
		else if (contains(&guesses, lower)) {
			output.push_back(character);
		}
		else {
			output.push_back(PLACEHOLDER);
		}
	}
	img->addLine(output);
}

optional<char> checkInput(const vector<char>* guesses, TextImg* img) {
	char input=_getch();
	//cin >> input;
	char lower = tolower(input);

	// if next char is not new line
	if (contains(guesses, lower)) {
		cout << "Doppelt" << endl;

	}
	else if (!isalpha(lower)) {
		cout << "Keine Nummern du Huso" << endl;

	}
	else {

		return  lower;
	}
	return {};
}

char getInput(const vector<char>* guesses, TextImg* img) {

	while (true) {
		auto input = checkInput(guesses, img);
		if (input) {
			return input.value();
		}
	}
}

optional<char> timedInput(int last_t, TextImg* img, const vector<char> guesses, int time) {
	clock_t t = clock();
	while ((clock() - t) / CLOCKS_PER_SEC <time ) {
		while (!_kbhit()) {
			if ((clock() - t) / CLOCKS_PER_SEC >= time) {
				return {};
			}
			int current_t = (clock() - t) / CLOCKS_PER_SEC;
			if (current_t != last_t) {
				cout << (time - (clock() - t) / CLOCKS_PER_SEC)<<endl;
				last_t = (clock() - t) / CLOCKS_PER_SEC;
			}
		}
		
		auto input = checkInput(&guesses, img);
		if (input) {
			return input;
		}
	}
	return {};
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

		if (!contains(guesses, lower) && lower != SPACE) {
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

int getLives(Config config) {
	return LIVES[config.difficulty];
}

bool winMessage(double misses, Config config) {
	double lives = getLives(config);
	bool again = false;
	auto frame = new TextImg();
	double ratio = (lives - misses) / lives;
	if (ratio == 1) {
		frame->addLine("gz")->addLine("Bruder!")->addLine(to_string(misses) + " Fehler?! Macher! das nenn ich n Immortal gamer! Ich ruf kurz Secret an die brauchen glaub ich n neues Teamcaptain");
		frame->render();
	}
	else if (ratio > 0.85) {
		frame->addLine("gz")->addLine("Macher!")->addLine(to_string(misses) + " Fehler nur? Das is schon sehr krass. Könntest auf Divine spielen");
		frame->render();
	}
	else if (ratio > 0.7) {
		frame->addLine("gz")->addLine("TIER.")->addLine(to_string(misses) + " Fehler. Du spielst zwar auf Ancient, aber siehst hier auf jeden Fall nicht alt aus. huehuehue...");
		frame->render();
	}
	else if (ratio > 0.55) {
		frame->addLine("gz")->addLine("not bad, ")->addLine(to_string(misses) + " Fehler. Bist schon auf Legende gelandet, aber du kannst die Ränge doch sicher weiter klettern oder? ;) ");
		frame->render();
	}
	else if (ratio > 0.4) {
		frame->addLine("gz")->addLine("ei jo, ")->addLine(to_string(misses) + " Fehler. Lass mich raten. Du steckst in Archon fest, aber es liegt immer daran, dass deine Lane nicht genügend ganks bekommt?... ");
		frame->render();
	}
	else if (ratio > 0.25) {
		frame->addLine("gz")->addLine("naja, ")->addLine(to_string(misses) + " Fehler. Lass mich raten... du bist ein Pos 4 Undying OTP weil dir alles andere zu schwer ist?... ");
		frame->render();
	}
	else if (ratio < 0.25) {
		frame->addLine("gz")->addLine("schwach ")->addLine(to_string(misses) + " Fehler. Also entweder du hast nur 2-3 mal Dota gespielt, oder du bist in bre der Wraith King doomt. Wie isses so in Herald? ");
		frame->render();
	}
	
	again = playAgain(frame);
	delete frame;
	return again;
}

void displayUsedLetters(const vector<char> guesses, TextImg* img) {
	img->addLine("bereits verwendete Buchstaben:");
	string letters="";
	for (auto i = 0; i < guesses.size(); i++)
	{
		letters.push_back(guesses[i]);
	}
	img->addLine(letters);

}

int Options() {
	int time = 0;
	
while (true) {
		auto option = new TextImg();
		option->addLine("1-Timer Einstellen (0=kein Timer): " + to_string(time));
		option->addLine("2-Farbenblindenmodus (inaktiv)");
		option->addLine("3-zuruek zu Hauptmenu");
		option->render();
		int OptionsIn;
		cin >> OptionsIn;
		if (OptionsIn == 1) {
			cin >> time;

			continue;
		}
		else if (OptionsIn == 2) {
			option->addLine("noch nicht implementiert");
			continue;
		}
		else if (OptionsIn == 3) {
			delete option;
			return time;
		}
		
	}
}

MenuState mainMenu() {

	int difficulty = 1;
	int time = 0;

	while (true) {

		auto menu = new TextImg();

		menu->addLine("Willkommen zu Dota2-Hangman!");
		menu->addLine("1-Starte das verdammte Spiel!");
		menu->addLine("2-Schwierigkeitsgrad: " + DIFFICLUTY_NAMES[static_cast<Difficulty>(difficulty)]);
		menu->addLine("3-Optionen");
		menu->addLine("4-Beenden");
		menu->render();
		int menuIn;
		cin >> menuIn;
		if (menuIn == 2) {
			difficulty++;
			difficulty = difficulty % 3;
			continue;
		}
		if (menuIn == 3) {
			delete menu;
			time = Options();
			continue;
		}
		return MenuState(static_cast<Difficulty>(difficulty), static_cast<MenuOption>(menuIn),time);
	}
}

bool playGame(Config config)
{
	bool again = false;
	string hero = getRandomHero();
	vector<char> guesses = {};
	auto count = guesses.size();
	TextImg* img = new TextImg();
	int last_t = 0;

	printHero(hero, guesses, img);
	img->render();

	int lives = getLives(config);

	while (getMisses(&hero, &guesses) < lives) {
		char input;

		if (config.time != 0) {
			auto timedinput = timedInput(last_t, img, guesses,config.time);
			if (!timedinput) {
				lives = 0;
			}
			else {
				input = *move(timedinput);												//wandelt optional<char> zu char
			}
		}
		else {
			input = getInput(&guesses, img);
		}
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
			again = winMessage(misses, config);
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

	do {
		MenuState choice = mainMenu();
		if (choice.selected == 1) {
			do {
				again = playGame(choice.config);
			} while (again == true);
		}
		else if (choice.selected == 4) {
			exit = true;
			return 0;
		}
	} while (!exit);
	return 0;
}

