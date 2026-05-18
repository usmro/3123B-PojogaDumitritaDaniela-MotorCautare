#include <iostream>
#include "Document.h"
#include "Index.h"

int main() {
    std::cout << "--- Motor de Cautare Documente Text (Proiect POO) ---\n";

    // Test?m rapid structura de baze
    Document doc1("test1.txt", "Salutare! Acesta este un proiect pentru disciplina POO.");
    Document doc2("test2.txt", "Programarea orientata pe obiecte este interesanta si utila.");

    Index index;
    index.adaugaDocument(doc1);
    index.adaugaDocument(doc2);

    std::cout << "Cautam cuvantul 'proiect':\n";
    auto rezultate = index.cautaCuvant("proiect");

    for (const auto& cale : rezultate) {
        std::cout << "Gasit in: " << cale << "\n";
    }

    return 0;
}