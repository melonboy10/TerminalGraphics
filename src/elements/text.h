#include <algorithm>
#include <string>

#include "element.h"

using namespace std;

/**
 * Creates a new Text object.
 * @param text the string to be displayed
 * @param widthPercent the percentage of the width of the window that the Text should take up.
 */
class Text : public WindowElement {
   public:
    /**
     * Creates a new Text object.
     * @param text the string to be displayed
     */
    Text(string text);

    /**
     * Creates a new Text object.
     * @param text the string to be displayed
     * @param widthPercent the percentage of the width of the window that the Text should take up.
     */
    Text(string text, float widthPercent);

    /**
     * Sets the text of the Text object.
     * @param text the string to be displayed
     */
    void setText(string text);

    /**
     * Displays the text on the window.
     * @param x the x coordinate of the text's position
     * @param y the y coordinate of the text's position
     * @param width the width of the text
     * @param height the height of the text
     */
    void paint(int x, int y, int width, int height);

   private:
    string text = "";
};

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
    delete[] widths;
}

Text::Text(string text, float widthPercent) : text(text), WindowElement(widthPercent, 1) {
    height = (int)count(text.begin(), text.end(), '\n') + 1;
}

void Text::setText(string text) {
    this->text = text;
}

void Text::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (hidden) return;
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