#pragma once

enum Difficulty { easy  = 0, normal = 1, hard = 2 };
enum MenuOption { start = 1, difficulty = 2, options = 3, close = 4};


struct Config {
    Difficulty difficulty = Difficulty::normal;
};

struct MenuState {
    Config config;
    MenuOption selected;
public:
    MenuState(Difficulty difficulty, MenuOption selected) {
        this->config.difficulty = difficulty;
        this->selected = selected;
    }

};
