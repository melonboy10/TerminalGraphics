#include "layout.h"
#include <tuple>

using namespace std;

/**
 * A class representing a horizontal layout of elements.
 */
class HorizontalLayout : public Layout {
   public:
    /**
     * Constructor for HorizontalLayout.
     */
    HorizontalLayout();
    /**
     * Paints the elements in the layout from left to right.
     * @param x the x coordinate of the layout
     * @param y the y coordinate of the layout
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements a vector of WindowElement pointers to be painted
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
};


HorizontalLayout::HorizontalLayout() {}

void HorizontalLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    vector<tuple<int, int>> sizes;
    int totalWidth = 0;
    for (int i = 0; i < elements.size(); i++) {
        sizes.push_back(elements[i]->getFixedSize(width, height));
        totalWidth += get<0>(sizes[i]);
    }

    int xOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + xOffset, y, get<0>(sizes[i]), height);
        xOffset += get<0>(sizes[i]) / totalWidth * width;
    }
}
