#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include "SearchEngine.h"
#include "Exceptii.h"

namespace fs = std::filesystem;

// Culori ANSI Premium pentru interfață premium
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define BG_BLUE "\033[44m"
#define BG_CYAN "\033[46m"

struct DocumentTehnic {
    std::string numeFisier;
    std::string titluAfisare;
    std::string continut;
};

// Clasa pentru Alerte Automate - Implementare extinsă pentru evenimente live
class SistemAlerteContinut {
private:
    std::set<std::string> cuvinteMonitorizate;
    std::vector<std::string> istoricAlerteDeclansate;
public:
    void aboneazaLaTermen(const std::string& termen) {
        std::string t = termen;
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);
        cuvinteMonitorizate.insert(t);
    }

    void dezaboneazaDeLaTermen(const std::string& termen) {
        std::string t = termen;
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);
        cuvinteMonitorizate.erase(t);
    }

    void verificaDocument(const std::string& numeDoc, const std::string& continut) {
        std::string text = continut;
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);

        for (const auto& termen : cuvinteMonitorizate) {
            if (text.find(termen) != std::string::npos) {
                std::string alerta = "[CRITIC] Termenul '" + termen + "' detectat in " + numeDoc;
                istoricAlerteDeclansate.push_back(alerta);
            }
        }
    }

    void afiseazaStatusEvenimente() {
        if (istoricAlerteDeclansate.empty()) {
            std::cout << GREEN << "  🟢 STATUS SISTEM: Toate circuitele sunt optimizate și stabile.\n" << RESET;
        }
        else {
            std::cout << RED << "  🚨 ALERTE ACTIVE PE SUBSTRATUL TEHNIC:\n" << RESET;
            for (const auto& alerta : istoricAlerteDeclansate) {
                std::cout << "     ⚠️  " << RED << alerta << RESET << "\n";
            }
        }
    }

    void afiseazaTermeniActivi() {
        std::cout << CYAN << "  Urmărire activă senzori: " << RESET;
        if (cuvinteMonitorizate.empty()) {
            std::cout << YELLOW << "Niciunul" << RESET;
        }
        else {
            for (const auto& t : cuvinteMonitorizate) {
                std::cout << "[" << YELLOW << t << RESET << "] ";
            }
        }
        std::cout << "\n";
    }

    void reseteazaIstoric() {
        istoricAlerteDeclansate.clear();
    }
};

std::string genereazaBaraGrafica(double scor, double scorMaxim) {
    if (scorMaxim <= 0 || scor <= 0) return "[                    ]";
    int lungimeMaxBara = 20;
    int caracterePline = static_cast<int>((scor / scorMaxim) * lungimeMaxBara);
    if (caracterePline < 1 && scor > 0) caracterePline = 1;
    if (caracterePline > lungimeMaxBara) caracterePline = lungimeMaxBara;

    std::string bara = "";
    for (int i = 0; i < lungimeMaxBara; ++i) {
        if (i < caracterePline) bara += "█";
        else bara += "░";
    }
    return bara;
}

