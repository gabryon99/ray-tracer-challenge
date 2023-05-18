#include <iostream>

#include "canvas.hpp"

int main() {

    Canvas canvas(5, 3);
    std::cout << canvas.ppm();

    return 0;
}
