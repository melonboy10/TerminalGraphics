#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>
#include <string>
#include <vector>
#include "util.h"
#include "group.h"

using namespace std;

class Terminal {
   public:
    Terminal(Layout* layout);

   private:
    const static struct winsize size;
    const static int minWidth = 100;
    const static int minHeight = 30;

    const static Group* rootWindow;

    static void initTerminal();
    static void checkScreenSize();
    static void exit();
};

Terminal::Terminal(Layout* layout) {
    initTerminal();
    rootWindow = new Group(layout);
}

Terminal::~Terminal() {
    exit();
}

void Terminal::initTerminal() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
}

void Terminal::checkScreenSize() {
    if (size.ws_col < minWidth || size.ws_row < minHeight) {
        cout << getColorCode(LIGHT_CYAN) << "🚨 Screen size is too small." << endl;
        cout << "Please resize your Window to at least" << minWidth << "x" << minHeight << " characters." << endl;
        cout << "Your terminal is currently " << size.ws_col << "x" << size.ws_row << " characters." << endl;
        cout << getColorCode(RESET);
        std::exit(1);
    }
}

void Terminal::exit() {
    showCursor();
    setCursorPosition(0, 0);

    for (int t = 5; t > 0; t--) {
        int time = t * t;
        for (int i = 0; i < size.ws_col; i++) {
            float x = (float)i / (float)size.ws_col * 2 - 1;
            float eqTop = -pow(abs(x), time) + 1;
            float eqBottom = pow(abs(x), time) - 1;

            for (int i = 0; i < size.ws_row; i++) {
                float y = (float)i / (float)size.ws_row * 2 - 1;
                if (y < eqTop && y > eqBottom) {
                    cout << "▓";
                }
            }
        }

        sleep(1);
    }

    for (int i = 0; i < size.ws_col; i++) {
        for (int i = 0; i < size.ws_row; i++) {
            cout << "\b";
        }
        cout << "\b";
    }
    cout << "\033[2J\033[1;1H"<< "Goodbye. 👋" << endl;
}