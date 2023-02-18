#include "layout.h"

using namespace std;

/**
 * Constructs a RowLayout with the given array of heights
 * @param heights array of heights of each element
 */
class RowLayout : public Layout {
   public:
    /**
     * Constructs a RowLayout with the given array of heights
     * @param heights array of heights of each element
     */
    RowLayout(int heights[]);

    /**
     * Paints the list of elements in a vertical row
     * @param x the x coordinate of the starting position
     * @param y the y coordinate of the starting position
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements the list of WindowElements to paint
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

   private:
    int* heights;
};

RowLayout::RowLayout(int heights[]) : heights(heights) {}

void RowLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalHeight = 0;
    int numElements = min(elements.size(), sizeof(heights) / sizeof(int));
    for (int i = 0; i < numElements; i++) {
        totalHeight += heights[i];
    }

    int yOffset = 0;
    for (int i = 0; i < numElements; i++) {
        elements[i]->paint(x, y + yOffset, width, heights[i] / totalHeight * height);
        yOffset += heights[i] / totalHeight * height;
    }
}
