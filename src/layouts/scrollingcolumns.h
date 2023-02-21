#include <cmath>

#include "layout.h"

using namespace std;

/**
 * @param widths an array of integers representing the width of each element in the grid
 */
class ScrollingColumnsLayout : public Layout {
   public:
    /**
     * @param numColumns the number of columns in the grid
     */
    ScrollingColumnsLayout(int numColumns);
    /**
     * A grid where the width of each element is the same as the height
     * @param x the x coordinate of the top-left corner of the grid
     * @param y the y coordinate of the top-left corner of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements a vector of pointers to the WindowElements in the grid
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int numColumns;
    int scrollOffset = 0;
};

ScrollingColumnsLayout::ScrollingColumnsLayout(int numColumns) : numColumns(numColumns) {}

void ScrollingColumnsLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int columnWidth = width / numColumns;
    int xOffset = 0;

    int numElements = min((int)elements.size(), numColumns);
    for (int i = 0; i < numElements; i++) {
        elements[i + scrollOffset]->paint(x + xOffset, y, columnWidth, height);
        xOffset += columnWidth;
    }
}

bool ScrollingColumnsLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
    selectedElement->setState(State::ERROR);
    // Find the index of the selected element in the vector
    int selectedIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == selectedElement) {
            selectedIndex = i;
            break;
        }
    }

    if (selectedIndex == -1) {
        return false;
    }

    if (direction == ArrowKey::LEFT) {
        for (int i = selectedIndex - 1; i >= 0; i--) {
            if (elements[i]->select()) {
                scrollOffset = max(i - 1, 0);
                return true;
            }
        }
    } else if (direction == ArrowKey::RIGHT) {
        for (int i = selectedIndex + 1; i < elements.size(); i++) {
            if (elements[i]->select()) {
                scrollOffset = min(i - numColumns + 2, (int)elements.size() - numColumns);
                return true;
            }
        }
    }
    return false;
}
