#include "Include/String.h"

namespace _24FSI1 {

    // Konstruktoren
    // Legt leeren String an
    String::String() : str(new char[1]), length(0) {
        str[0] = '\0';
    }

    // Legt String an und weisst ihm einen String zu
    String::String(char const * str): length(0) {

        for (int i = 0; str[i] != '\0'; i++) {
            length++;
        }
        this->str = new char[length + 1];

        for (int i = 0; i <= length; i++) {
            this->str[i] = str[i];
        }
        this->str[length] = '\0';
    }

    // Operatoren
    void String::operator=(char const * str) {
        length = getStringLength(str);
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            this->str[i] = str[i];
        }
        this->str[length] = '\0';
    }

    // Addiere String + Char
    String String::operator+(char const c) const {
        String tStr;
        tStr.str[0] = c;

        return addiere(str, tStr.str);
    }

    // Addiere String + Char[]
    String String::operator+(char const & c) const {
        // String tStr(str);
        //
        // tStr.length = this->length + getStringLength(str);
        //
        // tStr.str = new char[tStr.length + 1];
        // //delete[] tStr.str;
        // // Erst wird der erste String in den neuen String übertragen
        // for (int i = 0; i <length; i++) {
        //     tStr.str[i] = this->str[i];
        // }
        // // Anschließend wird der zweite String direkt hinten angehangen
        // for (int i = length; i < tStr.length; i++) {
        //     tStr.str[i] = str[i - length];
        // }
        // tStr.str[tStr.length] = '\0';


        return addiere(this->str, str);
    }

    String String::addiere(String const & str1, String const & str2) const {
        String tStr;
        tStr.length = str1.length + str2.length;
        tStr.str = new char[tStr.length + 1];
        // Erst wird der erste String in den neuen String übertragen
        for (int i = 0; i <length; i++) {
            tStr.str[i] = this->str[i];
        }
        // Anschließend wird der zweite String direkt hinten angehangen
        for (int i = length; i < tStr.length; i++) {
            tStr.str[i] = str[i - length];
        }
        tStr.str[tStr.length] = '\0';
        return tStr;
    }

    String String::operator+(String const & str) const {
        String tStr;
    }

    // Gibt die Länge des ursprünglichen Char-Arrays zurück
    int String::getStringLength(char const * str) {
        int tLength = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            tLength++;
        }
        return tLength;
    }

    char String::operator[](int const stelle) {
        if (stelle >= 0 && stelle <= length) {
            return str[stelle];
        }
        else {
            std::__throw_length_error("Index out of range.");
        }
    }

    bool String::operator==(String const & z) const{
        // Direkter Abbruch, wenn die Länge
        // der Strings unterschiedlich ist.
        if (length != z.length) {
            return false;
        }

        // Zeichenweiser Vergleich der Strings.
        // Abbruch bei dem ersten unterschiedlichen Zeichen.
        for (int i = 0; i < length; i++) {
            if (str[i] != z.str[i]) {
                return false;
            }
        }

        // Wenn der Vergleich bis hier gelangt ist,
        // sind beide Strings identisch und
        // es wird TRUE zurückgegeben.
        return true;
    }

    bool String::operator<(String const & z) const {
        String s1 = toLower();
        String s2 = z.toLower();
        int kuerzeresWortLaenge = length < z.length ? s1.length : s2.length;

        for (int i = 0; i < kuerzeresWortLaenge; i++) {
            if (s1.str[i] < s2.str[i]) {
                return true;
            } else if (s1.str[i] > s2.str[i]) {
                return false;
            }
        }

        // Wenn alle verglichenen Zeichen gleich sind,
        // entscheidet die Länge des Strings.
        return s1.length < s2.length;
    }

    bool String::operator>(String const & z) const {
        String s1 = toLower();
        String s2 = z.toLower();
        int kuerzeresWortLaenge = length < z.length ? s1.length : s2.length;

        for (int i = 0; i < kuerzeresWortLaenge; i++) {
            if (s1.str[i] > s2.str[i]) {
                return true;
            } else if (s1.str[i] < s2.str[i]) {
                return false;
            }
        }

        // Wenn alle verglichenen Zeichen gleich sind,
        // entscheidet die Länge des Strings.
        return s1.length > s2.length;
    }


    // Klassen-Methoden

    // Gibt einen String zurück, der den
    // gegebenen String in Kleinbuchstaben umwandelt.
    String String::toLower() const {
        String temp;
        temp.length = length;
        delete[] temp.str;
        temp.str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                temp.str[i] = str[i] + 32;
            }
            else {
                temp.str[i] = str[i];
            }
        }
        temp.str[length] = '\0';
        return temp;
    }

    // Gibt einen String zurück, der den
    // gegebenen String in Großbuchstaben umwandelt.
    String String::toUpper() const {
        String temp;
        delete[] temp.str;
        temp.str = new char[length + 1];
        temp.length = length;

        for (int i = 0; i < length; i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                temp.str[i] = str[i] - 32;
            }
            else {
                temp.str[i] = str[i];
            }
        }
        temp.str[length] = '\0';
        return temp;
    }

    // Gibt den String auf der Konsole aus.
    std::ostream & operator<<(std::ostream & os, String const & str) {
        os << str.str;
        return os;
    }

} // _24FSI1

// Löschen
// std::ostream & operator<<(std::ostream & os, String const & z) {
//     z.printOn(os);
//     return os;
// }

// void String::printOn(std::ostream & os) const {
//     os << str;
// }

// Copy-Konstruktor
// String::String(String const & z){
//     length = z.length;
//     str = z.str;
// }

// Destruktor, löscht die Daten und gibt den Speicher wieder frei.
// String::~String() {
//     delete[] str;
// }