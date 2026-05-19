# 🔍 Motor Avansat de Căutare pentru Documente Text (POO)

Proiect academic complex realizat pentru disciplina **Proiectare Orientată pe Obiecte**. Aplicația este un motor de căutare de tip *Inverted Index*, optimizat pentru performanță ridicată pe medii **Linux (g++)** prin utilizarea paralelismului și a structurilor de date eficiente din STL.

---

## 🚀 Caracteristici și Funcționalități Complete

Aplicația depășește nivelul unui proiect de bază, integrând concepte avansate de inginerie software și optimizare:

### 1. Algoritm de Relevanță Matematică (TF-IDF)
În loc de o afișare liniară, rezultatele sunt sortate descrescător în funcție de importanța cuvântului în text:
* **TF (Term Frequency):** Calculează densitatea cuvântului în documentul curent.
* **IDF (Inverse Document Frequency):** Penalizează cuvintele comune și oferă o pondere mai mare cuvintelor rare și specifice în întreaga bază de date.

### 2. Indexare Paralelă (Multi-threading)
* Scanarea și parsarea documentelor brute din folderul `date/` se realizează concurent folosind fire de execuție (`std::thread`).
* Partajarea indexului global este securizată la nivel de memorie folosind mecanisme de sincronizare (`std::mutex` și `std::lock_guard`) pentru a preveni fenomenele de *Race Condition*.

### 3. Persistența Datelor (In-Memory Database Dump/Load)
* **Prima rulare:** Aplicația indexează fișierele text și serializează (salvează) structura optimizată pe disc în fișierul `baza_date.index`.
* **Rulările ulterioare:** Evită complet overhead-ul de I/O de a reciti documentele brute. Încarcă direct indexul de pe disc în RAM în mai puțin de o milisecundă.

### 4. Procesare Text și Filtrare (NLP de bază)
* Curățare automată a semnele de punctuație și normalizare în litere mici (*case-insensitivity*).
* Filtrare prin listă de *Stop-Words* (elimină automat cuvintele de legătură nesemnificative precum: *si, in, la, cu, o, pe, ca, the, is*).

### 5. Gestiune Robustă a Excepțiilor & Observer Pattern
* Implementare de ierarhii proprii de excepții (`FolderNotFoundException`, `EmptyQueryException`) pentru a preveni crash-ul aplicației la input eronat.
* Jurnalizare decuplată (Design Pattern **Observer**): un modul `Logger` monitorizează căutările și salvează automat istoricul în `cautari.log`.

---

## 📂 Structura Proiectului

| Director / Fișier | Rol în cadrul aplicației |
| :--- | :--- |
| `src/` | Conține codul sursă C++ (clasele `Document`, `Index`, `SearchEngine`, `Observer`, `Exceptii`) |
| `tests/` | Suita de teste unitare automate pentru validarea logicii de indexare |
| `date/` | Baza de date text (folderul unde se plasează documentele reale `.txt`) |
| `docs/` | Documentația teoretică detaliată cu conceptele POO explicate |
| `Makefile` | Scriptul de automatizare a compilării și testării pentru Linux |
| `baza_date.index` | Fișierul generat ce conține indexul inversat salvat persistent |
| `cautari.log` | Fișierul de jurnalizare generat automat de către Logger |

---

## 🛠️ Instrucțiuni de Build și Rulare (Consolă Linux / WSL)

### 1. Compilarea și Lansarea Aplicației Interactive
Pentru a curăța build-urile vechi, a compila noul cod și a porni motorul de căutare cu interfață ANSI colorată:
```bash
make clean
make
./app