#include "layout.h"
#include <vector>

using namespace std;

class GridLayout : public Layout {
   public:
    GridLayout(int* widths, int* heights);
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

   private:
    int* widths;
    int* heights;
};

GridLayout::GridLayout(int* widths, int* heights) {
    this->widths = widths;
    this->heights = heights;
}

void GridLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalWidth = 0;
    int numWidths = min(elements.size(), sizeof(widths) / sizeof(int));
    for (int i = 0; i < numWidths; i++) {
        totalWidth += widths[i];
    }

    int totalHeight = 0;
    int numHeights = min(elements.size(), sizeof(heights) / sizeof(int));
    for (int i = 0; i < numHeights; i++) {
        totalHeight += heights[i];
    }

    int xOffset = 0;
    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + xOffset, y + yOffset, widths[i] / totalWidth * width, heights[i] / totalHeight * height);
        xOffset += widths[i] / totalWidth * width;
        if (i % numWidths == numWidths - 1) {
            xOffset = 0;
            yOffset += heights[i] / totalHeight * height;
        }
    }
}