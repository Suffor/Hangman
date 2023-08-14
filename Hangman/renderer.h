#pragma once

#include <vector>
#include <string>

using namespace std;

class TextImg {
    vector<string> lines = {};

public:

    TextImg();
    TextImg* addLine(string line);
    void render();
};

