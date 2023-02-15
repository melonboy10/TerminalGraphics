#include <iostream>
#include <string>
#include "../util.h"

using namespace std;

class WindowElement {
   public:
    WindowElement(int width, int height);
    WindowElement(double widthPercent, int height);
    WindowElement(int width, double heightPercent);
    WindowElement(double widthPercent, double heightPercent);
    ~WindowElement();

    /* 
    * Paints the element at the given coordinates.
    * The width and height are the size that the element should be painted at.
    * The element will fill the entire space given.
    */
    virtual void paint(int x, int y, int width, int height) = 0;
    tuple<int, int> getFixedSize(int parentWidth, int parentHeight);

    void setSelected(bool selected);
    void setState(State state);
    void setHidden(bool hidden);

   protected:
    void setValues(int x, int y, int width, int height);

    double widthPercent = -1, heightPercent = -1;
    int width = -1, height = -1;
    bool selected;
    bool hidden = false;
    int cachedX = 0, cachedY = 0, cachedWidth = 0, cachedHeight = 0;
    State state = DEFAULT;
};

WindowElement::WindowElement(int width, int height): width(width), height(height) {}

WindowElement::WindowElement(double widthPercent, int height): widthPercent(widthPercent), height(height) {}

WindowElement::WindowElement(int width, double heightPercent): width(width), heightPercent(heightPercent) {}

WindowElement::WindowElement(double widthPercent, double heightPercent): widthPercent(widthPercent), heightPercent(heightPercent) {}

WindowElement::~WindowElement() {}

void WindowElement::setSelected(bool selected) {
    this->selected = selected;
    paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
}

void WindowElement::setState(State state) {
    this->state = state;
    paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
}

void WindowElement::setHidden(bool hidden) {
    this->hidden = hidden;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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