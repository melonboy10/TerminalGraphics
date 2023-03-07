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
    bool codeMode = false;
    while (getline(file, line)) {
        // if the line is ``` then switch to code mode
        if (line == "```") {
            codeMode = !codeMode;
            continue;
        }
        if (codeMode) {
            // Text in file: \033[1;32mint\033[0m x = \033[1;32m5\033[0m;
            // Print text in color: int x = 5;
            // drawRawText(line, x, y + lineNum);

            string::size_type start = 0;
            string::size_type end = 0;
            while (start != string::npos) {
                start = line.find("\\033[", end);
                if (start != string::npos) {
                    end = line.find("m", start);
                    if (end != string::npos) {
                        string colorCode = line.substr(start, end - start + 1);
                        string text = line.substr(end + 1);
                        end = text.find("\\033[");
                        if (end != string::npos) {
                            text = text.substr(0, end);
                        }
                        drawText(text, x + start, y + lineNum, stoi(colorCode.substr(2)));
                    }
                } else {
                    drawText(line, x, y + lineNum);
                    break;
                }
            }
        } else {
            // if the line is not a code line then print it in a normal font
            drawText(line, x, y + lineNum, BLUE);
        }
        lineNum++;
    }
};