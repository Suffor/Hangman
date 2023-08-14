#include "renderer.h"
#include <iostream>

using namespace std;


TextImg::TextImg() {

}
TextImg* TextImg::addLine(string line) {
    this->lines.push_back(line);
    return this;
}
void TextImg::render() {
    system("cls");

    for (auto i = 0; i < this->lines.size(); i++)               //Konflikt signed unsigned untersuchen
    {
        auto line = this->lines.at(i);
        cout << line << endl;
    }
}