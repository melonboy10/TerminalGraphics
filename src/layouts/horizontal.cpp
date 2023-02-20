#include <tuple>

#include "layout.h"
#include "horizontal.h"

using namespace std;

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
