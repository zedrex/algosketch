#pragma once

#include <iostream>

void debug(const std::string &message)
{
    std::cout << "DEBUG: " << message << std::endl;
}