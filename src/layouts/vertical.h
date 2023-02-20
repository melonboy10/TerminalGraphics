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
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;
};

VerticalLayout::VerticalLayout() {}

void VerticalLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    vector<tuple<int, int>> sizes;
    int totalWidth = 0;
    for (int i = 0; i < elements.size(); i++) {
        sizes.push_back(elements[i]->getFixedSize(width - totalWidth, height));
        totalWidth += get<1>(sizes[i]);
    }

    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + (width - get<0>(sizes[i])) / 2, y + (width - totalWidth) / 2 + yOffset, get<0>(sizes[i]), get<1>(sizes[i]));
        yOffset += get<1>(sizes[i]);
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

    if (currentIndex == -1) {
        return false;
    }

    int nextIndex = -1;
    if (direction == ArrowKey::UP) {
        if (currentIndex > 0) {
            // search for the next selectable element to the left
            for (int i = currentIndex - 1; i >= 0; i--) {
                if (elements[i]->select()) {
                    return true;
                }
            }
        }
    } else if (direction == ArrowKey::DOWN) {
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
