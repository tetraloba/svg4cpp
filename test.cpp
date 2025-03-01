#include <iostream>
#include "svg.hpp"
using namespace std;

int main() {
    svg s("test.svg", {0, 0}, {1920, 1080}, "px");
    cout << s.default_fill.str() << endl;
    s.rect({40, 80}, {90, 100}, {150, 25, 30});
    return 0;
}
