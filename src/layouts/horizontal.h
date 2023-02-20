#ifndef HORIZONTAL_H
#define HORIZONTAL_H

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
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;
};

#endif
