#include "layout.h"
#include "squaregrid.h"

using namespace std;

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
