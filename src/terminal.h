#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <string>
#include <vector>
#include "util.h"
#include "window.h"

using namespace std;

class Terminal {
    public:
    Terminal() {
        initTerminal();
    }
   private:
    const static struct winsize size;
    const static int minWidth = 100;
    const static int minHeight = 30;

    const static Group* rootWindow;

    static void initTerminal();
    static void checkScreenSize();
};

void Terminal::initTerminal() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    rootWindow = new Group();
}

void Terminal::checkScreenSize() {
    if (size.ws_col < minWidth || size.ws_row < minHeight) {
        cout << getColor(BRIGHT_CYAN) << "🚨 Screen size is too small." << endl;
        cout << "Please resize your Window to at least" << minWidth << "x" << minHeight << " characters." << endl;
        cout << "Your terminal is currently " << size.ws_col << "x" << size.ws_row << " characters." << endl;
        cout << getColor(RESET);
        std::exit(1);
    }
}

#endif