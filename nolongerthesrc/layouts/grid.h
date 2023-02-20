#include <vector>

#include "layout.h"

using namespace std;

/**
 * A class that represents a grid layout.
 */
#include <vector>

#include "layout.h"

using namespace std;

/**
 * A constructor that initializes a GridLayout instance with the provided
 * widths and heights.
 *
 * @param widths the array of the column widths
 * @param heights the array of the row heights
 */
class GridLayout : public Layout {
   public:
    /**
     * A constructor that initializes a GridLayout instance with the provided
     * widths and heights.
     *
     * @param widths the array of the column widths
     * @param heights the array of the row heights
     */
    GridLayout(int widths[], int heights[]);

    /**
     * Paints the grid layout on the screen with the given x and y positions,
     * width, height, and vector of window elements.
     *
     * @param x the x-coordinate of the grid
     * @param y the y-coordinate of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements the vector of WindowElement objects to be painted
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
    int* widths;   // an array of the column widths
    int* heights;  // an array of the row heights
};

GridLayout::GridLayout(int widths[], int heights[]) : widths(widths), heights(heights) {}

void GridLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalWidth = 0;
    for (int i = 0; i < sizeof(widths) / sizeof(int); i++) {
        totalWidth += widths[i];
    }

    int totalHeight = 0;
    for (int i = 0; i < sizeof(heights) / sizeof(int); i++) {
        totalHeight += heights[i];
    }

    int xOffset = 0;
    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + xOffset, y + yOffset, width / totalWidth * widths[i], height / totalHeight * heights[i]);
        xOffset += width / totalWidth * widths[i];
        if (xOffset >= width) {
            xOffset = 0;
            yOffset += height / totalHeight * heights[i];
        }
    }
}

bool GridLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
    // Find the index of the selected element
    int selectedIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == selectedElement) {
            selectedIndex = i;
            break;
        }
    }
    if (selectedIndex == -1) {
        return false;  // selected element not found in the elements vector
    }

    // Find the index of the next selectable element in the given direction
    int nextIndex = -1;
    int numRows = sizeof(heights) / sizeof(int);
    int numCols = sizeof(widths) / sizeof(int);
    int currentRow = 0;
    int currentCol = 0;
    for (int i = 0; i < elements.size(); i++) {
        if (i == selectedIndex) {
            // record the current row and column of the selected element
            currentRow = i / numCols;
            currentCol = i % numCols;
            break;
        }
    }
    if (direction == ArrowKey::LEFT) {
        if (currentCol > 0) {
            // search for the previous selectable element in the current row
            for (int i = currentCol - 1; i >= 0; i--) {
                int index = currentRow * numCols + i;
                if (elements[index]->isSelectable()) {
                    nextIndex = index;
                    break;
                }
            }
            // if no selectable element found in the current row, search the row above
            if (nextIndex == -1 && currentRow > 0) {
                for (int i = numCols - 1; i >= 0; i--) {
                    int index = (currentRow - 1) * numCols + i;
                    if (elements[index]->isSelectable()) {
                        nextIndex = index;
                        break;
                    }
                }
            }
        }
    } else if (direction == ArrowKey::RIGHT) {
        if (currentCol < numCols - 1) {
            // search for the next selectable element in the current row
            for (int i = currentCol + 1; i < numCols; i++) {
                int index = currentRow * numCols + i;
                if (elements[index]->isSelectable()) {
                    nextIndex = index;
                    break;
                }
            }
            // if no selectable element found in the current row, search the row below
            if (nextIndex == -1 && currentRow < numRows - 1) {
                for (int i = 0; i < numCols; i++) {
                    int index = (currentRow + 1) * numCols + i;
                    if (elements[index]->isSelectable()) {
                        nextIndex = index;
                        break;
                    }
                }
            }
        }
    } else if (direction == ArrowKey::UP) {
        if (currentRow > 0) {
            // search for the previous selectable element in the current column
            for (int i = currentRow - 1; i >= 0; i--) {
                int index = i * numCols + currentCol;
                if (elements[index]->isSelectable()) {
                    nextIndex = index;
                    break;
                }
            }
            // if no selectable element found in the current column, search the previous column
            if (nextIndex == -1) {
                for (int i = currentCol - 1; i >= 0; i--) {
                    for (int j = numRows - 1; j >= 0; j--) {
                        int index = j * numCols + i;
                        if (elements[index]->isSelectable()) {
                            nextIndex = index;
                            break;
                        }
                    }
                    if (nextIndex != -1) {
                        break;
                    }
                }
            }
        }
    } else if (direction == ArrowKey::DOWN) {
        if (currentRow < numRows - 1) {
            // search for the next selectable element in the current column
            for (int i = currentRow + 1; i < numRows; i++) {
                int index = i * numCols + currentCol;
                if (elements[index]->isSelectable()) {
                    nextIndex = index;
                    break;
                }
            }
            // if no selectable element found in the current column, search the next column
            if (nextIndex == -1) {
                for (int i = currentCol + 1; i < numCols; i++) {
                    for (int j = 0; j < numRows; j++) {
                        int index = j * numCols + i;
                        if (elements[index]->isSelectable()) {
                            nextIndex = index;
                            break;
                        }
                    }
                    if (nextIndex != -1) {
                        break;
                    }
                }
            }
        }
    }
    // If a next selectable element was found, select it and return true
    if (nextIndex != -1) {
        elements[nextIndex]->select();
        return true;
    } else {
        return false;
    }
}