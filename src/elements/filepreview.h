#include <algorithm>
#include <fstream>
#include <string>

#include "element.h"

using namespace std;

/*
* A file preview element that displays the contents of a file.

*/
class FilePreview : public WindowElement {
   public:
    /*
     * Creates a new file preview element with the given path.
     *
     * @param path The path of the file to be previewed.
     */
    FilePreview(string path);
    /*
     * Creates a new file preview element with the given path and width.
     *
     * @param path The path of the file to be previewed.
     * @param widthPercent The width of the file preview element.
     */
    FilePreview(string path, float widthPercent);

    /*
     * Sets the path of the file to be previewed.
     *
     * @param path The path of the file to be previewed.
     */
    void setPath(string path);

    /*
     * Paints the file preview element at the given coordinates.
     *
     * @param x The x coordinate at which the file preview element should be painted.
     * @param y The y coordinate at which the file preview element should be painted.
     * @param width The width at which the file preview element should be painted.
     * @param height The height at which the file preview element should be painted.
     */
    void paint(int x, int y, int width, int height);

   private:
    string path = "";
};

FilePreview::FilePreview(string path) : path(path), WindowElement(1.0, 1.0) {}

FilePreview::FilePreview(string path, float widthPercent) : path(path), WindowElement(widthPercent, 1.0) {}

void FilePreview::setPath(string path) {
    this->path = path;
}

void FilePreview::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (hidden) return;

    // print all the lines in the file
    ifstream file(path);
    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '\\' && line[i + 1] == '0' && line[i + 2] == '3' && line[i + 3] == '3') {
                line.replace(i, 4, "\033");
            }
        }
        drawText(line, x, y + lineNum);
        lineNum++;
    }
};