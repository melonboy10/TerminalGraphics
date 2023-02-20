#include "element.h"
#include "image.h"

using namespace std;

Image::Image(string path, int size) : path(path), WindowElement(size, size) {}

void Image::setImage(string path) {
    this->path = path;
}

void Image::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (path.length() > 0) {
        drawImage(path, x, y, width, height);
    }
}