std::vector<DocumentTehnic> obtineDateInginerie() {
    std::vector<DocumentTehnic> biblioteca;

    biblioteca.push_back({
        "Puntea_Wheatstone_Masurari.txt",
        "Teorie Punte Wheatstone - Circuite de Masura",
        "puntea wheatstone este un circuit electric utilizat pentru masurarea unei rezistente electrice necunoscute "
        "prin echilibrarea a doua brate ale unui circuit in punte. acest circuit are o precizie foarte mare in inginerie electrica. "
        "puntea este formata din patru rezistente conectate sub forma de romb, o sursa de tensiune si un galvanometru care indica "
        "curentul de dezechilibru. cand puntea este echilibrata, curentul prin galvanometru este zero, iar raportul rezistentelor "
        "din bratele adiacente devine egal. masurarea rezistentelor electrice prin aceasta metoda elimina erorile introduse de "
        "tensiunea sursei de alimentare. puntea wheatstone este utilizata intens in senzori de temperatura, senzori de presiune "
        "si punti de masura de inalta precizie pentru rezistenta electrica."
        });

    biblioteca.push_back({
        "Circuit_Integrat_555_Timer.txt",
        "Catalog Tehnic - IC 555 Timer",
        "circuitul integrat 555 este un temporizator utilizat pe scara larga in electronica pentru a genera semnale "
        "de ceas, impulsuri si temporizari precise. timerul 555 poate functiona in mod astabil pentru a genera un semnal "
        "dreptunghiular continuu sau in mod monostabil pentru a genera un single impuls de durata controlata. frecventa "
        "semnalului si factorul de umplere sunt determinate de o retea externa formata din doua rezistente si un condensator. "
        "circuitul integrat contine comparatoare de tensiune interne, un divizor de tensiune rezistiv si un circuit basculant flip-flop. "
        "tensiunea de alimentare poate varia intre 5v si 15v. este o componenta fundamentala pentru circuite de frecventa, "
        "generatoare de impulsuri, scheme de alarma si controlul aprinderii led-urilor."
        });

    biblioteca.push_back({
        "Generator_Tensiune_Liniar_Variabila_GTLV.txt",
        "Analiza Circuit GTLV - Tensiune in Rampa",
        "generatorul de tensiune liniar variabila sau gtlv este un circuit electronic conceput pentru a genera o "
        "tensiune de iesire care creste sau scade liniar in timp, formand un semnal in rampa sau in dintel de fierastrau. "
        "un gtlv real contine un circuit integrator construit in jurul unui amplificator operational, o sursa de curent continuu "
        "si un condensator de incarcare liniara. curentul constant asigura o panta perfect liniara pentru cresterea tensiunii. "
        "descarcarea condensatorului se face rapid printr-un tranzistor de comutatie controlat de un impuls extern. "
        "acest semnal liniar variabil este utilizat in sistemele de baleiaj pentru osciloscoape, convertoare analog-digitale "
        "si circuite de modulatie in durata a impulsurilor pentru controlul tensiunii."
        });

    return biblioteca;
}

