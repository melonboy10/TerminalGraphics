#include <string>

#include "element.h"

using namespace std;

/**
 * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
 * to specify a function that should be called when the Button is clicked.
 * It also has a paint method that paints the button in the console window.
 * @param title The text that is displayed on the button.
 * @param widthPercent The percentage of the parent width that the Button should take up.
 */
class Button : public WindowElement {
   public:
    /**
     * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
     * to specify a function that should be called when the Button is clicked.
     * It also has a paint method that paints the button in the console window.
     * @param title The text that is displayed on the button.
     * @param action The function that will be executed when the button is clicked.
     * @param widthPercent The percentage of the parent width that the Button should take up.
     */
    Button(
        string title, function<void()> action = []() {});

    /**
     * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
     * to specify a function that should be called when the Button is clicked.
     * It also has a paint method that paints the button in the console window.
     * @param title The text that is displayed on the button.
     * @param widthPercent The percentage of the parent width that the Button should take up.
     * @param action The function that will be executed when the button is clicked.
     */
    Button(
        string title, float widthPercent, function<void()> action = []() {});

    /**
     * Sets the title of the Button.
     * @param title The new title of the button.
     */
    void setTitle(string title);

    /**
     * Sets the action to be performed when the button is clicked.
     * @param action The function that will be executed when the button is clicked.
     */
    void setAction(function<void()> action);

    /**
     * Paints the button in the console window.
     * @param x The x-coordinate of the top left corner of the button.
     * @param y The y-coordinate of the top left corner of the button.
     * @param width The width of the button.
     * @param height The height of the button.
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Handles key events.
     * @param key The key that was pressed.
     */
    void keyEvent(int key) override;

    /**
     * Simulates a click of the button by executing its action function.
     */
    void click();

   private:
    string title;
    function<void()> action;
};

Button::Button(string title, function<void()> action) : WindowElement((int)title.length() + 2, 3), title(title), action(action) {
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
    if (hidden) return;
    drawBox(x, y, width, height, (selected ? CYAN : state));

    int titleX = x + (width / 2) - (title.length() / 2);
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