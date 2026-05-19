#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Index.h"
#include "Observer.h"
#include <memory>
#include <mutex>

class SearchEngine {
private:
    Index index;
    std::vector<std::shared_ptr<Observer>> observatori;
    std::mutex indexMutex; // Protejeaza indexul in mediu multi-threaded

    void notifica(const std::string& query, int rezultateGasite);

public:
    void salveazaIndex(const std::string& fisier) { index.salveazaBazaDate(fisier); }
    void incarcaIndex(const std::string& fisier) { index.incarcaBazaDate(fisier); }
    void adaugaObservator(std::shared_ptr<Observer> obs);
    void incarcaDocumenteDinDirector(const std::string& caleDirector);

    // Returneaza lista sortata dupa relevanta TF-IDF
    std::vector<std::pair<std::string, double>> cautaComplex(const std::string& interogare, const std::string& mod);
};

#endif