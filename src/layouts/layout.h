#include "element.h"

using namespace std;

class Layout {
  public:
    virtual void paint(int x, int y, int width, int height, vector<WindowElement*> elements) = 0;
};