#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Interfata Observer (Polimorfism pur)
class Observer {
public:
    virtual void update(const std::string& query, int rezultateGasite) = 0;
    virtual ~Observer() = default;
};

// Implementarea concreta: Logger (Salveaza intr-un fisier text pe Linux)
class Logger : public Observer {
private:
    std::string fisierLog;
public:
    Logger(const std::string& caleLog = "cautari.log") : fisierLog(caleLog) {}

    void update(const std::string& query, int rezultateGasite) override {
        std::ofstream f(fisierLog, std::ios::app);
        if (f.is_open()) {
            f << "[LOG] S-a cautat: \"" << query << "\" | Rezultate gasite: " << rezultateGasite << "\n";
            f.close();
        }
    }
};

#endif