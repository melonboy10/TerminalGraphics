#ifndef LOCK_H
#define LOCK_H

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

#endif
