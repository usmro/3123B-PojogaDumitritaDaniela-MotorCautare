#include "SearchEngine.h"
#include "Exceptii.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>

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
        throw FolderNotFoundException("Directorul '" + caleDirector + "' nu a fost gasit sau nu este valid!");
    }

    std::vector<fs::path> fisiere;
    for (const auto& entry : fs::directory_iterator(caleDirector)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            fisiere.push_back(entry.path());
        }
    }

    // Abordare Multi-threaded: impartim fisierele pe fire de executie
    auto indexeazaPartitie = [this](const std::vector<fs::path>& caiFisiere) {
        for (const auto& cale : caiFisiere) {
            std::ifstream f(cale);
            if (f.is_open()) {
                std::stringstream buffer;
                buffer << f.rdbuf();
                Document doc(cale.string(), buffer.str());
                f.close();

                // Zona critica - doar un thread are voie sa scrie in map in acelasi timp
                std::lock_guard<std::mutex> lock(this->indexMutex);
                this->index.adaugaDocument(doc);
            }
        }
        };

    size_t nrThreaduri = std::min((size_t)std::thread::hardware_concurrency(), fisiere.size());
    if (nrThreaduri == 0) nrThreaduri = 1;

    std::vector<std::thread> threaduri;
    size_t dimensiunePartitie = fisiere.size() / nrThreaduri;

    for (size_t i = 0; i < nrThreaduri; ++i) {
        auto inceput = fisiere.begin() + i * dimensiunePartitie;
        auto sfarsit = (i == nrThreaduri - 1) ? fisiere.end() : inceput + dimensiunePartitie;

        std::vector<fs::path> partitie(inceput, sfarsit);
        threaduri.push_back(std::thread(indexeazaPartitie, partitie));
    }

    for (auto& t : threaduri) {
        if (t.joinable()) t.join();
    }
}

std::vector<std::pair<std::string, double>> SearchEngine::cautaComplex(const std::string& interogare, const std::string& mod) {
    if (interogare.empty() || interogare.find_first_not_of(' ') == std::string::npos) {
        throw EmptyQueryException("Interogarea de cautare nu poate fi goala!");
    }

    std::stringstream ss(interogare);
    std::string cuvant;
    std::vector<std::string> cuvinteCautate;
    std::vector<std::set<std::string>> seturiRezultate;

    while (ss >> cuvant) {
        cuvinteCautate.push_back(cuvant);
        seturiRezultate.push_back(index.cautaCuvant(cuvant));
    }

    std::set<std::string> documenteGasite;
    if (!seturiRezultate.empty()) {
        if (mod == "OR" || mod == "or") {
            for (const auto& s : seturiRezultate) {
                documenteGasite.insert(s.begin(), s.end());
            }
        }
        else if (mod == "AND" || mod == "and") {
            documenteGasite = seturiRezultate[0];
            for (size_t i = 1; i < seturiRezultate.size(); ++i) {
                std::set<std::string> intersectie;
                std::set_intersection(documenteGasite.begin(), documenteGasite.end(),
                    seturiRezultate[i].begin(), seturiRezultate[i].end(),
                    std::inserter(intersectie, intersectie.begin()));
                documenteGasite = intersectie;
            }
        }
    }

    // Calculam relevanta totala TF-IDF pentru fiecare document gasit
    std::vector<std::pair<std::string, double>> rezultateOrdonate;
    for (const auto& caleDoc : documenteGasite) {
        double scorTotal = 0.0;
        for (const auto& cuvantCheie : cuvinteCautate) {
            scorTotal += index.getScorTFIDF(cuvantCheie, caleDoc);
        }
        rezultateOrdonate.push_back({ caleDoc, scorTotal });
    }

    // Sortam descrescator dupa scorul de relevanta
    std::sort(rezultateOrdonate.begin(), rezultateOrdonate.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    notifica(interogare, rezultateOrdonate.size());
    return rezultateOrdonate;
}