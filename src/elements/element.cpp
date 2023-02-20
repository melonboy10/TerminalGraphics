#include "../terminal.h"
#include "../util.h"
#include "element.h"

using namespace std;

WindowElement::WindowElement(int width, int height) : width(width), height(height) {}

WindowElement::WindowElement(double widthPercent, int height) : widthPercent(widthPercent), height(height) {}

WindowElement::WindowElement(int width, double heightPercent) : width(width), heightPercent(heightPercent) {}

WindowElement::WindowElement(double widthPercent, double heightPercent) : widthPercent(widthPercent), heightPercent(heightPercent) {}

WindowElement::~WindowElement() {}

void WindowElement::setSelected(bool selected) {
    Terminal::focusedElement->setSelected(false);
    Terminal::focusedElement = this;
    this->selected = selected;
    paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
}

void WindowElement::select() {
    if (this->selectable) {
        this->selected = true;
        paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
    }
}

bool WindowElement::isSelectable() {
    return this->selectable;
}

void WindowElement::setState(State state) {
    this->state = state;
    paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
}

void WindowElement::setHidden(bool hidden) {
    this->hidden = hidden;
}

void WindowElement::paint(int x, int y, int width, int height) {
    clearArea(cachedX, cachedY, cachedWidth, cachedHeight);
    clearArea(x, y, width, height);
    setValues(x, y, width, height);
}

void WindowElement::keyEvent(int key) {}

void WindowElement::arrowKeyEvent(ArrowKey key) {
    if (this->parent != nullptr) {
        this->parent->arrowKeyEvent(key);
    }
}

tuple<int, int> WindowElement::getFixedSize(int parentWidth, int parentHeight) {
    int width = this->width;
    int height = this->height;
    if (this->widthPercent != -1) {
        width = this->widthPercent * parentWidth;
    }
    if (this->heightPercent != -1) {
        height = this->heightPercent * parentHeight;
    }
    return make_tuple(width, height);
}

void WindowElement::setValues(int x, int y, int width, int height) {
    this->cachedX = x;
    this->cachedY = y;
    this->cachedWidth = width;
    this->cachedHeight = height;
}