void calculeazaStatisticiCuvinte(const std::vector<DocumentTehnic>& biblioteca) {
    std::map<std::string, int> frecventaCuvinte;
    for (const auto& doc : biblioteca) {
        std::stringstream ss(doc.continut);
        std::string cuvant;
        while (ss >> cuvant) {
            cuvant.erase(std::remove_if(cuvant.begin(), cuvant.end(), ::ispunct), cuvant.end());
            std::transform(cuvant.begin(), cuvant.end(), cuvant.begin(), ::tolower);
            if (cuvant.length() > 4) {
                frecventaCuvinte[cuvant]++;
            }
        }
    }

    std::vector<std::pair<std::string, int>> sortat(frecventaCuvinte.begin(), frecventaCuvinte.end());
    std::sort(sortat.begin(), sortat.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    std::cout << MAGENTA << "\n📊 TOP 5 TERMENI TEHNICI IDENTIFICAȚI SEMANTIC ÎN INDEX:\n" << RESET;
    int limita = 0;
    for (const auto& p : sortat) {
        if (limita++ >= 5) break;
        std::cout << "   🔹 " << std::left << std::setw(15) << p.first << " -> Găsit de " << YELLOW << p.second << " ori" << RESET << "\n";
    }
}

void afiseazaDashboard(const SearchEngine& engine, const std::string& fisierDB, SistemAlerteContinut& alerte) {
    std::uintmax_t dimensiuneDB = 0;
    if (fs::exists(fisierDB)) dimensiuneDB = fs::file_size(fisierDB);

    std::cout << CYAN << "\n┌──────────────────────────────────────────────────────────┐\n" << RESET;
    std::cout << CYAN << "│" << RESET << BG_BLUE << "       CORE ENGINE V3: CLUSTER MONITORING SYSTEM          " << RESET << CYAN << "│\n" << RESET;
    std::cout << CYAN << "├──────────────────────────────────────────────────────────┤\n" << RESET;
    std::cout << CYAN << "│" << RESET << "  📄 Documente Analizate Local : " << YELLOW << std::left << std::setw(23) << engine.getNumarTotalDocumente() << CYAN << "│\n" << RESET;
    std::cout << CYAN << "│" << RESET << "  🔤 Indici Unici de Frecvență : " << YELLOW << std::left << std::setw(23) << engine.getNumarCuvinteUnice() << CYAN << "│\n" << RESET;
    std::cout << CYAN << "│" << RESET << "  💾 Dimensiune RAM Stocare    : " << YELLOW << std::left << std::setw(15) << (dimensiuneDB / 1024.0) << " KB        " << CYAN << "│\n" << RESET;
    std::cout << CYAN << "├──────────────────────────────────────────────────────────┤\n" << RESET;
    alerte.afiseazaTermeniActivi();
    std::cout << CYAN << "├──────────────────────────────────────────────────────────┤\n" << RESET;
    alerte.afiseazaStatusEvenimente();
    std::cout << CYAN << "└──────────────────────────────────────────────────────────┘\n" << RESET;
}

int main() {
    SearchEngine engine;
    SistemAlerteContinut sistemAlerte;


    // --- INTEGRARE ȘI ÎNREGISTRARE LOGGER PATTERN OBSERVER ---
    auto logger = std::make_shared<Logger>();
    engine.adaugaObservator(logger);
    // ---------------------------------------------------------
    // 
    // Înregistrăm din oficiu cuvintele cheie sensibile din laboratoare pentru a genera alerte proactive
    sistemAlerte.aboneazaLaTermen("dezechilibru");
    sistemAlerte.aboneazaLaTermen("decalada");

    std::string fisierBazaDate = "baza_date.index";
    std::string directorDate = "date";

    if (!fs::exists(directorDate)) fs::create_directory(directorDate);
    auto bibliotecaTehnica = obtineDateInginerie();

    std::cout << CYAN << "===============================================================\n" << RESET;
    std::cout << GREEN << "    ⚡ INTEL-SEARCH PIPELINE: LOGIC EVENT ALERTS ACTIVE ⚡  \n" << RESET;
    std::cout << CYAN << "===============================================================\n" << RESET;

    // Evaluare inițială și populare istoric evenimente live
    try {
        if (fs::exists(fisierBazaDate)) {
            std::cout << BLUE << "[CACHE] Înregistrare noduri mapate în memoria RAM...\n" << RESET;
            engine.incarcaIndex(fisierBazaDate);
            // Pentru consistența alertelor la pornirea din cache, rulăm o verificare pe fișierele existente
            for (const auto& doc : bibliotecaTehnica) {
                sistemAlerte.verificaDocument(doc.numeFisier, doc.continut);
            }
        }
        else {
            std::cout << YELLOW << "[BUILD] Generare bibliotecă locală și procesare evenimente...\n" << RESET;
            for (const auto& doc : bibliotecaTehnica) {
                std::string caleCompleta = directorDate + "/" + doc.numeFisier;
                std::ofstream f(caleCompleta);
                if (f.is_open()) {
                    f << doc.continut;
                    f.close();
                }
                sistemAlerte.verificaDocument(doc.numeFisier, doc.continut);
            }
            engine.incarcaDocumenteDinDirector(directorDate);
            engine.salveazaIndex(fisierBazaDate);
        }
    }
    catch (const std::exception& e) {
        std::cout << RED << "[EROARE] " << e.what() << "\n" << RESET;
    }

    std::string optiune;
    while (true) {
        afiseazaDashboard(engine, fisierBazaDate, sistemAlerte);

        std::cout << CYAN << "┌────────────────────────────────────────────────┐\n" << RESET;
        std::cout << CYAN << "│" << RESET << BG_CYAN << "                MENIU INTERACTIV                " << RESET << CYAN << "│\n" << RESET;
        std::cout << CYAN << "├────────────────────────────────────────────────┤\n" << RESET;
        std::cout << CYAN << "│" << RESET << "  [" << GREEN << "1" << RESET << "] Căutare Vectorială Termeni (TF-IDF)        " << CYAN << "│\n" << RESET;
        std::cout << CYAN << "│" << RESET << "  [" << GREEN << "2" << RESET << "] Configurare Alerte / Monitorizare Senzori  " << CYAN << "│\n" << RESET;
        std::cout << CYAN << "│" << RESET << "  [" << GREEN << "3" << RESET << "] Analiză Semantică și Frecvențe Cuvinte     " << CYAN << "│\n" << RESET;
        std::cout << CYAN << "│" << RESET << "  [" << GREEN << "4" << RESET << "] Resetare Totală Cluster (Forțare Re-index) " << CYAN << "│\n" << RESET;
        std::cout << CYAN << "│" << RESET << "  [" << RED << "0" << RESET << "] Oprire Subsistem                             " << CYAN << "│\n" << RESET;
        std::cout << CYAN << "└────────────────────────────────────────────────┘\n" << RESET;

        std::cout << "Selectați opțiunea: ";
        std::getline(std::cin, optiune);

        if (optiune == "0") break;

        if (optiune == "1") {
            std::string interogare, mod;
            std::cout << "\n🔍 Termeni: "; std::getline(std::cin, interogare);
            std::cout << "⚖️  Mod Logic (AND/OR): "; std::getline(std::cin, mod);

            try {
                auto rezultate = engine.cautaComplex(interogare, mod);
                if (rezultate.empty()) {
                    std::cout << YELLOW << "\n[REZULTAT] Lipsă corelații în baza tehnică.\n" << RESET;
                }
                else {
                    double scorMaxim = rezultate[0].second;
                    std::cout << CYAN << "╔══════════════════════════════════════════════╦══════════════════════╦══════════════════════╗\n" << RESET;
                    for (const auto& p : rezultate) {
                        std::string cale = p.first.substr(p.first.find("/") + 1);
                        std::replace(cale.begin(), cale.end(), '_', ' ');
                        std::cout << CYAN << "║" << RESET << " " << std::left << std::setw(44) << cale << CYAN << "║ " << RESET
                            << genereazaBaraGrafica(p.second, scorMaxim) << CYAN << "║" << RESET << "  "
                            << YELLOW << p.second << RESET << CYAN << "║\n" << RESET;
                    }
                    std::cout << CYAN << "╚══════════════════════════════════════════════╩══════════════════════╩══════════════════════╝\n" << RESET;
                }
            }
            catch (...) {}
            std::cout << "\nApăsați ENTER..."; std::cin.get();
        }
        else if (optiune == "2") {
            std::cout << "\n🛠️  [SISTEM LIVE DETECTIE - SETARI OBSERVER]\n";
            std::cout << "1. Adaugă termen spre urmărire critică\n";
            std::cout << "2. Elimină termen din sistemul de avertizare\n";
            std::cout << "Alege o acțiune: ";
            std::string subOpt; std::getline(std::cin, subOpt);

            if (subOpt == "1") {
                std::cout << "Introduceți cuvântul cheie monitorizat: ";
                std::string cuv; std::getline(std::cin, cuv);
                sistemAlerte.aboneazaLaTermen(cuv);
                std::cout << GREEN << "[OK] Modulul Observer a înregistrat cuvântul cheie.\n" << RESET;
            }
            else {
                std::cout << "Introduceți cuvântul de eliminat: ";
                std::string cuv; std::getline(std::cin, cuv);
                sistemAlerte.dezaboneazaDeLaTermen(cuv);
                std::cout << YELLOW << "[OK] Termen eliminat din matricea de risc.\n" << RESET;
            }

            // Re-evaluăm automat starea fișierelor pe baza noii liste de monitorizare
            sistemAlerte.reseteazaIstoric();
            for (const auto& doc : bibliotecaTehnica) {
                sistemAlerte.verificaDocument(doc.numeFisier, doc.continut);
            }
            std::cout << "\nApăsați ENTER..."; std::cin.get();
        }
        else if (optiune == "3") {
            calculeazaStatisticiCuvinte(bibliotecaTehnica);
            std::cout << "\nApăsați ENTER pentru a continua..."; std::cin.get();
        }
        else if (optiune == "4") {
            fs::remove(fisierBazaDate);
            for (const auto& entry : fs::directory_iterator(directorDate)) fs::remove(entry.path());
            sistemAlerte.reseteazaIstoric();
            std::cout << GREEN << "[CLEANUP] Toate zonele de memorie cache au fost golite.\nReporniți aplicația pentru recalibrare.\n" << RESET;
            break;
        }
    }
    return 0;
}