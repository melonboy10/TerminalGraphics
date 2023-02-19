#include "layout.h"

using namespace std;

/**
 * @param widths an array of integers representing the width of each element in the grid
 */
class SquareGridLayout : public Layout {
   public:
    /**
     * @param widths an array of integers representing the width of each element in the grid
     */
    SquareGridLayout(int widths[]);
    /**
     * A grid where the width of each element is the same as the height
     * @param x the x coordinate of the top-left corner of the grid
     * @param y the y coordinate of the top-left corner of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements a vector of pointers to the WindowElements in the grid
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

   private:
    int* widths;
    int scrollOffset = 0;
};

SquareGridLayout::SquareGridLayout(int widths[]) : widths(widths) {}

void SquareGridLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalWidth = 0;
    for (int i = 0; i < sizeof(widths) / sizeof(int); i++) {
        totalWidth += widths[i];
    }

    int xOffset = 0;
    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + xOffset, y + yOffset, width / totalWidth * widths[i], width / totalWidth * widths[i]);
        xOffset += widths[i] / totalWidth * width;
        if (i % (sizeof(widths) / sizeof(int)) == sizeof(widths) / sizeof(int) - 1) {
            xOffset = 0;
            yOffset += widths[i] / totalWidth * width;
        }
    }
}