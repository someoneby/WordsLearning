#pragma once

#include <iostream>

struct IRequestHandler {
    virtual std::string handleRequest(std::string request) = 0;
};