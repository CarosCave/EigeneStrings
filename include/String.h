#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace _24FSI1 {

class String {
private:
    char * str;
    int length;

    int getStringLength(char const * NewStr);
    String static addiere(String const & NewStr1, String const & NewStr2);
    String & plusGleich(String const & NewStr);
    void memZero() const;

public:
    // Konstruktoren und Destruktoren
    // Standardkonstruktor
    String();

    // Erlaub implizierte Typkonvertierungen
    // für String s = "Test";
    // oder String t("Test");
    String(char const * NewStr);

    // Konstruktor baut aus einzelnem Char ein String
    String(char const c);

    // Kopierkonstruktor, stellt sicher, dass die Strings
    // korrekt kopiert werden und es keine Speicherprobleme gibt
    String(String const & NewStr);

    // Destruktor
    ~String();

    // Operatoren
    // Operator=
    void operator=(char const c);
    void operator=(char const * NewStr);
    void operator=(String const & NewStr);

    // Operator+
    String operator+(char c) const;
    String operator+(char const * NewStr) const;
    String operator+(String const & NewStr) const;

    // Operator+=
    String & operator+=(char c);
    String & operator+=(char const * NewStr);
    String & operator+=(String const & NewStr);

    char operator[](int stelle) const;

    // Vergleicher Friends damit der symetrische Verleich möglich ist
    friend bool operator==(String const & NewStr1, String const & NewStr2);
    friend bool operator!=(String const & NewStr1, String const & NewStr2);
    friend bool operator<(String const & NewStr1, String const & NewStr2);
    friend bool operator>(String const & NewStr1, String const & NewStr2);
    friend bool operator<=(String const & NewStr1, String const & NewStr2);
    friend bool operator>=(String const & NewStr1, String const & NewStr2);

    // Methoden

    String toLower() const;
    String toUpper() const;
    int toInt() const;

    // Inline-Methoden
    // Rückgabe der Stringlänge
    int Length() {
        return length;
    }

    // Rückgabe als Char-Array
    [[nodiscard]] char * c_str() const {
        return str;
    }

    friend std::ostream & operator<<(std::ostream & os, String const & NewStr);
    friend std::istream & operator>>(std::istream & is, String & NewStr);
};

} // _24FSI1

#endif //STRING_H
