#include <string>

#include "element.h"

using namespace std;

class Button : public WindowElement {
   public:
    Button(string title, float widthPercent = 0.3);
    void setTitle(string title);
    void setAction(function<void()> action);

    void paint(int x, int y, int width, int height) override;

    void click();

   private:
    string title;
    function<void()> action;
};

Button::Button(string title, float widthPercent): title(title), WindowElement(widthPercent, 3) {}

void Button::setTitle(string title) {
    this->title = title;
}

void Button::paint(int x, int y, int width, int height) {
    for (int i = 0; i < width; i++) {
        drawText("─", x + i, y, (selected ? CYAN : state));
        drawText(" ", x + i, y + 1);
        drawText("─", x + i, y + 2, (selected ? CYAN : state));
    }
    drawText("╭", x, y, (selected ? CYAN : state));
    drawText("╮", x + width, y, (selected ? CYAN : state));
    drawText("│", x, y + 1, (selected ? CYAN : state));
    drawText("│", x + width, y + 1, (selected ? CYAN : state));
    drawText("╰", x, y + 2, (selected ? CYAN : state));
    drawText("╯", x + width, y + 2, (selected ? CYAN : state));

    int titleX = x + (width / 2) - (title.length() / 2);
    drawText(title, titleX, y + 1, (selected ? CYAN : state));
}

void Button::click() {
    action();
}