#ifndef WINDOW_ELEMENT_H
#define WINDOW_ELEMENT_H

#include <string>
#include <iostream>
#include "util.h"
#include "spacer.h"

using namespace std;

class WindowElement {
  public:
    WindowElement(int height, float widthPercent) {
      this->height = height;
      this->widthPercent = widthPercent;
      this->selected = false;
    }

    ~WindowElement() {}

    virtual void paint() {
      cout << "AHHHHH";
    }
    
    void setWidthPercent(double widthPercent) {
      this->widthPercent = widthPercent;
    }

    void setSelected(bool selected) {
      this->selected = selected;
      this->paint();
    }

    void setLocation(int x, int y, int width) {
      this->x = x;
      this->y = y;
      this->width = width;
    }

    void setState(State state) {
      this->state = state;
      this->paint();
    }

    void setHidden(bool hidden) {
      this->hidden = hidden;
      this->paint();
    }

    void addElement(WindowElement* element, int spacer = 0) {
      this->elements.push_back(element);
      if (spacer) {
        this->elements.push_back(new Spacer(spacer));
      }
    }

    WindowElement* getElement(int index) {
      return this->elements[index];
    }

    void removeElement(WindowElement* element) {
      for (int i = 0; i < this->elements.size(); i++) {
        if (this->elements[i] == element) {
          this->elements.erase(this->elements.begin() + i);
          delete element;
          break;
        }
      }
    }
    
    void removeAllElements() {
      for (int i = 0; i < this->elements.size(); i++) {
        delete this->elements[i];
      }
      this->elements.clear();
    }

    double widthPercent;
    double height;
    bool selected;
    bool hidden = false;
    int x = 0, y = 0, width = 0;
    vector<WindowElement*> elements = vector<WindowElement*>();
    State state = DEFAULT;
};

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
  BRIGHT_CYAN = 96,
};

enum State {
  DEFAULT = WHITE,
  DISABLED = DIM,
  SUCCESS = GREEN,
  ERROR = RED,
};

#endif