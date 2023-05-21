#pragma once

#include "../../src/RequestHandler/IRequestHandler.hh"

struct RequestHandlerEchoMock : public IRequestHandler {
    std::string handleRequest(std::string request) override;
};