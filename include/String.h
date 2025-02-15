#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace _24FSI1 {

class String {
private:
    char * str;
    int length;

    int static getStringLength(char const * str);
    [[nodiscard]] String addiere(String const & str1, String const & str2) const;
    String & plusGleich(String const & str);


public:
    // Konstruktoren und Destruktoren
    String();
    // Standardkonstruktor
    // Erlaub implizierte Typkonvertierungen
    // für String s = "Test";
    // oder String t("Test");
    String(char const * str);

    // Konstruktor baut aus einzelnem Char ein String
    String(char const c);

    ~String();

    // Operatoren
    void operator=(char const * str);

    // Operator+
    String operator+(char c) const;
    String operator+(char const * c) const;
    String operator+(String const & str) const;

    // Operator+=
    String & operator+=(char c);
    String & operator+=(char const * c);
    String & operator+=(String const & str);

    // void operator<<();
    // void operator>>();
    char operator[](int stelle) const;

    // Vergleicher
    bool operator==(String const & z) const;
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

    friend std::ostream & operator<<(std::ostream & os, String const & str);
    friend std::istream & operator>>(std::istream & is, String & str);
};



} // _24FSI1

#endif //STRING_H
