#include "layout.h"
#include <tuple>

using namespace std;

class VerticalLayout : public Layout {
   public:
    VerticalLayout();
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
};

VerticalLayout::VerticalLayout() {}

void VerticalLayout::paint(int x, int y, int width, int height, vector<WindowElement*> elements) {
    vector<tuple<int, int>> sizes;
    int totalHeight = 0;
    for (int i = 0; i < elements.size(); i++) {
        sizes.push_back(elements[i]->getFixedSize(width, height));
        totalHeight += get<1>(sizes[i]);
    }

    int yOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->paint(x, y + yOffset, width, get<1>(sizes[i]));
        yOffset += get<1>(sizes[i]) / totalHeight * height;
    }
}