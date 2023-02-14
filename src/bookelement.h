#ifndef SPELLBOOK_ELEMENT_H
#define SPELLBOOK_ELEMENT_H

#include <iostream>
#include "element.h"
#include "util.h"

using namespace std;

struct Book {
    string title;
    string author;
    int numPages;
    int edition;
};

class SpellbookElement: public WindowElement {
  public:
    SpellbookElement(Book book, float widthPercent = 0.8): WindowElement(2, widthPercent) {
        this->book = book;
    }
    void paint() override {
        for (int i = 1; i < width - 1; i++) {
            drawText("·", x + i, y + 1);
            drawText("·", x + i, y + height - 2);
        }
        
        drawText("╭┬─┤", x, y);
        drawText("╰┴─┤", x, y + height - 1);
        
        drawText("├─┬╮", x + width - 4, y);
        drawText("├─┴╯", x + width - 4, y + height - 1);

        drawText(toCapitalCase(book.title), x + 5, y);
        drawText("By " + toCapitalCase(book.author), x + 5, y + 1);
        drawText("Pages: " + to_string(book.numPages), x + width - 12 - to_string(book.numPages).length(), y);
        drawText("Edition: " + to_string(book.edition), x + width - 14 - to_string(book.edition).length(), y + 1);
    }
  private:
    struct Book book;
    bool showSpells;

};

#endif