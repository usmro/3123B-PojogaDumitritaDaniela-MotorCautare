# Documentație Teoretică - Proiect POO

## Descrierea Arhitecturii și a Funcționalităților Avansate
Aplicația este un motor de căutare bazat pe o structură de **Index Inversat**, optimizat pentru performanță ridicată pe volume mari de text și sortare inteligentă a rezultatelor.

### Concepte POO și Tehnice Aplicate:
1. **Encapsulare:** Atributele claselor (`Document`, `Index`) sunt private și sunt expuse controlat prin metode publice de tip getter.
2. **Moștenire și Polimorfism:** Clasa `Logger` moștenește interfața abstractă `Observer` și suprascrie metoda pur virtuală `update()` pentru a asigura jurnalizarea automată a căutărilor în `cautari.log`.
3. **Șabloane (STL):** S-au utilizat containere standard complexe precum `std::map` pentru structura indexului și `std::set` pentru eliminarea duplicatelor și realizarea operațiilor de intersecție (`AND`) și reuniune (`OR`).
4. **Gestiunea Excepțiilor:** S-au implementat clasele custom `FolderNotFoundException` și `EmptyQueryException` (care moștenesc `std::runtime_error`) pentru a prinde erorile de sistem și interogările goale fără întreruperea aplicației.
5. **Algoritmul TF-IDF (Term Frequency - Inverse Document Frequency):** Rezultatele căutării nu sunt afișate brut, ci sunt sortate descrescător în mod tabelar folosind un scor matematic de relevanță textuală.
6. **Multi-threading (Paralelism):** Încărcarea și parsarea fișierelor din folderul `date` se realizează concurent folosind `std::thread`, partiturile fiind protejate împotriva fenomenului de Race Condition cu ajutorul unui obiect `std::mutex` (`std::lock_guard`).
7. **Persistența Datelor (In-Memory Database Dump/Load):** La prima rulare, starea indexului se serializează pe disc în fișierul `baza_date.index`. La rulările ulterioare, programul încarcă direct acest fișier în memorie, evitând overhead-ul operațiilor I/O pe documentele brute.

## Design Pattern Utilizat
A fost implementat pattern-ul **Observer** pentru monitorizarea decuplată a căutărilor. Clasa `SearchEngine` acționează ca subiect (*Subject*), notificând automat obiectul de tip `Logger` la fiecare interogare trimisă de utilizator.