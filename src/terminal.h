#ifndef TERMINAL_H
#define TERMINAL_H

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
    static WindowElement* focusedElement;
    static termios oldTerminalSettings;
    static struct winsize size;
    static struct pollfd fds[1];
    static bool exitFlag;
    const static int minWidth = 100;
    const static int minHeight = 30;
};

#endif
