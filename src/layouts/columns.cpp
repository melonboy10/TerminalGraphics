#include <vector>

#include "layout.h"
#include "columns.h"

using namespace std;

ColumnLayout::ColumnLayout(int widths[]) : widths(widths) {}

void ColumnLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    int totalWidth = 0;
    for (int i = 0; i < sizeof(widths) / sizeof(int); i++) {
        totalWidth += widths[i];
    }
    int segment = width / totalWidth;
    int numElements = min(elements.size(), sizeof(widths) / sizeof(int));
    int xOffset = 0;
    for (int i = 0; i < numElements; i++) {
        elements[i]->paint(x + xOffset, y, segment * widths[i], height);
        xOffset += segment * widths[i];
    }
}

bool ColumnLayout::selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) {
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
        selectedElement->setSelected(false);
        elements[nextIndex]->setSelected(true);
        return true;
    } else {
        return false;
    }
}
