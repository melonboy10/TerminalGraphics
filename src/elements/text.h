#include <string>
#include "element.h"

using namespace std;

class Text : public WindowElement {
   public:
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

Text::Text(string text, float widthPercent) : text(text), WindowElement(1, widthPercent) {}

void Text::paint(int x, int y, int width, int height) {
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