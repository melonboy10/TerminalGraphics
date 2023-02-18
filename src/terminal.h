#include <math.h>
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
 * Terminal class is responsible for managing the terminal and printing content to the terminal.
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

   private:
    static termios oldTerminalSettings;
    static struct winsize size;
    const static int minWidth = 100;
    const static int minHeight = 30;

    static Group* rootWindow;

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
};

termios Terminal::oldTerminalSettings;
struct winsize Terminal::size;
Group* Terminal::rootWindow;

Terminal::Terminal(Layout* layout) {
    initTerminal();
    rootWindow = new Group(layout);
}

Terminal::~Terminal() {
    printf("\033[?1049l");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminalSettings);
    exit();
}

void Terminal::initTerminal() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    tcgetattr(STDIN_FILENO, &oldTerminalSettings);
    termios new_attr = oldTerminalSettings;
    new_attr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
    printf("\033[?1049h");
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
    cout << "\033[2J\033[1;1H"
         << "\033[1J"
         << "Goodbye. 👋" << endl;
}