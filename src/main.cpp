#include <iostream>

#include "Image.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Image image = Image(4,3);
    image.pixel();
    return 0;
}
