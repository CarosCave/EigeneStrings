#include "Include/String.h"

namespace _24FSI1 {

    // Konstruktoren
    // Legt leeren String an
    String::String() : str(new char[1]), length(0) {
        str[0] = '\0';
    }

    // Legt String an und weisst ihm einen String zu
    String::String(char const * NewStr): length(0) {

        length = getStringLength(NewStr);

        str = new char[length + 1];

        for (int i = 0; i < length; i++) {
            str[i] = NewStr[i];
        }
        str[length] = '\0';
    }

    // Legt String aus einem einzelnen Char an.
    String::String(char const c): str(new char[2]), length(1) {
        str[0] = c;
        str[1] = '\0';
    }

    // Kopierkonstruktor
    String::String(String const & NewStr): length(NewStr.length), str(new char[NewStr.length + 1]) {
        for (int i = 0; i < length; i++) {
            str[i] = NewStr.str[i];
        }
        str[length] = '\0';
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
    void String::operator=(char const * NewStr) {
        delete[] str;
        length = getStringLength(NewStr);
        str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            str[i] = NewStr[i];
        }
        str[length] = '\0';
    }

    // String = String
    void String::operator=(String const & NewStr) {
        length = NewStr.length;
        delete[] str;
        str = new char[length + 1];

        for (int i = 0; i < length; i++) {
            str[i] = NewStr.str[i];
        }
        str[length] = '\0';
    }

    // #endregion Zuweisungsoperator

    // region Operator+
    // Addiere String + Char
    String String::operator+(char const c) const {
        String tStr(c);

        return addiere(*this, tStr);
    }

    // Addiere String + Char[]
    String String::operator+(char const * NewStr) const {
        String tStr(NewStr);

        return addiere(*this, tStr);
    }

    // Addiere String + String
    String String::operator+(String const & NewStr) const {
        return addiere(str, NewStr);
    }

    // endregion Operator+

    // region Operator+=
    // Addiere String += Char
    String & String::operator+=(char const c) {
        // Aufrufen des Konstruktors für ein einzelnes Char
        String tStr { c };

        return plusGleich(tStr);
    }

    // Addiere String += Char-Array
    String & String::operator+=(char const * NewStr) {
        // Aufrufen des Konstruktors für ein Char-Array
        String tStr { NewStr };

        return plusGleich(tStr);
    }

    // Addiere String += String
    String & String::operator+=(String const & NewStr) {
        return plusGleich(NewStr);
    }

    // endregion Operator+=

    // region Private Klassenfunktionen
    // Gibt die Länge des ursprünglichen Char-Arrays zurück
    // Dry-Prinzip (Don't repeat yourself)
    int String::getStringLength(char const * NewStr) {
        int tLength { 0 };
        for (int i = 0; NewStr[i] != '\0'; i++) {
            tLength++;
        }
        return tLength;
    }

    // Eigentliches Addieren ausgelagert.
    // Dry-Prinzip (Don't repeat yourself)
    String String::addiere(String const & NewStr1, String const & NewStr2) {
        String tStr { };

        tStr.length = NewStr1.length + NewStr2.length;
        tStr.str = new char[tStr.length + 1];

        tStr.memZero();

        // Erst wird der erste String in den neuen String übertragen
        for (int i = 0; i < NewStr1.length; i++) {
            tStr.str[i] = NewStr1.str[i];
        }
        // Anschließend wird der zweite String direkt hinten angehangen
        for (int i = 0; i < NewStr2.length; i++) {
            tStr.str[i + NewStr1.length] = NewStr2.str[i];
        }
        tStr.str[tStr.length] = '\0';
        return tStr;
    }

    // Plus Gleich ausgelagert
    // Dry-Prinzip (Don't repeat yourself)
    String & String::plusGleich(String const & NewStr) {
        String temp { };
        temp = addiere(*this, NewStr);

        // Speichern der ursprünglichen Adresse
        char * tPointer = str;

        // Übertragen des neuen Speichers
        str = temp.str;
        length = temp.length;

        // Setze den Temp-String-Zeiger auf tPointer,
        // damit sichergestellt wird, dass der
        // Destruktor die richtige Adresse freigibt.
        temp.str = tPointer;

        return *this;
    }

