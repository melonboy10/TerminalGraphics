#include <fstream>

#include "element.h"
#include "icon.h"

using namespace std;

Icon::Icon(string path, int width, int height) : path(path), WindowElement(width, height) {}

void Icon::setIcon(string path) {
    this->path = path;
}

void Icon::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);

    ifstream file(path);
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        drawText(line, x, y + lineNum);
        lineNum++;
    }
    printf("\033[0m");
    file.close();
}
