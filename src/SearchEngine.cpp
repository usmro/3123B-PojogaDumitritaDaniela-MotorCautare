#include "SearchEngine.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

void SearchEngine::adaugaObservator(std::shared_ptr<Observer> obs) {
    observatori.push_back(obs);
}

void SearchEngine::notifica(const std::string& query, int rezultateGasite) {
    for (auto& obs : observatori) {
        obs->update(query, rezultateGasite);
    }
}

void SearchEngine::incarcaDocumenteDinDirector(const std::string& caleDirector) {
    if (!fs::exists(caleDirector) || !fs::is_directory(caleDirector)) {
        std::cerr << "[Eroare] Directorul nu exista: " << caleDirector << "\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(caleDirector)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream f(entry.path());
            if (f.is_open()) {
                std::stringstream buffer;
                buffer << f.rdbuf();
                Document doc(entry.path().string(), buffer.str());
                index.adaugaDocument(doc);
                f.close();
            }
        }
    }
}

std::set<std::string> SearchEngine::cautaComplex(const std::string& interogare, const std::string& mod) {
    std::stringstream ss(interogare);
    std::string cuvant;
    std::vector<std::set<std::string>> seturiRezultate;

    while (ss >> cuvant) {
        seturiRezultate.push_back(index.cautaCuvant(cuvant));
    }

    std::set<std::string> rezultatFinal;
    if (seturiRezultate.empty()) return rezultatFinal;

    if (mod == "OR" || mod == "or") {
        for (const auto& s : seturiRezultate) {
            rezultatFinal.insert(s.begin(), s.end());
        }
    }
    else if (mod == "AND" || mod == "and") {
        
        rezultatFinal = seturiRezultate[0];
        for (size_t i = 1; i < seturiRezultate.size(); ++i) {
            std::set<std::string> intersectie;
            std::set_intersection(rezultatFinal.begin(), rezultatFinal.end(),
                seturiRezultate[i].begin(), seturiRezultate[i].end(),
                std::inserter(intersectie, intersectie.begin()));
            rezultatFinal = intersectie;
        }
    }

    notifica(interogare, rezultatFinal.size());
    return rezultatFinal;
}