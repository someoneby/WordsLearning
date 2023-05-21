#pragma once

#include "IRequestHandler.hh"

struct RequestHandler : public IRequestHandler {
    std::string handleRequest(std::string request) override;
};