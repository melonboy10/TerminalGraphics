#include <tuple>

#include "layout.h"

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
        sizes.push_back(elements[i]->getFixedSize(width - totalWidth, height));
        totalWidth += get<0>(sizes[i]);
    }

    int xOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + (width - totalWidth) / 2 + xOffset, y + (height - get<1>(sizes[i])) / 2, get<0>(sizes[i]), get<1>(sizes[i]));
        xOffset += get<0>(sizes[i]);
    }
}

bool HorizontalLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
    int currentIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == selectedElement) {
            currentIndex = i;
            break;
        }
    }

    int nextIndex = -1;
    if (direction == ArrowKey::LEFT) {
        if (currentIndex > 0) {
            // search for the next selectable element to the left
            for (int i = currentIndex - 1; i >= 0; i--) {
                if (elements[i]->isSelectable()) {
                    nextIndex = i;
                    break;
                }
            }
        }
    } else if (direction == ArrowKey::RIGHT) {
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
