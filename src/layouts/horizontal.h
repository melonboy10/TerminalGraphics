#include "layout.h"
#include <tuple>

using namespace std;

class HorizontalLayout : public Layout {
   public:
    HorizontalLayout();
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
};

HorizontalLayout::HorizontalLayout() {}

void HorizontalLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    vector<tuple<int, int>> sizes;
    int totalWidth = 0;
    for (int i = 0; i < elements.size(); i++) {
        sizes.push_back(elements[i]->getFixedSize(width, height));
        totalWidth += get<0>(sizes[i]);
    }

    int xOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x + xOffset, y, get<0>(sizes[i]), height);
        xOffset += get<0>(sizes[i]) / totalWidth * width;
    }
}
