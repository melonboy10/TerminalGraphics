#include <sstream>
#include <string>
#include <vector>

#include "../layouts/layout.h"
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
    void removeElement(WindowElement* element, bool remove = true);
    /**
     * Removes all WindowElements from the Group
     */
    void removeAllElements();
    /**
     * Hides all WindowElements in the Group
     */
    void hideAllElements();
    /**
     * Shows all WindowElements in the Group
     */
    void showAllElements();
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
    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;

    /**
     * Selects the Group
     */
    bool select() override;
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

Group::Group(Layout* layout) : title(""), layout(layout), borderHidden(true), backgroundColor(Color::WHITE), WindowElement(1.0, 1.0) {}

Group::Group(Layout* layout, string title) : title(title), layout(layout), borderHidden(false), backgroundColor(Color::WHITE), WindowElement(1.0, 1.0) {}

Group::~Group() {
    delete this->layout;
    for (WindowElement* element : this->elements) {
        delete element;
    }
}

void Group::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (hidden) return;

    if (!this->borderHidden) {
        drawBox(x, y, width, height, title, backgroundColor);
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

void Group::hideAllElements() {
    for (WindowElement* element : this->elements) {
        element->setHidden(true);
    }
}

void Group::showAllElements() {
    for (WindowElement* element : this->elements) {
        element->setHidden(false);
    }
}

void Group::addElement(WindowElement* element, int spacer) {
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

void Group::removeElement(WindowElement* element, bool remove) {
    for (int i = 0; i < this->elements.size(); i++) {
        if (this->elements[i] == element) {
            this->elements.erase(this->elements.begin() + i);
            if (remove) delete element;
            break;
        }
    }
}

void Group::removeAllElements() {
    for (int i = 0; i < this->elements.size(); i++) {
        if (WindowElement::focusedElement == this->elements[i]) {
            WindowElement::focusedElement = nullptr;
        }
        delete this->elements[i];
    }
    this->elements.clear();
}

void Group::arrowKeyEvent(ArrowKey key, WindowElement* element) {
    if (!layout->selectNext(element, elements, key)) {
        if (parent != nullptr) {
            parent->arrowKeyEvent(key, this);
        }
    } else {
        paint(cachedX, cachedY, cachedWidth, cachedHeight);
    }
}

bool Group::select() {
    if (!WindowElement::select() && !this->hidden) {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i]->select()) {
                return true;
            }
        }
    }
    return false;
}