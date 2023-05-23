#pragma once

#include <iostream>
#include "../ConnectionHandler/ParsedRequest.hh"

struct IRequestHandler {
    virtual std::string handleRequest(const ParsedRequest& request) = 0;
};