#include <functional>
#include <string>

#include "element.h"

using namespace std;

/**
 * Constructor for TextField object
 * @param title the title of the text input
 * @param templateText the template text to be shown if input is empty
 * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
 */
class TextField : public WindowElement {
   public:
    /**
     * Constructor for TextField object
     * @param title the title of the text input
     * @param templateText the template text to be shown if input is empty
     * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
     */
    TextField(string title, string templateText, float widthPercent = 0.9);

    /**
     * Sets the title of the text input
     * @param title the new title to be set
     */
    void setTitle(string title);

    /**
     * Sets the text input's current text
     * @param text the new text to be set
     */
    void setText(vector<string> text);

    /**
     * Gets the text input's current text
     * @return the text input's current text
     */
    vector<string> getText();

    /**
     * Sets whether or not the text input should show line numbers
     * @param lineNumbers whether or not the text input should show line numbers
     */
    void setLineNumbers(bool lineNumbers);

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

    void setHeader(vector<string> header);

    void setFooter(vector<string> footer);

   private:
    string title;
    vector<string> text = vector<string>(1, "");
    vector<string> header = vector<string>();
    vector<string> footer = vector<string>();
    pair<int, int> selectedText = pair<int, int>(0, 0);
    string templateText;
    bool lineNumbers = false;
};

TextField::TextField(string title, string templateText, float widthPercent) : title(title), templateText(templateText), WindowElement(widthPercent, 0.9) {
    this->selectable = true;
}

void TextField::setTitle(string title) {
    this->title = title;
}
void TextField::setText(vector<string> text) {
    this->text = text;
}
vector<string> TextField::getText() {
    return text;
}
void TextField::setLineNumbers(bool lineNumbers) {
    this->lineNumbers = lineNumbers;
}

void TextField::setHeader(vector<string> header) {
    this->header = header;
}

void TextField::setFooter(vector<string> footer) {
    this->footer = footer;
}

void TextField::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (hidden) return;

    int numberOffset = lineNumbers ? 4 : 0;

    drawBox(x, y, width, height, title, state);
    drawText("┤Press Tab to exit├", x + 2, y, state);

    if (selected) {
        drawText(title, x + 2, y, CYAN);
    } else {
        drawText(title, x + 2, y, state);
    }
    if (text.size() > 0) {
        for (int i = 0; i < header.size(); i++) {
            drawText(header[i], x + 1, y + 1 + i, DIM);
        }
        for (int i = 0; i < text.size(); i++) {
            if (lineNumbers) {
                string number = to_string(i + 1);
                number.resize(numberOffset - 2, ' ');
                drawText(number + "|", x + 1, y + 1 + i + header.size(), GRAY);
            }
            drawText(text[i], x + numberOffset, y + 1 + i + header.size(), WHITE);

            setCursorPosition(x + numberOffset + selectedText.second, y + 1 + selectedText.first + header.size());
            printf("▒");
        }
        for (int i = 0; i < footer.size(); i++) {
            drawText(footer[i], x + 1, y + 1 + i + text.size() + header.size(), DIM);
        }
    } else {
        drawText((selected ? "_" : "") + templateText, x + numberOffset, y + 1, DIM);
    }
}

void TextField::keyEvent(int key) {
    // Multiline text editing
    // Handles, backspace, enter, and normal text
    if (key == ENTER) {
        // Add new line below
        text.insert(text.begin() + selectedText.first + 1, "");
        selectedText.first++;
        selectedText.second = 0;
    } else if (key == BACKSPACE) {
        // Remove character to the left if none combine current line with line above
        if (selectedText.second > 0) {
            text[selectedText.first].erase(selectedText.second - 1, 1);
            selectedText.second--;
        } else if (selectedText.first > 0) {
            text[selectedText.first - 1] += text[selectedText.first];
            text.erase(text.begin() + selectedText.first);
            selectedText.first--;
            selectedText.second = text[selectedText.first].length();
        }
    } else if (key == TAB) {
        WindowElement::arrowKeyEvent(RIGHT, this);
    } else {
        text[selectedText.first].insert(selectedText.second, 1, key);
        selectedText.second++;
    }
}

void TextField::arrowKeyEvent(ArrowKey key, WindowElement* element) {
    // Multiline text editing
    // Handles arrow keys
    if (key == UP) {
        if (selectedText.first > 0) {
            selectedText.first--;
            if (selectedText.second > text[selectedText.first].length()) {
                selectedText.second = text[selectedText.first].length();
            }
        }
    } else if (key == DOWN) {
        if (selectedText.first < text.size() - 1) {
            selectedText.first++;
            if (selectedText.second > text[selectedText.first].length()) {
                selectedText.second = text[selectedText.first].length();
            }
        }
    } else if (key == LEFT) {
        if (selectedText.second > 0) {
            selectedText.second--;
        } else if (selectedText.first > 0) {
            selectedText.first--;
            selectedText.second = text[selectedText.first].length();
        }
    } else if (key == RIGHT) {
        if (selectedText.second < text[selectedText.first].length()) {
            selectedText.second++;
        } else if (selectedText.first < text.size() - 1) {
            selectedText.first++;
            selectedText.second = 0;
        }
    }
}