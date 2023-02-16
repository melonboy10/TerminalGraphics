#include "layout.h"
#include <vector>

using namespace std;

/**
 * A class that represents a grid layout.
 */
#include "layout.h"
#include <vector>

using namespace std;

/**
 * A class that represents a grid layout with fractional widths and heights.
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

   private:
    int* widths; // an array of the column widths
    int* heights; // an array of the row heights
};


GridLayout::GridLayout(int widths[], int heights[]): widths(widths), heights(heights) {}

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
        elements[i]->paint(x + xOffset, y + yOffset, widths[i] / totalWidth * width, heights[i] / totalHeight * height);
        xOffset += widths[i] / totalWidth * width;
        if (xOffset >= width) {
            xOffset = 0;
            yOffset += heights[i] / totalHeight * height;
        }
    }
}