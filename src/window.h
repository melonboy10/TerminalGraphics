#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <tuple>
#include <vector>
#include <string>
#include "element.h"

using namespace std;

class Group: public WindowElement {
  public:
    Group(string = "");
    void setTitle(string);

  private:
    static struct winsize w;
    static void updateWinSize();
    static void paintAll();
    void paint();
    void drawBorder();

    bool hidden, borderHidden;
    int width, index;
    string title;
};

#endif