# TerminalGraphics
This is a graphics library in C++, designed to provide an easy-to-use interface for creating and manipulating graphical elements.

### File Structure
```
include/
    include.h
src/
    layouts
        layout.h
        grid.h
        column.h
        row.h
        horizontal.h
        vertical.h
    bookelement.h
    element.h
    group.h
    spacer.h
    terminal.h
    util.h
    window.h
    button.h
    lock.h
Makefile
```
include/
This directory contains the header file include.h, which includes all the necessary headers for using the library.

layouts/
This directory contains the layout headers, which are used to arrange graphical elements in specific ways. The available layout headers are:

- layout.h: A base class for all layouts.
- grid.h: A grid layout, which arranges elements in a two-dimensional grid.
- column.h: A column layout, which arranges elements vertically.
- row.h: A row layout, which arranges elements horizontally.
- horizontal.h: A horizontal layout, which arranges elements from left to right.
- vertical.h: A vertical layout, which arranges elements from top to bottom.
- bookelement.h: This file contains the declaration of the BookElement class, which represents an element that can be added to a layout.

### Makefile
The Makefile is used to build the library. Simply run make to build the library.
