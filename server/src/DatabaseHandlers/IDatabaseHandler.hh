#pragma once

#include <vector>
#include <pqxx/pqxx>

#include "../ConnectionHandler/ParsedRequest.hh"

struct IDatabaseHandler {
    virtual pqxx::result db_select(const ParsedRequest& request) const = 0;

    virtual ~IDatabaseHandler() {};
};