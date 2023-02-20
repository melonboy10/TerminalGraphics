#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"

using namespace std;

//::

ArrowKey getArrowKey(int key) {
    switch (key) {
        case UP:
            return UP;
        case DOWN:
            return DOWN;
        case RIGHT:
            return RIGHT;
        case LEFT:
            return LEFT;
        default:
            return NONE;
    }
}

string getColorCode(int color) {
    return "\033[" + to_string(color) + "m";
}

void drawText(string text, int x, int y, int color) {
    setCursorPosition(x, y);
    cout << getColorCode(color) << text << "\033[0m";
}

void clearArea(int x, int y, int width, int height) {
    // for (int i = 0; i < height; i++) {
    //     setCursorPosition(x, y + i);
    //     for (int j = 0; j < width; j++) {
    //         cout << " ";
    //     }
    // }
}

string toCapitalCase(string text) {
    string result = "";
    bool isSpace = true;
    for (int i = 0; i < text.length(); i++) {
        if (isSpace) {
            result += toupper(text[i]);
            isSpace = false;
        } else {
            if (text[i] == ' ' || text[i] == '_') {
                isSpace = true;
                result += ' ';
            } else {
                result += tolower(text[i]);
            }
        }
    }
    return result;
}

void setCursorPosition(int x, int y) {
    cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

void showCursor() {
    cout << "\033[?25h";
}

void hideCursor() {
    cout << "\033[?25l";
}

void drawBox(int x, int y, int width, int height, int color) {
    drawText("╭", x, y, color);
    drawText("╰", x, y + height - 1, color);
    drawText("╮", x + width - 1, y, color);
    drawText("╯", x + width - 1, y + height - 1, color);

    // Draw side borders
    for (int i = 1; i < height - 1; i++) {
        drawText("│", x, y + i, color);
        drawText("│", x + width - 1, y + i, color);
    }

    // Draw top & bottom border
    string border = "";
    for (int i = 1; i < width - 1; i++) {
        border += "─";
    }
    drawText(border, x + 1, y, color);
    drawText(border, x + 1, y + height - 1, color);
}

void drawBox(int x, int y, int width, int height, string title) {
    drawBox(x, y, width, height);
    drawText("┤" + title + "├", x + 1, y);
}

void drawImage(string path, int x, int y, int width, int height) {
    vector<vector<int>> image = readImage(path);
    vector<vector<int>> scaledImage = scaleImage(image, width, height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int colorCode = scaledImage[j][i];
            drawText("█", x + i, y + j, colorCode + 30);
        }
    }
}

vector<vector<int>> readImage(string path) {
    vector<vector<int>> image;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        image.push_back(row);
    }
    return image;
}

vector<vector<int>> scaleImage(vector<vector<int>> image, int width, int height) {
    int imageWidth = image[0].size();
    int imageHeight = image.size();
    vector<vector<int>> scaledImage(height, vector<int>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int imageX = (x * imageWidth) / width;
            int imageY = (y * imageHeight) / height;
            scaledImage[y][x] = image[imageY][imageX];
        }
    }
    return scaledImage;
}
