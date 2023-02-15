#include <string>
#include <vector>
#include "element.h"
#include "spacer.h"
#include "layouts/layout.h"

using namespace std;

class Group : public WindowElement {
   public:
    Group(Layout* layout);
    Group(Layout* layout, string title);

    void addElement(WindowElement* element, int spacer = 0);
    WindowElement* getElement(int index);
    void removeElement(WindowElement* element);
    void removeAllElements();

    void paint(int x, int y, int width, int height) override;

    void setTitle(string title);
    void setBorderHidden(bool borderHidden);
    void setLayout(Layout* layout);
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