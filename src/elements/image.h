#include "element.h"

using namespace std;

class Image : public WindowElement {
   public:
    Image(string path, int size = 1);
    void setImage(string path);

    void paint(int x, int y, int width, int height) override;

   private:
    string path = "";
};

Image::Image(string path, int size): path(path), WindowElement(size, size) {}

void Image::setImage(string path) {
    this->path = path;
}

void Image::paint(int x, int y, int width, int height) {
    if (path.length() > 0) {
        drawImage(path, x, y, width, height);
    }
}