#pragma once

#include "../../src/DatabaseHandlers/IDatabaseHandler.hh"

struct DatabaseHandlerMock : public IDatabaseHandler{
    virtual std::string db_select(const ParsedRequest& request) const {
        return "lion;лев;cat;кот;computer;компьютер;table;стол;phone;телефон;screen;экран;";
    }
};