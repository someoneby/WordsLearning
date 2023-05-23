#pragma once

#include <memory>

#include "IRequestHandler.hh"
#include "../DatabaseHandlers/IDatabaseHandler.hh"

struct WordPair {
    std::string nativeWord;
    std::string translatedWord;
};

struct RequestHandler : public IRequestHandler {
    RequestHandler(std::unique_ptr<IDatabaseHandler> databaseHandler);

    std::string handleRequest(const ParsedRequest& request) override;

private:
    std::vector<WordPair> parseResult(pqxx::result result);

    std::unique_ptr<IDatabaseHandler> m_databaseHandler;
};