#include <iostream>

using namespace std;

enum Let {
    A,
    B,
    C
};

class Group {
  public:
    Group(string = "");
};

Group::Group(string title) {}