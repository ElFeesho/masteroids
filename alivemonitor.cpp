#include <iostream>
#include "alivemonitor.h"

AlwaysAlive::AlwaysAlive() {
    std::cout << "AlwaysAlive" << std::endl;
}

AlwaysAlive::~AlwaysAlive() {
    std::cout << "~AlwaysAlive" << std::endl;
}

bool AlwaysAlive::alive() const {
    return true;
}