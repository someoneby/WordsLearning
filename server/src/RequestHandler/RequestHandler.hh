#pragma once

#include <memory>
#include <set>

#include "IRequestHandler.hh"
#include "../DatabaseHandlers/IDatabaseHandler.hh"

struct WordPair {
    std::string nativeWord;
    std::string translatedWord;
};

struct RequestHandler : public IRequestHandler {
    RequestHandler(std::unique_ptr<IDatabaseHandler> databaseHandler);

    std::string handleRequest(const ParsedRequest& request) const override;

private:
    std::vector<WordPair> parseResult(std::string result) const;
    void mixResult(std::vector<WordPair>& pairs) const;
    std::string makeAnswer(const std::vector<WordPair>& pairs) const;
    std::set<int64_t> takeUniqueRandomSet(int64_t maxValue, std::set<int64_t> exclude, int64_t howMany = 1) const;

    std::unique_ptr<IDatabaseHandler> m_databaseHandler;
};