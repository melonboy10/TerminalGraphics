#include <iostream>
#include <string>
#include "../util.h"

using namespace std;

/**
* This class represents an element in a window.
* This class can be used to create any type of window element.
*/

class WindowElement {
   /**
    * Constructs a new window element with a given width and height.
    * @param width the width of the window
    * @param height the height of the window
    */
    public: WindowElement(int width, int height);

    /**
    * Constructs a new window element with a given width percentage and height.
    * @param widthPercent the width percentage of the window
    * @param height the height of the window
    */
    public: WindowElement(double widthPercent, int height);

    /**
    * Constructs a new window element with a given width and height percentage.
    * @param width the width of the window
    * @param heightPercent the height percentage of the window
    */
    public: WindowElement(int width, double heightPercent);

    /**
    * Constructs a new window element with a given width percentage and height percentage.
    * @param widthPercent the width percentage of the window
    * @param heightPercent the height percentage of the window
    */
    public: WindowElement(double widthPercent, double heightPercent);

    /**
    * Destroys the WindowElement object.
    */
    public: ~WindowElement();

    /* 
    * Paints the element at the given coordinates.
    * The width and height are the size that the element should be painted at.
    * The element will fill the entire space given.
    * @param x the x position of the element
    * @param y the y position of the element
    * @param width the width of the element
    * @param height the height of the element
    */
    public: virtual void paint(int x, int y, int width, int height) = 0;

    /**
    * Gets the fixed size of the window element
    * @param parentWidth the parent's width
    * @param parentHeight the parent's height
    * @return a tuple of width and height
    */
    public: tuple<int, int> getFixedSize(int parentWidth, int parentHeight);

    /**
    * Sets the selected status of the window element
    * @param selected the new status
    */
    public: void setSelected(bool selected);

    /**
    * Sets the state of the window element
    * @param state the new state
    */
    public: void setState(State state);

    /**
    * Sets the hidden status of the window element
    * @param hidden the new status
    */
    public: void setHidden(bool hidden);

    protected:
    /**
    * Sets the values of the cached position and size of the window element
    * @param x the x position of the window element
    * @param y the y position of the window element
    * @param width the width of the window element
    * @param height the height of the window element
    */
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