#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include "Document.h"

class Index {
private:
    // map: cuvânt -> set de căi de fișiere (set-ul elimină duplicatele automat)
    std::map<std::string, std::set<std::string>> indexInversat;
    std::set<std::string> stopWords;

    std::string proceseazaCuvant(std::string cuvant);
    void incarcaStopWords();

public:
    Index();
    void adaugaDocument(const Document& doc);
    std::set<std::string> cautaCuvant(const std::string& cuvant);
};

#endif