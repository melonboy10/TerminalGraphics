#include "button.h"

#include <string>

#include "element.h"

using namespace std;

Button::Button(string title, function<void()> action) : WindowElement((int)title.length() + 1, 3), title(title), action(action) {
    this->selectable = true;
}

Button::Button(string title, float widthPercent, function<void()> action) : WindowElement(widthPercent, 3), title(title), action(action) {
    this->selectable = true;
}

void Button::setTitle(string title) {
    this->title = title;
}

void Button::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    drawBox(x, y, width, height, (selected ? CYAN : state));

    int titleX = x + (width / 2) - (title.length() / 2) + 1;
    drawText(title, titleX, y + 1, (selected ? CYAN : state));
}

void Button::keyEvent(int key) {
    if (key == Key::ENTER) {
        click();
    }
}

void Button::click() {
    action();
}
