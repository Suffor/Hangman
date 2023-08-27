#pragma once

#include <vector>
#include <optional>
#include "constants.h"

const int TARGET_FPS = 60;
const double TARGET_FRAME_TIME = 1000 / TARGET_FPS;

enum class InputError:int {
	NonAlpha,
	Duplicate
};


struct GameState {
	string hero;
	vector<char> guesses = {};
	double lastInputTime;
	optional<InputError> error;
	optional<string> ending;
};


struct GameEvent {
	char key;
	GameEvent(char key) {
		this->key = key;
	}
};


class Game {

private:
	GameState* state;
	Config config;

	bool isFinished();
	std::vector<GameEvent> getInput();
	void update(double deltaTime, std::vector<GameEvent> events);
	void render(double deltaTime);

public:
	Game(Config config);
	~Game();
	void run();
};