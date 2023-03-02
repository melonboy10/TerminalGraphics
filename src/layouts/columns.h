#include <vector>

#include "layout.h"

using namespace std;

/**
 * Constructor for ColumnLayout object
 * @param widths an array of integers representing the width of each element in the layout
 */
class ColumnLayout : public Layout {
   public:
    /**
     * Constructor for ColumnLayout object
     * @param widths an array of integers representing the width of each element in the layout
     */
    ColumnLayout(int widths[]);

    /**
     * Paints the layout on the screen
     * @param x the x position of the layout on the screen
     * @param y the y position of the layout on the screen
     * @param width the width of the layout on the screen
     * @param height the height of the layout on the screen
     * @param elements a vector of WindowElement objects to be included in the layout
     */
    void paint(int x, int y, int width, int height, vector<shared_ptr<WindowElement>> elements) override;

    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<shared_ptr<WindowElement>> elements, ArrowKey direction) override;

    /**
     * Destructor for ColumnLayout object
     */
    ~ColumnLayout();

   private:
    int* widths;
};

ColumnLayout::ColumnLayout(int widths[]) : widths(widths) {}

ColumnLayout::~ColumnLayout() {
    delete[] widths;
}

void ColumnLayout::paint(int x, int y, int width, int height, vector<shared_ptr<WindowElement>> elements) {
    int totalWidth = 0;
    for (int i = 0; i < sizeof(widths) / sizeof(int); i++) {
        totalWidth += widths[i];
    }
    int segment = width / totalWidth;
    unsigned long numNonHidden = 0;
    for (int i = 0; i < elements.size(); i++)
        if (!elements[i]->hidden) numNonHidden++;
    int numElements = min(numNonHidden, sizeof(widths) / sizeof(int));
    int xOffset = 0;
    for (int i = 0; i < numElements; i++) {
        if (elements[i]->hidden) continue;
        elements[i]->paint(x + xOffset, y, segment * widths[i], height);
        xOffset += segment * widths[i];
    }
}

bool ColumnLayout::selectNext(WindowElement* selectedElement, vector<shared_ptr<WindowElement>> elements, ArrowKey direction) {
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
