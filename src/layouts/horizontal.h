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
    void paint(int x, int y, int width, int height, vector<shared_ptr<WindowElement>> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<shared_ptr<WindowElement>> elements, ArrowKey direction) override;
};

HorizontalLayout::HorizontalLayout() {}

void HorizontalLayout::paint(int x, int y, int width, int height, vector<shared_ptr<WindowElement>> elements) {
    vector<tuple<int, int>> sizes;
    int totalWidth = 0;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->hidden) continue;
        sizes.push_back(elements[i]->getFixedSize(width - totalWidth, height));
        totalWidth += get<0>(sizes[i]);
    }

    int xOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i]->hidden) continue;
        elements[i]->paint(x + (width - totalWidth) / 2 + xOffset, y + (height - get<1>(sizes[i])) / 2, get<0>(sizes[i]), get<1>(sizes[i]));
        xOffset += get<0>(sizes[i]);
    }
}

bool HorizontalLayout::selectNext(WindowElement* selectedElement, vector<shared_ptr<WindowElement>> elements, ArrowKey direction) {
    int currentIndex = -1;
    for (int i = 0; i < elements.size(); i++) {
        if (elements[i].get() == selectedElement) {
            currentIndex = i;
            break;
        }
    }

    int nextIndex = -1;
    if (direction == ArrowKey::LEFT) {
        if (currentIndex > 0) {
            // search for the next selectable element to the left
            for (int i = currentIndex - 1; i >= 0; i--) {
                if (elements[i]->select()) {
                    return true;
                }
            }
        }
    } else if (direction == ArrowKey::RIGHT) {
        if (currentIndex < elements.size() - 1) {
            // search for the next selectable element to the right
            for (int i = currentIndex + 1; i < elements.size(); i++) {
                if (elements[i]->select()) {
                    return true;
                }
            }
        }
    }

    return false;
}
