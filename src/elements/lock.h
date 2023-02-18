#include "element.h"

using namespace std;

class Lock : public WindowElement {
    /**
     * Creates a new lock element with default dimensions
     */
    Lock();

    /**
     * Displays a lock icon
     * @param x - the x coordinate of the top left corner of the element
     * @param y - the y coordinate of the top left corner of the element
     * @param width - the width of the element
     * @param height - the height of the element
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Sets the message to display when the lock is active
     * @param message - the message to display
     */
    void setLockedMessage(string message);

    /**
     * Sets the locked status of the element
     * @param locked - true if the element is locked, false otherwise
     */
    void setLocked(bool locked);

   private:
    bool locked;                // whether the lock is active or not
    string lockedMessage = "";  // message to display when the lock is active
};

Lock::Lock() : locked(true), WindowElement(20, 15) {}

void Lock::paint(int x, int y, int width, int height) {
    WindowElement::paint(x, y, width, height);
    if (locked) {
        drawText("     .--------.     ", x, y);
        drawText("    / .------. \\    ", x, y + 1);
        drawText("   / /        \\ \\   ", x, y + 2);
        drawText("   | |        | |   ", x, y + 3);
        drawText("  _| |________`| |_  ", x, y + 4);
        drawText(".' |_|        |_| '.", x, y + 5);
        drawText("'._____ ____ _____.'", x, y + 6);
        drawText("|     .'____'.     |", x, y + 7);
        drawText("'.__.'.'    '.'.__.'", x, y + 8);
        drawText("'.__  |      |  __.'", x, y + 9);
        drawText("|   '.'.____.'.'   |", x, y + 10);
        drawText("'.____'.____.'____.'", x, y + 11);
        drawText("'.________________.'", x, y + 12);

        drawText(lockedMessage, x - (lockedMessage.length() / 2), y + 14);
    }
}
void Lock::setLockedMessage(string message) {
    lockedMessage = message;
}
void Lock::setLocked(bool locked) {
    this->locked = locked;
}