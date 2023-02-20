#include "../elements/element.h"

using namespace std;

/**
 * A base class for creating different Layout objects
 */
class Layout {
   public:
    /**
     * Paints the layout on the screen
     * @param x the x position of the layout on the screen
     * @param y the y position of the layout on the screen
     * @param width the width of the layout on the screen
     * @param height the height of the layout on the screen
     * @param elements a vector of WindowElement objects to be included in the layout
     */
    virtual void paint(int x, int y, int width, int height, vector<WindowElement*> elements) = 0;

    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     * @return true if the next element was selected, false if the selected element was not changed
     */
    virtual bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) = 0;
};
