#include "../util.h"

using namespace std;

/**
 * Constructs a new window element with a given width and height.
 * @param width the width of the window
 * @param height the height of the window
 */
class WindowElement {
   public:
    /**
     * Constructs a new window element with a given width and height.
     * @param width the width of the window
     * @param height the height of the window
     */
    WindowElement(int width, int height);

    /**
     * Constructs a new window element with a given width percentage and height.
     * @param widthPercent the width percentage of the window
     * @param height the height of the window
     */
    WindowElement(double widthPercent, int height);

    /**
     * Constructs a new window element with a given width and height percentage.
     * @param width the width of the window
     * @param heightPercent the height percentage of the window
     */
    WindowElement(int width, double heightPercent);

    /**
     * Constructs a new window element with a given width percentage and height percentage.
     * @param widthPercent the width percentage of the window
     * @param heightPercent the height percentage of the window
     */
    WindowElement(double widthPercent, double heightPercent);

    /**
     * Destroys the WindowElement object.
     */
    virtual ~WindowElement();

    /*
     * Paints the element at the given coordinates.
     * The width and height are the size that the element should be painted at.
     * The element will fill the entire space given.
     * @param x the x position of the element
     * @param y the y position of the element
     * @param width the width of the element
     * @param height the height of the element
     */
    virtual void paint(int x, int y, int width, int height);

    /**
     * Gets the fixed size of the window element
     * @param parentWidth the parent's width
     * @param parentHeight the parent's height
     * @return a tuple of width and height
     */
    tuple<int, int> getFixedSize(int parentWidth, int parentHeight);

    /**
     * Gets if the element is selectable
     * @return true if the element is selectable, false otherwise
     */
    bool isSelectable();

    /**
     * Sets the selected status of the window element
     * @param selected the new status
     */
    void setSelected(bool selected);

    /**
     * Selects the window element
     */
    virtual bool select();

    /**
     * Sends a key event to the window element
     * @param key the key code
     */
    virtual void keyEvent(int key);

    /**
     * Sends an arrow key event to the window element
     * @param key the arrow key
     */
    virtual void arrowKeyEvent(ArrowKey key, WindowElement* element);

    /**
     * Sets the state of the window element
     * @param state the new state
     */
    void setState(State state);

    /**
     * Sets the hidden status of the window element
     * @param hidden the new status
     */
    void setHidden(bool hidden);

    /**
     * Sets the values of the cached position and size of the window element
     * @param x the x position of the window element
     * @param y the y position of the window element
     * @param width the width of the window element
     * @param height the height of the window element
     */
    void setValues(int x, int y, int width, int height);

    static WindowElement* focusedElement;

    double widthPercent = -1, heightPercent = -1;
    int width = -1, height = -1;
    bool selected, selectable;
    bool hidden = false;
    int cachedX = 0, cachedY = 0, cachedWidth = 0, cachedHeight = 0;
    State state = DEFAULT;
    WindowElement* parent;
};

WindowElement* WindowElement::focusedElement;

WindowElement::WindowElement(int width, int height) : width(width), height(height) {}

WindowElement::WindowElement(double widthPercent, int height) : widthPercent(widthPercent), height(height) {}

WindowElement::WindowElement(int width, double heightPercent) : width(width), heightPercent(heightPercent) {}

WindowElement::WindowElement(double widthPercent, double heightPercent) : widthPercent(widthPercent), heightPercent(heightPercent) {}

WindowElement::~WindowElement() {}

void WindowElement::setSelected(bool selected) {
    if (WindowElement::focusedElement != nullptr && WindowElement::focusedElement != this) {
        WindowElement::focusedElement->setSelected(false);
    }
    WindowElement::focusedElement = this;
    this->selected = selected;
    // paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
}

bool WindowElement::select() {
    if (this->selectable) {
        setSelected(true);
        paint(this->cachedX, this->cachedY, this->cachedWidth, this->cachedHeight);
        drawText("void Group::arrowKeyEvent(ArrowKey key, WindowElement* element) {", 0, 0, RED);
        return true;
    }
    return false;
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

void WindowElement::arrowKeyEvent(ArrowKey key, WindowElement* element) {
    if (this->parent != nullptr) {
        this->parent->arrowKeyEvent(key, element);
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