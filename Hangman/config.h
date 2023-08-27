#pragma once

enum Difficulty { easy  = 0, normal = 1, hard = 2 };
enum MenuOption { start = 1, difficulty = 2, options = 3, close = 4};


struct Config {
    Difficulty difficulty = Difficulty::normal;
    int time = 0;
};

struct MenuState {
    Config config;
    MenuOption selected;
    Config time;
public:
    MenuState(Difficulty difficulty, MenuOption selected, int time) {
        this->config.difficulty = difficulty;
        this->selected = selected;
        this->config.time = time;
    }

};
