#include "element.h"

class Spacer: public WindowElement {
  public:
    Spacer(int height) : WindowElement(0.0, height) {}
    void paint(int x, int y, int width, int height) override {}
};