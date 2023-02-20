#ifndef GRID_H
#define GRID_H

#include <vector>

#include "layout.h"

using namespace std;

/**
 * A class that represents a grid layout.
 */
#include <vector>

#include "layout.h"


/**
 * A constructor that initializes a GridLayout instance with the provided
 * widths and heights.
 *
 * @param widths the array of the column widths
 * @param heights the array of the row heights
 */
class GridLayout : public Layout {
   public:
    /**
     * A constructor that initializes a GridLayout instance with the provided
     * widths and heights.
     *
     * @param widths the array of the column widths
     * @param heights the array of the row heights
     */
    GridLayout(int widths[], int heights[]);

    /**
     * Paints the grid layout on the screen with the given x and y positions,
     * width, height, and vector of window elements.
     *
     * @param x the x-coordinate of the grid
     * @param y the y-coordinate of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements the vector of WindowElement objects to be painted
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
    int* widths;   // an array of the column widths
    int* heights;  // an array of the row heights
};

#endif
