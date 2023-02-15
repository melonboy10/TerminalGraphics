#include <string>
#include "element.h"

using namespace std;

class Text : public WindowElement {
   public:
    Text(string text, float widthPercent = 0.5);
    void setText(string text);

    void paint(int x, int y, int width, int height) override;

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