    // Eigenes MemZero implementiert.
    // Schreibt \0 in den angelegten Speicher
    void String::memZero() const {
        for (int i = 0; i < length + 1; i++) {
            str[i] = '\0';
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
    bool operator==(String const & NewStr1, String const & NewStr2) {
        // Direkter Abbruch, wenn die Länge
        // der Strings unterschiedlich ist.
        if (NewStr1.length != NewStr2.length) {
            return false;
        }

        // Zeichenweiser Vergleich der Strings.
        // Abbruch bei dem ersten unterschiedlichen Zeichen.
        for (int i = 0; i < NewStr1.length; i++) {
            if (NewStr1.str[i] != NewStr2.str[i]) {
                return false;
            }
        }

        // Wenn der Vergleich bis hier gelangt ist,
        // sind beide Strings identisch und
        // es wird TRUE zurückgegeben.
        return true;
    }

    bool operator!=(String const & NewStr1, String const & NewStr2) {
        return !(NewStr1 == NewStr2);
    }

    bool operator<(String const & NewStr1, String const & NewStr2) {
        String s1 = NewStr1.toLower();
        String s2 = NewStr2.toLower();
        int kuerzeresWortLaenge = NewStr1.length < NewStr2.length ? s1.length : s2.length;

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

    bool operator>(String const & NewStr1, String const & NewStr2) {
        String s1 = NewStr1.toLower();
        String s2 = NewStr2.toLower();
        int kuerzeresWortLaenge = NewStr1.length < NewStr2.length ? s1.length : s2.length;

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

    bool operator<=(String const & NewStr1, String const & NewStr2) {
        return !(NewStr1 > NewStr2);
    }

    bool operator>=(String const & NewStr1, String const & NewStr2) {
        return !(NewStr1 < NewStr2);
    }

    // endregion Vergleicher

    // Klassen-Methoden

    // Gibt einen String zurück, der den
    // gegebenen String in Kleinbuchstaben umwandelt.
    String String::toLower() const {
        String temp(*this);

        for (int i = 0; i < length; i++) {
            if (temp.str[i] >= 'A' && temp.str[i] <= 'Z') {
                temp.str[i] = temp.str[i] + ('a' - 'A');
            }
        }

        return temp;
    }

    // Gibt einen String zurück, der den
    // gegebenen String in Großbuchstaben umwandelt.
    String String::toUpper() const {
        String temp {*this};

        for (int i = 0; i < length; i++) {
            if (temp.str[i] >= 'a' && temp.str[i] <= 'z') {
                temp.str[i] = temp.str[i] - ('a' - 'A');
            }
        }

        return temp;
    }

    // Wenn im String eine Integer Zahl gespeichert ist,
    // dann wird diese als Integer ausgegeben.
    int String::toInt() const {
        // Wenn die Stringlänge 0 ist, dann ist es ein leerer String
        // und es ist auf gar keinen Fall eine Zahl gespeichert.
        if (length == 0) {
            return 0;
        }

        int tInt { 0 };
        int tSign { 1 };
        int tPos { 0 };

        // Wenn der erste Zeichen ein Minuszeichen ist
        if (str[0] == '-') {
            tSign = -1;
            tPos = 1;
        }
        // Wenn das erste Zeichen Positiv ist.
        else if (str[tPos] == '+') {
            tPos = 1;
        }

        // Wenn der erste Zeichen kein Minuszeichen oder + ist,
        // aber nur ein Zeichen enthalten ist, gibt 0 zurück
        if (str[0] == '+' || str[0] == '-' && length == 1 ) {
            return 0;
        }

        for (int i = tPos; i < length; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 0;
            }
            tInt = tInt * 10 + str[i] - '0';
        }
        return tInt * tSign;
    }

    // Gibt den String auf der Konsole aus.
    std::ostream & operator<<(std::ostream & os, String const & NewStr) {
        os << NewStr.str;
        return os;
    }

    // Liest von der Konsole ein
    std::istream & operator>>(std::istream & is, String & NewStr) {
        char c;
        int laufvariable {0};
        int laenge {8};

        char * tStr {new char[laenge]};

        // Liest den Eingabestrom bis ungültige Zeichen laut isspace kommen
        while (is.get(c) && !std::isspace(c)) {
            tStr[laufvariable] = c;
            laufvariable++;

            // Wenn die festgelegte Länge des Temp-Strings gleich
            // der Laufvariablen sind, wird ein neues Array doppelter
            // Größe erzeugt und die Daten werden umgeschrieben.
            if (laufvariable == laenge) {
                laenge *= 2;
                char * tTemp {new char[laenge]};
                for (int i = 0; i < laufvariable; i++) {
                    tTemp[i] = tStr[i];
                }
                delete[] tStr;
                tStr = tTemp;
            }
        }
        // Terminieren des fertig eingelesenen Strings
        tStr[laufvariable] = '\0';

        // Übergeben des eingelesenen Strings mittels des
        // überladenen operator=(char const *)
        NewStr = tStr;

        // Freigeben des allokierten Speichers
        delete[] tStr;

        return is;
    }
} // _24FSI1