#include <cmath>

#include "layout.h"

using namespace std;

/**
 * @param widths an array of integers representing the width of each element in the grid
 */
class SquareGridLayout : public Layout {
   public:
    /**
     * @param numColumns the number of columns in the grid
     */
    SquareGridLayout(int numColumns);
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

SquareGridLayout::SquareGridLayout(int numColumns) : numColumns(numColumns) {}

void SquareGridLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int columnWidth = width / numColumns;
    int maxNumberOfRows = height / columnWidth / 2 + 1;
    int xOffset = 0;
    int yOffset = -scrollOffset * columnWidth / 2;

    int numElements = min((int)elements.size(), maxNumberOfRows * numColumns);

    for (int i = 0; i < numElements; i++) {
        elements[i]->paint(x + xOffset, y + yOffset, columnWidth, columnWidth / 2);
        xOffset += columnWidth;

        if (i % numColumns == numColumns - 1) {
            xOffset = 0;
            yOffset += columnWidth / 2;
        }
    }
}

bool SquareGridLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
    selectedElement->setState(State::ERROR);
    // Find the index of the selected element in the vector
    int selectedIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == selectedElement) {
            selectedIndex = i;
            break;
        }
    }

    // If the selected element is not found or cannot be selected, return false
    if (selectedIndex == -1) {
        return false;
    }

    // Determine the index of the next selectable element based on the direction
    int nextIndex = -1;
    switch (direction) {
        case ArrowKey::UP:
            nextIndex = selectedIndex - numColumns;
            break;
        case ArrowKey::DOWN:
            nextIndex = selectedIndex + numColumns;
            break;
        case ArrowKey::LEFT:
            nextIndex = selectedIndex - 1;
            break;
        case ArrowKey::RIGHT:
            nextIndex = selectedIndex + 1;
            break;
    }

    // Check if the next index is valid and the element at that index is selectable
    if (nextIndex >= 0 && nextIndex < elements.size() && elements[nextIndex]->select()) {
        // if the next element is not visible, scroll the grid
        int nextIndexRow = nextIndex / numColumns;
        scrollOffset = max(0, nextIndexRow - 1);
        return true;
    }

    // Otherwise, return false
    return false;
}
