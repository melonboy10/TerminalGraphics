#include <vector>

#include "layout.h"

using namespace std;

/**
 * Constructor for ColumnLayout object
 * @param widths an array of integers representing the width of each element in the layout
 */
class ColumnLayout : public Layout {
   public:
    /**
     * Constructor for ColumnLayout object
     * @param widths an array of integers representing the width of each element in the layout
     */
    ColumnLayout(int widths[]);

    /**
     * Paints the layout on the screen
     * @param x the x position of the layout on the screen
     * @param y the y position of the layout on the screen
     * @param width the width of the layout on the screen
     * @param height the height of the layout on the screen
     * @param elements a vector of WindowElement objects to be included in the layout
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

   private:
    int* widths;
};

ColumnLayout::ColumnLayout(int widths[]) : widths(widths) {}

void ColumnLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalWidth = 0;
    int numElements = min(elements.size(), sizeof(widths) / sizeof(int));
    for (int i = 0; i < numElements; i++) {
        totalWidth += widths[i];
    }

    int yOffset = 0;
    for (int i = 0; i < numElements; i++) {
        elements[i]->paint(x, y + yOffset, width, widths[i] / totalWidth * height);
        yOffset += widths[i] / totalWidth * height;
    }
}