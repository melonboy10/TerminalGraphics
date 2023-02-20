#include "layout.h"
#include "rows.h"

using namespace std;

RowLayout::RowLayout(int heights[]) : heights(heights) {}

void RowLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalHeight = 0;
    for (int i = 0; i < sizeof(heights) / sizeof(int); i++) {
        totalHeight += heights[i];
    }
    int segment = height / totalHeight;
    int numElements = min(elements.size(), sizeof(heights) / sizeof(int));
    int yOffset = 0;
    for (int i = 0; i < numElements; i++) {
        elements[i]->paint(x, y + yOffset, width, segment * heights[i]);
        yOffset += segment * heights[i];
    }
}

bool RowLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
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
            // search for the next selectable element above
            for (int i = currentIndex - 1; i >= 0; i--) {
                if (elements[i]->isSelectable()) {
                    nextIndex = i;
                    break;
                }
            }
        }
    } else if (direction == ArrowKey::DOWN) {
        if (currentIndex < elements.size() - 1) {
            // search for the next selectable element below
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
        selectedElement->setSelected(false);
        elements[nextIndex]->setSelected(true);
        return true;
    } else {
        return false;
    }
}
