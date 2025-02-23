#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace _24FSI1 {

class String {
private:
    char * str;
    int length;

    int getStringLength(char const * str);
    String static addiere(String const & str1, String const & str2);
    String & plusGleich(String const & str);
    void static memset(String const & str, int start, int length);

public:
    // Konstruktoren und Destruktoren
    // Standardkonstruktor
    String();

    // Erlaub implizierte Typkonvertierungen
    // für String s = "Test";
    // oder String t("Test");
    String(char const * str);

    // Konstruktor baut aus einzelnem Char ein String
    String(char const c);

    // Kopierkonstruktor, stellt sicher, dass die Strings
    // korrekt kopiert werden und es keine Speicherprobleme gibt
    String(String const & str);

    // Destruktor
    ~String();

    // Operatoren
    // Operator=
    void operator=(char const c);
    void operator=(char const * str);
    void operator=(String const & str);

    // Operator+
    String operator+(char c) const;
    String operator+(char const * c) const;
    String operator+(String const & str) const;

    // Operator+=
    String & operator+=(char c);
    String & operator+=(char const * c);
    String & operator+=(String const & str);

    char operator[](int stelle) const;

    // Vergleicher
    bool operator==(String const & z) const;
    bool operator!=(String const & z) const;
    bool operator<(String const & z) const;
    bool operator>(String const & z) const;

    // Methoden

    String toLower() const;
    String toUpper() const;
    // char toChar;

    // Inline-Methoden
    // Rückgabe der Stringlänge
    int Length() {
        return length;
    }

    // Rückgabe als Char-Array
    [[nodiscard]] char * c_str() const {
        return str;
    }

    friend std::ostream & operator<<(std::ostream & os, String const & str);
    friend std::istream & operator>>(std::istream & is, String & str);
};



} // _24FSI1

#endif //STRING_H
