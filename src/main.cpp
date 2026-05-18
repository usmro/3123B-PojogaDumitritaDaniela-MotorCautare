#include <iostream>
#include "SearchEngine.h"

int main() {
    SearchEngine engine;

    // Inregistram Logger-ul (Observer)
    auto logger = std::make_shared<Logger>();
    engine.adaugaObservator(logger);

    std::cout << "==================================================\n";
    std::cout << "   MOTOR DE CAUTARE DOCUMENT TEXT (POO) \n";
    std::cout << "==================================================\n";

    // Incarcam documentele dintr-un folder numit "date"
    // Poti crea un folder "date" in proiect si sa pui 2-3 fisiere .txt in el
    std::string directorDate = "date";
    std::cout << "[Info] Se incarca documentele din folderul '" << directorDate << "'...\n";
    engine.incarcaDocumenteDinDirector(directorDate);

    std::string interogare;
    std::string mod;

    while (true) {
        std::cout << "\nIntroduceti cuvintele de cautat (sau 'iesire'): ";
        std::getline(std::cin, interogare);
        if (interogare == "iesire") break;

        std::cout << "Alegeti modul de cautare (AND / OR): ";
        std::getline(std::cin, mod);

        auto rezultate = engine.cautaComplex(interogare, mod);

        if (rezultate.empty()) {
            std::cout << "[Rezultat] Nu s-au gasit documente.\n";
        }
        else {
            std::cout << "[Rezultat] Cuvintele apar in:\n";
            for (const auto& doc : rezultate) {
                std::cout << " -> " << doc << "\n";
            }
        }
    }

    std::cout << "\nProgram finalizat cu succes. Logurile au fost salvate in 'cautari.log'.\n";
    return 0;
}