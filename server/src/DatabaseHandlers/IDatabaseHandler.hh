#pragma once

#include <string>

#include "../ConnectionHandler/ParsedRequest.hh"

struct IDatabaseHandler {
    virtual std::string db_select(const ParsedRequest& request) const = 0;

    virtual ~IDatabaseHandler() {};
};