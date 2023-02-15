#include "layout.h"

using namespace std;

class SquareGridLayout: public Layout {
    public:
        SquareGridLayout(int* widths);
        void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

    private:
        int* widths;
        int scrollOffset = 0;
};

SquareGridLayout::SquareGridLayout(int* widths): widths(widths) {}

void SquareGridLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
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