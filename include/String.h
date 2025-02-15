#ifndef STRING_H
#define STRING_H
#include <iostream>

namespace _24FSI1 {

class String {
private:
    char * str;
    int length;

    int static getStringLength(char const * str);
    String addiere(String const & str1, String const & str2) const;

public:
    // Konstruktoren und Destruktoren
    String();
    // Standardkonstruktor
    /// Erlaub implizierte Typkonvertierungen
    /// für String s = "Test";
    /// oder String t("Test");
    ///
    String(char const * str);
    //String(char const * str);
    // String(String const &);
    //~String();

    // Operatoren
    void operator=(char const * str);
    String operator+(char const str) const;
    String operator+(char const & c) const;
    String operator+(String const & str) const;
    // void operator+=();

    // void operator<<();
    // void operator>>();
    char operator[](int const stelle);

    bool operator==(String const & z) const;
    bool operator<(String const & z) const;
    bool operator>(String const & z) const;

    // Methoden

    void printOn(std::ostream & os) const;
    String toLower() const;
    String toUpper() const;
    // char toChar;

    // Inline-Methoden
    // Rückgabe der Stringlänge
    int Length() {
        return length;
    }

    friend std::ostream & operator<<(std::ostream & os, String const & str);
};



} // _24FSI1

#endif //STRING_H
