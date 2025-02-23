#include "Include/String.h"

namespace _24FSI1 {

    // Konstruktoren
    // Legt leeren String an
    String::String() : str(new char[1]), length(0) {
        str[0] = '\0';
    }

    // Legt String an und weisst ihm einen String zu
    String::String(char const * str): length(0) {

        length = getStringLength(str);

        this->str = new char[length + 1];

        for (int i = 0; i < length; i++) {
            this->str[i] = str[i];
        }
        this->str[length] = '\0';
    }

    // Legt String aus einem einzelnen Char an.
    String::String(char const c): str(new char[2]), length(1) {
        //delete[] str;
        //str = nullptr;
        //operator=(c);
        str[0] = c;
        str[1] = '\0';
    }

    // Kopierkonstruktor
    String::String(String const & str): length(str.length), str(new char[str.length + 1]) {
        for (int i = 0; i < length; i++) {
            this->str[i] = str.str[i];
        }
        this->str[length] = '\0';
    }

    // Destruktor, löscht die Daten und gibt den Speicher wieder frei.
    // Da ich mit new Speicher alloziiere, muss ich
    // zwingend den Heap mit delete[] zurückgeben.
    String::~String() {
        delete[] str;
    }

    // Operatoren
    // #region Zuweisungsoperator
    // String = Char
    void String::operator=(char const c) {
        if (str != nullptr) {
            delete[] str;
        }
        str = new char[2];
        str[0] = c;
        length = 1;
        str[1] = '\0';
    }

    // String = Char-Array
    void String::operator=(char const * str) {
        delete[] this->str;
        length = getStringLength(str);
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            this->str[i] = str[i];
        }
        this->str[length] = '\0';
    }

    // String = String
    void String::operator=(String const & str) {
        length = str.length;
        delete[] this->str;
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            this->str[i] = str.str[i];
        }
        this->str[length] = '\0';
    }

    // #endregion Zuweisungsoperator

    // region Operator+
    // Addiere String + Char
    String String::operator+(char const c) const {
        String tStr(c);

        return addiere(this->str, tStr);
    }

    // Addiere String + Char[]
    String String::operator+(char const * c) const {
        String tStr(c);

        return addiere(this->str, tStr);
    }

    // Addiere String + String
    String String::operator+(String const & str) const {
        return addiere(this->str, str);
    }

    // endregion Operator+

    // region Operator+=
    // Addiere String += Char
    String & String::operator+=(char const c) {
        // Aufrufen des Konstruktors für ein einzelnes Char
        String tStr(c);

        return plusGleich(tStr);
    }

    // Addiere String += Char-Array
    String & String::operator+=(char const * c) {
        // Aufrufen des Konstruktors für ein Char-Array
        String tStr(c);

        return plusGleich(tStr);
    }

    // Addiere String += String
    String & String::operator+=(String const & str) {
        return plusGleich(str);
    }

    // endregion Operator+=

    // region Private Klassenfunktionen
    // Gibt die Länge des ursprünglichen Char-Arrays zurück
    // Dry-Prinzip (Don't repeat yourself)
    int String::getStringLength(char const * str) {
        int tLength = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            tLength++;
        }
        return tLength;
    }

    // Eigentliches Addieren ausgelagert.
    // Dry-Prinzip (Don't repeat yourself)
    String String::addiere(String const & str1, String const & str2) {
        String tStr;

        tStr.length = str1.length + str2.length;
        tStr.str = new char[tStr.length + 1];

        memset(tStr, 0, tStr.length + 1);

        // Erst wird der erste String in den neuen String übertragen
        for (int i = 0; i < str1.length; i++) {
            tStr.str[i] = str1.str[i];
        }
        // Anschließend wird der zweite String direkt hinten angehangen
        for (int i = 0; i < str2.length; i++) {
            tStr.str[i + str1.length] = str2.str[i];
        }
        tStr.str[tStr.length] = '\0';
        return tStr;
    }

    // Plus Gleich ausgelagert
    // Dry-Prinzip (Don't repeat yourself)
    String & String::plusGleich(String const & str) {
        String temp;
        temp = addiere(this->str, str);
        // Löschen des Speichers
        //delete[] this->str;
        // Übertragen des neuen Speichers
        this->str = temp.str;
        this->length = temp.length;

        // Setze den Temp-String auf NULL,
        // damit sichergestellt wird, dass der
        // Destruktor nicht versucht erneut freizugeben.
        temp.str = nullptr;
        temp.length = 0;

        return *this;
    }

    // Eigenes Memset implementiert.
    // Schreibt \0 in den angelegten Speicher
    void String::memset(String const & newStr, int start, int length) {
        for (int i = start; i < length + start; i++) {
            newStr.str[i] = '\0';
        }
    }

    // endregion Private Klassenfunktionen

    char String::operator[](int const stelle) const {
        if (stelle >= 0 && stelle <= length) {
            return str[stelle];
        }
        else {
            std::__throw_length_error("Index out of range.");
        }
    }

    // region Vergleicher
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

    bool String::operator!=(String const & z) const {
        return !(*this == z);
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
    // endregion Vergleicher

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

    // Liest von der Konsole ein
    std::istream & operator>>(std::istream & os, String & str) {
        return os;
    }
} // _24FSI1