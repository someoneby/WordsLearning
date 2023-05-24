#pragma once

#include <string>
#include <vector>

struct ParsedRequest {
    std::string nativeLanguage = "";
    std::string learningLanguage = "";
    std::vector<std::string> themes{};

    bool isValid() const { return !nativeLanguage.empty() && !learningLanguage.empty() && !themes.empty(); }
};