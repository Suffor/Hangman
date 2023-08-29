#include <ctime>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "game.h"
#include "renderer.cpp"

// implmentation as "real" game loop
using namespace std;

Game::Game(Config config)
{
	this->config = config;
	this->state = new GameState();
}

Game::~Game()
{
	delete this->state;
}


vector<GameEvent> Game::getInput()
{
	if (_kbhit()) {
		char input = _getch();
		return vector<GameEvent>{GameEvent(input)};
	}
	return vector<GameEvent>();
}

void Game::update(double deltaTime, vector<GameEvent> events)
{
	
}

void Game::render(double deltaTime)
{
	string out = "frame took: ";
	out.append(to_string(deltaTime));
	out.append("ms");
	cout << out;
	if (this->state->ending.has_value()) {

	} else {

	}
}

bool Game::isFinished()
{
	return false;
}

void Game::run() {

	auto t_last = std::chrono::high_resolution_clock::now();
	
	while (!this->isFinished())
	{
		// calculate passed time
		auto t_current = std::chrono::high_resolution_clock::now();
		double delta = std::chrono::duration<double, std::milli>(t_current - t_last).count();
		t_last = t_current;

		// calculate frame
		auto events = this->getInput();
		this->update(delta, events);
		this->render(delta);

		// wait until next frame
		auto t_fin = std::chrono::high_resolution_clock::now();
		double duration = std::chrono::duration<double, std::milli>(t_current - t_fin).count();


		int wait = TARGET_FRAME_TIME - duration;
		//cout << to_string(duration) << " wait: " << to_string(wait) << "\n";
		

		if (wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(wait));
		}
	}
}