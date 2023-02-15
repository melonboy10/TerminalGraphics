#include "element.h"

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
};
