#pragma once

#include <string>

#include "../ConnectionHandler/ParsedRequest.hh"

struct IRequestHandler {
    virtual std::string handleRequest(const ParsedRequest& request) const = 0;
};