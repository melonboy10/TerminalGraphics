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
    int maxNumberOfRows = height / columnWidth;
    int xOffset = 0;
    int yOffset = -scrollOffset * columnWidth;

    int numElements = min((int)elements.size(), maxNumberOfRows * numColumns);
    // Q: When is numElements 0?
    // A: When there are no elements in the vector

    drawText("█████████████████████" + to_string(elements.size()) + "████████████████████", 25, 25, Color::RED);

    for (int i = 0; i < numElements; i++) {
        // For debugging draw a rectangle around each element
        // drawBox(x + xOffset, y + yOffset, columnWidth, columnWidth);
        elements[i]->paint(x + xOffset, y + yOffset, columnWidth, columnWidth);
        drawText("██████████████████████████████████████████████████████████", 25, 25, Color::RED);

        // elements[i]->paint(22, 22, 22, 22);
        // elements[i]->paint(x + xOffset, y + yOffset, 25, 25);
        xOffset += columnWidth;
        if (i % numColumns == 0) {
            xOffset = 0;
            yOffset += columnWidth;
        }
    }
}

bool SquareGridLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
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

    int numColumns = this->numColumns;
    int numRows = (elements.size() + numColumns - 1) / numColumns;

    int nextIndex = -1;
    if (direction == ArrowKey::UP) {
        nextIndex = selectedIndex - numColumns;
    } else if (direction == ArrowKey::DOWN) {
        nextIndex = selectedIndex + numColumns;
    } else if (direction == ArrowKey::LEFT) {
        nextIndex = selectedIndex - 1;
    } else if (direction == ArrowKey::RIGHT) {
        nextIndex = selectedIndex + 1;
    }

    if (nextIndex < 0 || nextIndex >= elements.size()) {
        return false;
    }

    int selectedRow = selectedIndex / numColumns;
    int selectedCol = selectedIndex % numColumns;
    int nextRow = nextIndex / numColumns;
    int nextCol = nextIndex % numColumns;

    if (nextRow < 0 || nextRow >= numRows) {
        // Scroll to show the selected row
        int newOffset = scrollOffset;
        if (nextRow < 0) {
            newOffset += nextRow;
        } else {
            newOffset += nextRow + 1;
        }
        scrollOffset = newOffset;
        return true;
    }

    return false;
}
