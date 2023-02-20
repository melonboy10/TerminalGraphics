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

    int numElements = min(elements.size(), maxNumberOfRows * numColumns);

    for (int i = 0; i < numElements; i++) {
        if (i % numColumns == 0) {
            xOffset = 0;
            yOffset += columnWidth;
        }
        elements[i]->paint(x + xOffset, y + yOffset, columnWidth, columnWidth);
        xOffset += columnWidth;
    }
}