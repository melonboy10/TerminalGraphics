#include <string>
#include <vector>
#include "element.h"
#include "spacer.h"
#include "layouts/layout.h"

using namespace std;

/**
 * Class representing a group of WindowElements
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
    vector<WindowElement*> elements = vector<WindowElement*>();
    Layout* layout;
};


Group::Group(Layout* layout): WindowElement(1.0, 1.0) {
    this->title = "";
    this->layout = layout;
    this->borderHidden = true;
}

Group::Group(Layout* layout, string title): WindowElement(1.0, 1.0) {
    this->title = title;
    this->layout = layout;
    this->borderHidden = false;
}

void Group::paint(int x, int y, int width, int height) {
    if (this->hidden) return;
    if (!this->borderHidden) drawBox(x, y, width, height, title);

    this->layout->paint(x, y, width, height, this->elements);
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

void Group::addElement(WindowElement* element, int spacer = 0) {
    this->elements.push_back(element);
    if (spacer) {
        this->elements.push_back(new Spacer(spacer));
    }
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