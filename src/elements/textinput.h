#include <string>

#include "element.h"

using namespace std;

class TextInput : public WindowElement {
   public:
    TextInput(string title, string templateText, float widthPercent = 0.6);

    void setTitle(string title);
    void setText(string text);

    void paint(int x, int y, int width, int height) override;

    string getInput();

   private:
    string title;
    string text = "";
    string templateText;
};

TextInput::TextInput(string title, string templateText, float widthPercent): title(title), templateText(templateText), WindowElement(widthPercent, 3) {}

void TextInput::setTitle(string title) {
    this->title = title;
}
void TextInput::setText(string text) {
    this->text = text;
}
void TextInput::paint(int x, int y, int width, int height) {
    for (int i = 0; i < width; i++) {
        drawText("─", x + i, y, state);
        drawText(" ", x + i, y + 1, state);
        drawText("─", x + i, y + 2, state);
    }
    if (selected) {
        drawText(title, x + 2, y, CYAN);
    } else {
        drawText(title, x + 2, y, state);
    }
    drawText("╭┤", x, y, state);
    drawText("├", x + 2 + title.length(), y, state);
    if (text.length() > 0) {
        drawText(text, x + 2, y + 1, state);
    } else {
        drawText(templateText, x + 2, y + 1, DIM);
    }
    drawText("╮", x + width, y, state);
    drawText("│ ", x, y + 1, state);
    drawText("│", x + width, y + 1, state);
    drawText("╰", x, y + 2, state);
    drawText("╯", x + width, y + 2, state);
    cout << flush;
}
string TextInput::getInput() {
    setSelected(true);

    showCursor();
    string output;
    setCursorPosition(cachedX + 2, cachedY + 1);
    getline(cin, output);

    setText(output);
    hideCursor();
    setSelected(false);

    return output;
}