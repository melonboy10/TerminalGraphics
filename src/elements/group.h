#include <string>
#include <vector>

#include "../layouts/layout.h"
#include "../terminal.h"
#include "element.h"
#include "spacer.h"

using namespace std;

/**
 * Constructor for Group
 * @param layout A pointer to the layout of the Group
 */
class Group : public WindowElement {
   public:
    /**
     * Constructor for Group
     * @param layout A pointer to the layout of the Group
     */
    Group(Layout* layout);
    /**
     * Constructor for Group
     * @param layout A pointer to the layout of the Group
     * @param title The title of the Group
     */
    Group(Layout* layout, string title);
    /**
     * Destructor for Group
     */
    ~Group();
    /**
     * Adds a WindowElement to the Group
     * @param element A pointer to the WindowElement to add
     * @param spacer An integer representing the size of the Spacer to add after the WindowElement
     */
    void addElement(WindowElement* element, int spacer = 0);
    /**
     * Returns the WindowElement at the specified index
     * @param index The index of the WindowElement to return
     * @return The WindowElement at the specified index
     */
    WindowElement* getElement(int index);
    /**
     * Removes the specified WindowElement from the Group
     * @param element A pointer to the WindowElement to remove
     */
    void removeElement(WindowElement* element);
    /**
     * Removes all WindowElements from the Group
     */
    void removeAllElements();
    /**
     * Paints the Group to the screen
     * @param x The x coordinate to paint the Group at
     * @param y The y coordinate to paint the Group at
     * @param width The width of the Group
     * @param height The height of the Group
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Handles a key press event
     * @param key The key that was pressed
     */
    void arrowKeyEvent(ArrowKey key) override;

    /**
     * Selects the Group
     */
    void select() override;
    /**
     * Sets the title of the Group
     * @param title The title of the Group
     */
    void setTitle(string title);
    /**
     * Sets whether or not the border of the Group should be hidden
     * @param borderHidden A boolean representing whether or not the border should be hidden
     */
    void setBorderHidden(bool borderHidden);
    /**
     * Sets the layout of the Group
     * @param layout A pointer to the layout of the Group
     */
    void setLayout(Layout* layout);
    /**
     * Sets the background color of the Group
     * @param color The color to set the background to
     */
    void setBackgroundColor(Color color);

   private:
    string title;
    bool borderHidden;
    Color backgroundColor;
    vector<WindowElement*> elements;
    Layout* layout;
};

Group::Group(Layout* layout) : title(""), layout(layout), borderHidden(true), WindowElement(1.0, 1.0) {}

Group::Group(Layout* layout, string title) : title(title), layout(layout), borderHidden(false), WindowElement(1.0, 1.0) {}

Group::~Group() {
    delete this->layout;
}

void Group::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (this->hidden) return;
    if (!this->borderHidden) {
        drawBox(x, y, width, height, "X" + to_string(x) + " Y" + to_string(y) + " W" + to_string(width) + " H" + to_string(height));
        this->layout->paint(x + 1, y + 1, width - 2, height - 2, this->elements);
    } else {
        this->layout->paint(x, y, width, height, this->elements);
    }
}

void Group::setTitle(string title) {
    this->title = title;
}

void Group::setBorderHidden(bool borderHidden) {
    this->borderHidden = borderHidden;
}

void Group::setLayout(Layout* layout) {
    this->layout = layout;
}

void Group::setBackgroundColor(Color color) {
    this->backgroundColor = color;
}

void Group::addElement(WindowElement* element, int spacer) {
    if (element->parent == nullptr) {
        return;
    }
    this->elements.push_back(element);
    if (spacer) {
        this->elements.push_back(new Spacer(spacer));
    }
    element->parent = this;
    // paint(cachedX, cachedY, cachedWidth, cachedHeight);
}

WindowElement* Group::getElement(int index) {
    return this->elements[index];
}

void Group::removeElement(WindowElement* element) {
    for (int i = 0; i < this->elements.size(); i++) {
        if (this->elements[i] == element) {
            this->elements.erase(this->elements.begin() + i);
            delete element;
            break;
        }
    }
}

void Group::removeAllElements() {
    for (int i = 0; i < this->elements.size(); i++) {
        delete this->elements[i];
    }
    this->elements.clear();
}

void Group::arrowKeyEvent(ArrowKey key) {
    if (layout->selectNext(Terminal::focusedElement, elements, key)) {
        if (parent != nullptr) {
            parent->arrowKeyEvent(key);
        }
    }
}

void Group::select() {
    if (!selectable) {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i]->selectable) {
                elements[i]->select();
                break;
            }
        }
    }
}