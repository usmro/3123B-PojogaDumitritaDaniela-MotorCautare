#include "Document.h"

Document::Document(const std::string& cale, const std::string& cont)
    : caleFisier(cale), continut(cont) {
}

std::string Document::getCaleFisier() const { return caleFisier; }
std::string Document::getContinut() const { return continut; }