#ifndef VERTICAL_H
#define VERTICAL_H

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

#endif
