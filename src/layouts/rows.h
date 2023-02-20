#ifndef ROWS_H
#define ROWS_H

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

   private:
    int* heights;
};

#endif
