#include "element.h"
#include "lock.h"

using namespace std;

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
