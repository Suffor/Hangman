#include <ctime>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "game.h"

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

void testLine(AsciiRenderer* renderer, RGBColor color) {
	renderer->newLine();
	for (size_t i = 0; i < 20; i++)
	{
		float factor = i / 19.0f;
		renderer->push(RGBColor((int)(color.r * factor), (int)(color.g * factor), (int)(color.b * factor)));
	}
}

void Game::render(double deltaTime)
{
	this->renderer.clear();
	string out = "frame took: ";
	out.append(to_string(deltaTime));
	out.append("ms");
	testLine(&this->renderer, RGBColor(255, 255, 255));
	this->renderer.pushLn(out, RGBColor(200, 200, 200));
	testLine(&this->renderer, RGBColor(255, 0, 0));

	if (this->state->ending.has_value()) {

	} else {

	}

	this->renderer.render();
}

bool Game::isFinished()
{
	return false;
}

void Game::run() {

	auto t_last = std::chrono::high_resolution_clock::now();
	system("cls");
	
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

		if (wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(wait));
		}
	}
}