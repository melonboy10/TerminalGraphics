#include <math.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "elements/group.h"
#include "util.h"

using namespace std;

/**
 * Constructor method for Terminal class.
 * Initializes the Terminal.
 * @param layout: A pointer to a layout object.
 */
class Terminal {
   public:
    /**
     * Constructor method for Terminal class.
     * Initializes the Terminal.
     * @param layout: A pointer to a layout object.
     */
    Terminal(Layout* layout);

    /**
     * Destructor method for Terminal class.
     * Exits the terminal.
     */
    ~Terminal();

    /**
     * Checks if the user has pressed any keys.
     * If the user has pressed a key, it is handled.
     */
    static void checkInputs();

    /**
     * Initializes the Terminal window.
     */
    static void initTerminal();

    /**
     * Checks if the size of the Terminal window is big enough to display all content.
     * If the window is too small, prints an error message and exits the program.
     */
    static void checkScreenSize();

    /**
     * Exits the Terminal window with a fancy animation.
     */
    static void exit();

    static Group* rootWindow;
    static termios oldTerminalSettings;
    static struct winsize size;
    static struct pollfd fds[1];
    static bool exitFlag;
    const static int minWidth = 100;
    const static int minHeight = 30;
};

termios Terminal::oldTerminalSettings;
struct winsize Terminal::size;
Group* Terminal::rootWindow;
struct pollfd Terminal::fds[1];
bool Terminal::exitFlag = false;

Terminal::Terminal(Layout* layout) {
    initTerminal();
    rootWindow = new Group(layout);
    // rootWindow->paint(0, 0, size.ws_col, size.ws_row);
}

Terminal::~Terminal() {
    // printf("\033[?1049l");  // Disable alternate screen buffer
    // printf("\033[?25h");    // Show cursor
    // printf("\033[?1000l");  // Disable mouse input
    // tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
    exit();
}

void Terminal::initTerminal() {
    // printf("\033[?1049h");  // Enable alternate screen buffer

    struct termios raw_attr;

    tcgetattr(STDIN_FILENO, &oldTerminalSettings);
    raw_attr = oldTerminalSettings;
    cfmakeraw(&raw_attr);
    raw_attr.c_lflag &= ~(ICANON | ECHO);
    // raw_attr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_attr);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    // printf("\033[?1000h");  // Enable mouse input
    hideCursor();

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
}

// Checking the size of the terminal window and if it is too small, it will print an error message and exit the program.
void Terminal::checkScreenSize() {
    if (size.ws_col < minWidth || size.ws_row < minHeight) {
        cout << getColorCode(LIGHT_CYAN) << "🚨 Screen size is too small." << endl;
        cout << "Please resize your Window to at least" << minWidth << "x" << minHeight << " characters." << endl;
        cout << "Your terminal is currently " << size.ws_col << "x" << size.ws_row << " characters." << endl;
        cout << getColorCode(RESET);
        std::exit(1);
    }
}

void Terminal::checkInputs() {
    rootWindow->select();
    rootWindow->paint(0, 0, size.ws_col, size.ws_row);
    cout.flush();

    string input;
    while (!exitFlag) {
        int c = getchar();

        if (c == 3) {  // Check for Control+C
            exitFlag = true;
        } else if (c == 27) {        // Check for escape sequence
            if (getchar() == '[') {  // Check for arrow keys
                ArrowKey arrow = getArrowKey(getchar());
                if (arrow != ArrowKey::NONE) {
                    WindowElement::focusedElement->arrowKeyEvent(arrow, WindowElement::focusedElement);
                }
            }
        } else {
            WindowElement::focusedElement->keyEvent(c);
        }

        rootWindow->paint(0, 0, size.ws_col, size.ws_row);
        cout.flush();
    }
    exit();
}

void Terminal::exit() {
    showCursor();
    setCursorPosition(0, 0);

    // printf("\033[?1000l");  // Disable mouse input
    oldTerminalSettings.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
    tcflush(STDIN_FILENO, TCIFLUSH);

    // for (int t = 5; t > 0; t--) {
    //     int time = t * t;
    //     for (int i = 0; i < size.ws_col; i++) {
    //         float x = (float)i / (float)size.ws_col * 2 - 1;
    //         float eqTop = -pow(abs(x), time) + 1;
    //         float eqBottom = pow(abs(x), time) - 1;
    //
    //         for (int i = 0; i < size.ws_row; i++) {
    //             float y = (float)i / (float)size.ws_row * 2 - 1;
    //             if (y < eqTop && y > eqBottom) {
    //                 cout << "▓";
    //             }
    //         }
    //     }
    //
    //     sleep(1);
    // }
    cout << "\033[2J\033[1;1H"
         //  << "\033[1J"
         << "Goodbye. 👋" << endl;
}