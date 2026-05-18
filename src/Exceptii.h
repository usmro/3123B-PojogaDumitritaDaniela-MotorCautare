#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

// Excepție pentru directoare sau fișiere inexistente
class FolderNotFoundException : public std::runtime_error {
public:
    FolderNotFoundException(const std::string& mesaj) : std::runtime_error(mesaj) {}
};

// Excepție pentru interogări invalide sau goale
class EmptyQueryException : public std::runtime_error {
public:
    EmptyQueryException(const std::string& mesaj) : std::runtime_error(mesaj) {}
};

#endif
