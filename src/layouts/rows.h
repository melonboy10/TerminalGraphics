#include "layout.h"

using namespace std;

class RowLayout : public Layout {
   public:
    RowLayout(int* heights);
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

   private:
    int* heights;
};

RowLayout::RowLayout(int* heights): heights(heights) {}

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
