#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum Color {
    RESET = 0,
    BOLD = 1,
    DIM = 2,
    UNDERLINED = 4,
    BLINK = 5,
    REVERSE = 7,
    HIDDEN = 8,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    GRAY = 90,
    LIGHT_RED = 91,
    LIGHT_GREEN = 92,
    LIGHT_YELLOW = 93,
    LIGHT_BLUE = 94,
    LIGHT_MAGENTA = 95,
    LIGHT_CYAN = 96,
    LIGHT_WHITE = 97,
};

enum State {
    DEFAULT = WHITE,
    DISABLED = DIM,
    SUCCESS = GREEN,
    ERROR = RED,
};

string getColorCode(int color) {
    return "\033[" + to_string(color) + "m";
}

void drawText(string text, int x, int y, int color = WHITE) {
    setCursorPosition(x, y);
    cout << getColorCode(color) << text << "\033[0m";
}

void clearArea(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        setCursorPosition(x, y + i);
        for (int j = 0; j < width; j++) {
            cout << " ";
        }
    }
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

void drawBox(int x, int y, int width, int height) {
    drawText("╭", x, 0);
    drawText("╰", x, height);

    drawText("╮", x + width - 1, 0);
    drawText("╯", x + width - 1, height);

    // Draw side borders
    for (int i = 1; i < height - 1; i++) {
        drawText("│", x, i);
        drawText("│", x + width - 1, i);
    }

    // Draw top & bottom border
    for (int i = 1; i < width - 1; i++) {
        drawText("─", x + i, 0);
        drawText("─", x + i, height);
    }
}

void drawBox(int x, int y, int width, int height, string title) {
    drawBox(x, y, width, height);
    drawText("┤" + title + "├", x + 1, 0);
}

void drawImage(string path, int x, int y, int width, int height) {
    vector<vector<int>> image = readImage(path);
    vector<vector<int>> scaledImage = scaleImage(image, width, height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int colorCode = scaledImage[j][i];
            drawText("█", x + i, y + j, (Color)(colorCode + 30));
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
