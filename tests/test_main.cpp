#include <iostream>
#include <cassert>
#include "../src/Document.h"
#include "../src/Index.h"

void testIndexareSimpla() {
    Document doc("doc_test.txt", "programare obiecte");
    Index index;
    index.adaugaDocument(doc);

    // Verificăm dacă găsește cuvântul indexat
    auto rez1 = index.cautaCuvant("programare");
    assert(rez1.size() == 1);
    assert(*rez1.begin() == "doc_test.txt");

    // Verificăm că ignoră corect stop-words (cum ar fi "si")
    auto rez2 = index.cautaCuvant("si");
    assert(rez2.empty());

    std::cout << "[OK] Test Indexare Simpla trecut!\n";
}

int main() {
    std::cout << "=== RULARE TESTE UNITARE ===\n";
    testIndexareSimpla();
    std::cout << "=== TOATE TESTELE AU TRECUT CU SUCCES ===\n";
    return 0;
}