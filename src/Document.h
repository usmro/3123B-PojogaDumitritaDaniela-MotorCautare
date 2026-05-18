#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
private:
    std::string caleFisier;
    std::string continut;

public:
    Document(const std::string& cale, const std::string& cont);

    // Getteri (Encapsulare)
    std::string getCaleFisier() const;
    std::string getContinut() const;
};

#endif