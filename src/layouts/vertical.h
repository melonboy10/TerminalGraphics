#include <tuple>

#include "layout.h"

using namespace std;

/**
 * A vertical layout class for arranging WindowElements vertically.
 */
class VerticalLayout : public Layout {
   public:
    /**
     * Constructs a new VerticalLayout.
     */
    VerticalLayout();

    /**
     * Paints the given vector of elements in a vertical layout.
     * @param x the x-coordinate of the top-left corner of the layout
     * @param y the y-coordinate of the top-left corner of the layout
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements the vector of WindowElements to paint
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
};

VerticalLayout::VerticalLayout() {}

void VerticalLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    vector<tuple<int, int>> sizes;
    int totalHeight = 0;
    for (int i = 0; i < elements.size(); i++) {
        sizes.push_back(elements[i]->getFixedSize(width, height));
        totalHeight += get<1>(sizes[i]);
    }

    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x, y + (height - yOffset) / 2, width, get<1>(sizes[i]));
        yOffset += get<1>(sizes[i]) / totalHeight * height;
    }
}

bool VerticalLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
    int currentIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == selectedElement) {
            currentIndex = i;
            break;
        }
    }

    int nextIndex = -1;
    if (direction == ArrowKey::UP) {
        if (currentIndex > 0) {
            // search for the next selectable element to the left
            for (int i = currentIndex - 1; i >= 0; i--) {
                if (elements[i]->isSelectable()) {
                    nextIndex = i;
                    break;
                }
            }
        }
    } else if (direction == ArrowKey::DOWN) {
        if (currentIndex < elements.size() - 1) {
            // search for the next selectable element to the right
            for (int i = currentIndex + 1; i < elements.size(); i++) {
                if (elements[i]->isSelectable()) {
                    nextIndex = i;
                    break;
                }
            }
        }
    }

    // If a next selectable element was found, select it and return true
    if (nextIndex != -1) {
        elements[nextIndex]->select();
        return true;
    } else {
        return false;
    }
}
