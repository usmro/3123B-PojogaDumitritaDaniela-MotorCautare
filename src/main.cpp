#include <iostream>
#include <iomanip>
#include <filesystem>
#include "SearchEngine.h"
#include "Exceptii.h"

// Truc pentru versiunile stricte de g++ de pe Linux
namespace fs = std::filesystem;

// Culori ANSI pentru consola Linux
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

int main() {
    SearchEngine engine;
    auto logger = std::make_shared<Logger>();
    engine.adaugaObservator(logger);

    std::cout << CYAN << "===============================================================\n" << RESET;
    std::cout << GREEN << "    MOTOR AVANSAT DE CĂUTARE TEXT (TF-IDF & MULTI-THREADING)\n" << RESET;
    std::cout << CYAN << "===============================================================\n" << RESET;

    std::string fisierBazaDate = "baza_date.index";
    std::string directorDate = "date";

    try {
        if (fs::exists(fisierBazaDate)) {
            std::cout << BLUE << "[INFO] S-a găsit o bază de date existentă ('" << fisierBazaDate << "'). Se încarcă indexul...\n" << RESET;
            engine.incarcaIndex(fisierBazaDate);
            std::cout << GREEN << "[SUCCES] Baza de date a fost încărcată instant în memorie!\n" << RESET;
        }
        else {
            std::cout << BLUE << "[INFO] Nu există bază de date. Se inițiază indexarea paralelă a folderului '" << directorDate << "'...\n" << RESET;
            engine.incarcaDocumenteDinDirector(directorDate);
            std::cout << BLUE << "[INFO] Se salvează indexul în baza de date locală pentru utilizări viitoare...\n" << RESET;
            engine.salveazaIndex(fisierBazaDate);
            std::cout << GREEN << "[SUCCES] Documente indexate și bază de date creată cu succes!\n" << RESET;
        }
    }
    catch (const std::exception& e) {
        std::cout << RED << "[EROARE CRITICĂ] " << e.what() << "\n" << RESET;
        return 1;
    }
    




    std::string interogare;
    std::string mod;



    while (true) {
        std::cout << "\nIntroduceți cuvintele cheie (sau tipăriți '" << RED << "iesire" << RESET << "'): ";
        std::getline(std::cin, interogare);
        if (interogare == "iesire") break;

        std::cout << "Alegeți modul de căutare (" << YELLOW << "AND / OR" << RESET << "): ";
        std::getline(std::cin, mod);

        try {
            auto rezultate = engine.cautaComplex(interogare, mod);

            if (rezultate.empty()) {
                std::cout << YELLOW << "[REZULTAT] Nu s-au găsit documente relevante.\n" << RESET;
            }
            else {
                std::cout << GREEN << "\n[REZULTAT] S-au găsit " << rezultate.size() << " documente relevante:\n" << RESET;

                // Formatare tabelară "pompiloasă"
                std::cout << CYAN << "---------------------------------------------------------------\n" << RESET;
                std::cout << std::left << std::setw(40) << " CALE DOCUMENT" << " | " << std::setw(15) << "SCOR RELEVANȚĂ (TF-IDF)" << "\n";
                std::cout << CYAN << "---------------------------------------------------------------\n" << RESET;

                for (const auto& p : rezultate) {
                    std::cout << std::left << std::setw(40) << p.first << " | "
                        << YELLOW << std::fixed << std::setprecision(6) << p.second << RESET << "\n";
                }
                std::cout << CYAN << "---------------------------------------------------------------\n" << RESET;
            }
        }
        catch (const EmptyQueryException& e) {
            std::cout << RED << "[AVERTISMENT] " << e.what() << "\n" << RESET;
        }
        catch (const std::exception& e) {
            std::cout << RED << "[EROARE] A intervenit o problemă: " << e.what() << "\n" << RESET;
        }
    }

    std::cout << BLUE << "\nVă mulțumim! Logurile au fost salvate în 'cautari.log'. O zi bună!\n" << RESET;
    return 0;
}