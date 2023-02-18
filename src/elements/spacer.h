#include "element.h"

using namespace std;

/**
 * This class extends WindowElement class.
 * It creates Spacer objects with given height.
 * @param height The height of Spacer
 */
class Spacer : public WindowElement {
   public:
    /**
     * This class extends WindowElement class.
     * It creates Spacer objects with given height.
     * @param height The height of Spacer
     */
    Spacer(int height) : WindowElement(0.0, height) {}
    /**
     * This function is an override to the paint function in the WindowElement class.
     * It does not paint any text or spaces.
     * @param x The x coordinate of the Spacer object
     * @param y The y coordinate of the Spacer object
     * @param width The width of the Spacer object
     * @param height The height of the Spacer object
     */
    void paint(int x, int y, int width, int height) override {}
};

//::