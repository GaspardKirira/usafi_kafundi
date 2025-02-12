#include <tensorflow/c/c_api.h>
#include <iostream>

void print_version() {
    std::cout << "TensorFlow version: " << TF_Version() << std::endl;
}

int main() {
    print_version();
    return 0;
}
