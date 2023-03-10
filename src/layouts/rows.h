#include "layout.h"

using namespace std;

/**
 * Constructs a RowLayout with the given array of heights
 * @param heights array of heights of each element
 */
class RowLayout : public Layout {
   public:
    /**
     * Constructs a RowLayout with the given array of heights
     * @param heights array of heights of each element
     */
    RowLayout(int heights[]);

    /**
     * Paints the list of elements in a vertical row
     * @param x the x coordinate of the starting position
     * @param y the y coordinate of the starting position
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements the list of WindowElements to paint
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

    /**
     * Frees the memory allocated for the heights array
     */
    ~RowLayout();

   private:
    int* heights;
};

RowLayout::RowLayout(int heights[]) : heights(heights) {}

RowLayout::~RowLayout() {
    delete[] heights;
}

void RowLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    const int numberOfRows = sizeof(heights) / sizeof(int);
    int totalHeight = 0;
    for (int i = 0; i < numberOfRows; i++) {
        totalHeight += heights[i];
    }
    int yOffset = 0;
    int numberOfHiddenElements = 0;
    for (int i = 0; i < numberOfRows; i++) {
        if (i >= elements.size()) break;
        if (elements[i]->hidden) {
            numberOfHiddenElements++;
            continue;
        }
        int segment = height * heights[i - numberOfHiddenElements] / totalHeight;
        elements[i]->paint(x, y + yOffset, width, segment);
        yOffset += segment;
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
                if (elements[i]->select()) {
                    return true;
                }
            }
        }
    } else if (direction == ArrowKey::DOWN) {
        if (currentIndex < elements.size() - 1) {
            // search for the next selectable element below
            for (int i = currentIndex + 1; i < elements.size(); i++) {
                if (elements[i]->select()) {
                    return true;
                }
            }
        }
    }

    return false;
}