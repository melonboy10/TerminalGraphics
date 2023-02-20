#include <fstream>

#include "element.h"

using namespace std;

/**
 * Constructs an icon object with a given path and size.
 *
 * @param path The path of the icon to be constructed.
 * @param width The width of the icon to be constructed.
 * @param height The height of the icon to be constructed.
 */
class Icon : public WindowElement {
   public:
    /**
     * Constructs an icon object with a given path and size.
     *
     * @param path The path of the icon to be constructed.
     * @param width The width of the icon to be constructed.
     * @param height The height of the icon to be constructed.
     */
    Icon(string path, int width, int height);

    /**
     * Sets the icon of the icon object.
     *
     * @param path The path of the icon to be set.
     */
    void setIcon(string path);

    /**
     * Paints the icon object at the given coordinates.
     *
     * @param x The x coordinate at which the icon should be painted.
     * @param y The y coordinate at which the icon should be painted.
     * @param width The width at which the icon should be painted.
     * @param height The height at which the icon should be painted.
     */
    void paint(int x, int y, int width, int height) override;

   private:
    string path = "";
};

Icon::Icon(string path, int width, int height) : path(path), WindowElement(width, height) {}

void Icon::setIcon(string path) {
    this->path = path;
}

void Icon::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (hidden) return;

    ifstream file(path);
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        drawText(line, x, y + lineNum);
        lineNum++;
    }
    printf("\033[0m");
    file.close();
}