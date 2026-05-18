#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Index.h"
#include "Observer.h"
#include <memory>

class SearchEngine {
private:
    Index index;
    std::vector<std::shared_ptr<Observer>> observatori;

    void notifica(const std::string& query, int rezultateGasite);

public:
    void adaugaObservator(std::shared_ptr<Observer> obs);
    void incarcaDocumenteDinDirector(const std::string& caleDirector);

    // Cautare simpla si avansata (AND / OR)
    std::set<std::string> cautaComplex(const std::string& interogare, const std::string& mod);
};

#endif