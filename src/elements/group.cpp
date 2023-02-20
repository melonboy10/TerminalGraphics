#include <string>
#include <vector>

#include "../layouts/layout.h"
#include "../terminal.h"
#include "element.h"
#include "spacer.h"
#include "group.h"

using namespace std;

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
