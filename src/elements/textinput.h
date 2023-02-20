#include <string>

#include "element.h"

using namespace std;

/**
 * Constructor for TextInput object
 * @param title the title of the text input
 * @param templateText the template text to be shown if input is empty
 * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
 */
class TextInput : public WindowElement {
   public:
    /**
     * Constructor for TextInput object
     * @param title the title of the text input
     * @param templateText the template text to be shown if input is empty
     * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
     */
    TextInput(string title, string templateText, float widthPercent = 0.6);

    /**
     * Sets the title of the text input
     * @param title the new title to be set
     */
    void setTitle(string title);

    /**
     * Sets the text input's current text
     * @param text the new text to be set
     */
    void setText(string text);

    /**
     * Paints the text input on the screen
     * @param x the x position of the text input on the screen
     * @param y the y position of the text input on the screen
     * @param width the width of the text input on the screen
     * @param height the height of the text input on the screen
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * When key is pressed, adds the key to the text input's text
     * @param key the key that was pressed
     */
    void keyEvent(int key) override;

    /**
     * When arrow key is pressed, moves the cursor in the text input's text
     * @param key the key that was pressed
     * @return true if the key was handled, false otherwise
     */
    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;

    /**
     * Sets the exit action of the text input
     * @param exitAction the exit action to be set
     */
    void setExitAction(function<void(string)> exitAction);

   private:
    string title;
    string text = "";
    string templateText;
    function<void(string)> exitAction;
    function<void(string)> keyAction;
};

TextInput::TextInput(string title, string templateText, float widthPercent) : title(title), templateText(templateText), WindowElement(widthPercent, 3) {
    this->selectable = true;
}

void TextInput::setTitle(string title) {
    this->title = title;
}
void TextInput::setText(string text) {
    this->text = text;
}
void TextInput::setExitAction(function<void(string)> exitAction) {
    this->exitAction = exitAction;
}

void TextInput::setKeyAction(function<void(string)> keyAction) {
    this->keyAction = keyAction;
}

void TextInput::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
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
        drawText(text + (selected ? "▄" : ""), x + 2, y + 1, state);
    } else {
        drawText((selected ? "▄" : "") + templateText, x + 2, y + 1, DIM);
    }

    drawText("╮", x + width, y, state);
    drawText("│ ", x, y + 1, state);
    drawText("│", x + width, y + 1, state);
    drawText("╰", x, y + 2, state);
    drawText("╯", x + width, y + 2, state);
}

void TextInput::keyEvent(int key) {
    if (key == Key::BACKSPACE) {
        if (text.length() > 0) {
            text = text.substr(0, text.length() - 1);
        }
    } else if (key == Key::ENTER) {
        if (exitAction != nullptr) {
            exitAction(text);
        }
    } else {
        text += (char)key;
        if (keyAction != nullptr) {
            keyAction(text);
        }
    }
    paint(cachedX, cachedY, cachedWidth, cachedHeight);
}

void TextInput::arrowKeyEvent(ArrowKey key, WindowElement* element) {
    if (exitAction != nullptr) {
        exitAction(text);
    }
    WindowElement::arrowKeyEvent(key, element);
}