#include <string>

#include "element.h"
#include "text.h"

using namespace std;

Text::Text(string text) : text(text), WindowElement(1, 1) {
    height = (int)count(text.begin(), text.end(), '\n') + 1;

    int* widths = new int[height];
    int i = 0;
    int start = 0;
    int end = 0;
    while (end != string::npos) {
        end = text.find('\n', start);
        widths[i] = (int)text.substr(start, end - start).length();
        start = end + 1;
        i++;
    }

    width = *max_element(widths, widths + height);
}

Text::Text(string text, float widthPercent) : text(text), WindowElement(widthPercent, 1) {}

void Text::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    int line = 0;
    int start = 0;
    int end = 0;
    while (end != string::npos) {
        end = text.find('\n', start);
        if (widthPercent == 0) {
            drawText(text.substr(start, end - start), x + (width - text.substr(start, end - start).length()) / 2, y + line, state);
        } else {
            drawText(text.substr(start, end - start), x, y + line, state);
        }
        start = end + 1;
        line++;
    }
};
