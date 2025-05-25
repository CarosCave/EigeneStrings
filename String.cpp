#include "include/String.h"

namespace FSI1 {

    // Konstruktoren
    // Legt einen leeren String an und terminiert ihn.
    String::String() : m_str(new char[1] { '\0'} ), m_length(0) {
    }

    // Legt String an und weist ihm einen String zu
    String::String(char const * const NewStr): m_length(0) {
        m_length = get_string_length(NewStr);
        m_str = new char[m_length + 1];

        copy_string(NewStr, m_str, m_length);
    }

    // Legt String aus einem einzelnen Char an.
    String::String(char const c): m_str{ new char[2] {c, '\n'} }, m_length(1) {
    }

    // Kopierkonstruktor
    String::String(String const & NewStr): m_str(new char[NewStr.m_length + 1]), m_length(NewStr.m_length) {
        copy_string(NewStr.m_str, m_str, m_length);
    }

    // Destruktor, löscht die Daten und gibt den Speicher wieder frei.
    // Da ich mit new Speicher alloziere, muss ich
    // zwingend den Heap mit delete[] zurückgeben.
    String::~String() {
        delete[] m_str;
    }

    // Operatoren
    // ----------- Zuweisungsoperator -----------
    // String = String
    String & String::operator=(String const & NewStr) {
        m_length = NewStr.m_length;
        delete[] m_str;
        m_str = new char[m_length + 1];

        for (size_t i = 0; i < m_length; i++) {
            m_str[i] = NewStr.m_str[i];
        }
        m_str[m_length] = '\0';
        return *this;
    }

    // ----------- Zuweisungsoperator -----------

    // ----------- Operator+ -----------
    String String::operator+(String const & NewStr) const {
        return add( String{ m_str }, NewStr);
    }

    // ----------- Operator+ -----------

    // ----------- Operator+= -----------
    String & String::operator+=(String const & NewStr) {
        return add_equal(NewStr);
    }

    // ----------- Operator+= -----------

    // ----------- Private Klassenfunktionen -----------
    // internes Kopieren eines Strings
    void String::copy_string(char const * const origin, char * destination, std::size_t const length) {
        // Durch das i ≤ length + 1 wird auch der Terminator \0 mit kopiert
        for (std::size_t i = 0; i <= length ; i++) {
            destination[i] = origin[i];
        }
    }

    // void String::copy_string(String const & origin, String & destination, std::size_t const length) {
    //     // Durch das i ≤ length + 1 wird auch der Terminator \0 mit kopiert
    //     for (std::size_t i = 0; i <= length + 1; i++) {
    //         destination.m_str[i] = origin.m_str[i];
    //     }
    //     destination.m_length = length;
    // }

    // Gibt die Länge des ursprünglichen Char-Arrays zurück.
    // Dry-Prinzip (Don't repeat yourself)
    int String::get_string_length(char const * NewStr) {
        int tLength { 0 };
        for (int i = 0; NewStr[i] != '\0'; i++) {
            tLength++;
        }
        return tLength;
    }

    // Eigentliches Addieren ausgelagert.
    // Dry-Prinzip (Don't repeat yourself)
    String String::add(String const & NewStr1, String const & NewStr2) {
        String tStr { };

        tStr.m_length = NewStr1.m_length + NewStr2.m_length;
        tStr.m_str = new char[tStr.m_length + 1];

        tStr.mem_zero();

        // Erst wird der erste String in den neuen String übertragen
        for (size_t i = 0; i < NewStr1.m_length; i++) {
            tStr.m_str[i] = NewStr1.m_str[i];
        }
        // Anschließend wird der zweite String direkt hinten angehängt.
        for (size_t i = 0; i < NewStr2.m_length; i++) {
            tStr.m_str[i + NewStr1.m_length] = NewStr2.m_str[i];
        }
        tStr.m_str[tStr.m_length] = '\0';
        return tStr;
    }

    // Plus Gleich ausgelagert
    // Dry-Prinzip (Don't repeat yourself)
    String & String::add_equal(String const & NewStr) {
        String temp { };
        temp = add(*this, NewStr);

        // Speichern der ursprünglichen Adresse
        char * tPointer = m_str;

        // Übertragen des neuen Speichers
        m_str = temp.m_str;
        m_length = temp.m_length;

        // Setze den Temp-String-Zeiger auf tPointer,
        // damit sichergestellt wird, dass der
        // Destruktor die richtige Adresse freigibt.
        temp.m_str = tPointer;

        return *this;
    }

    // Eigenes MemZero implementiert.
    // Schreibt \0 in den angelegten Speicher
    void String::mem_zero() const {
        for (size_t i = 0; i < m_length + 1; i++) {
            m_str[i] = '\0';
        }
    }

    // ----------- Private Klassenfunktionen -----------

    char String::operator[](int const position) const {
        if (position >= 0 && position <= m_length) {
            return m_str[position];
        }
        else {
            std::__throw_length_error("Index out of range.");
        }
    }

    // ----------- Vergleicher -----------
    bool operator==(String const & NewStr1, String const & NewStr2) {
        // Direkter Abbruch, wenn die Länge
        // der Strings unterschiedlich ist.
        if (NewStr1.m_length != NewStr2.m_length) {
            return false;
        }

        // Zeichenweiser Vergleich der Strings.
        // Abbruch bei dem ersten unterschiedlichen Zeichen.
        for (size_t i = 0; i < NewStr1.m_length; i++) {
            if (NewStr1.m_str[i] != NewStr2.m_str[i]) {
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
        String s1 = NewStr1.to_lower();
        String s2 = NewStr2.to_lower();
        auto shorter_word_length = NewStr1.m_length < NewStr2.m_length ? s1.m_length : s2.m_length;

        for (std::size_t i = 0; i < shorter_word_length; i++) {
            if (s1.m_str[i] < s2.m_str[i]) {
                return true;
            } else if (s1.m_str[i] > s2.m_str[i]) {
                return false;
            }
        }

        // Wenn alle verglichenen Zeichen gleich sind,
        // entscheidet die Länge des Strings.
        return s1.m_length < s2.m_length;
    }

    bool operator>(String const & NewStr1, String const & NewStr2) {
        String s1 = NewStr1.to_lower();
        String s2 = NewStr2.to_lower();
        auto shorter_word_length = NewStr1.m_length < NewStr2.m_length ? s1.m_length : s2.m_length;

        for (size_t i = 0; i < shorter_word_length; i++) {
            if (s1.m_str[i] > s2.m_str[i]) {
                return true;
            } else if (s1.m_str[i] < s2.m_str[i]) {
                return false;
            }
        }

        // Wenn alle verglichenen Zeichen gleich sind,
        // entscheidet die Länge des Strings.
        return s1.m_length > s2.m_length;
    }

    bool operator<=(String const & NewStr1, String const & NewStr2) {
        return !(NewStr1 > NewStr2);
    }

    bool operator>=(String const & NewStr1, String const & NewStr2) {
        return !(NewStr1 < NewStr2);
    }

    // ----------- Vergleicher -----------

    // Klassen-Methoden

    // Gibt einen String zurück, der den
    // gegebenen String in Kleinbuchstaben umwandelt.
    String String::to_lower() const {
        String temp(*this);

        for (size_t i = 0; i < m_length; i++) {
            if (temp.m_str[i] >= 'A' && temp.m_str[i] <= 'Z') {
                temp.m_str[i] = temp.m_str[i] + ('a' - 'A');
            }
        }

        return temp;
    }

    // Gibt einen String zurück, der den
    // gegebenen String in Großbuchstaben umwandelt.
    String String::to_upper() const {
        String temp {*this};

        for (size_t i = 0; i < m_length; i++) {
            if (temp.m_str[i] >= 'a' && temp.m_str[i] <= 'z') {
                temp.m_str[i] = temp.m_str[i] - ('a' - 'A');
            }
        }

        return temp;
    }

    // Wenn im String eine Integer-Zahl gespeichert ist,
    // wird diese als Integer ausgegeben.
    int String::to_int() const {
        // Wenn die Stringlänge 0 ist, ist es ein leerer String
        // und es ist auf gar keinen Fall eine Zahl gespeichert.
        if (m_length == 0) {
            return 0;
        }

        int tInt { 0 };
        int tSign { 1 };
        int tPos { 0 };

        // Wenn das erste Zeichen ein Minuszeichen ist.
        if (m_str[0] == '-') {
            tSign = -1;
            tPos = 1;
        }
        // Wenn das erste Zeichen Positiv ist.
        else if (m_str[tPos] == '+') {
            tPos = 1;
        }

        // Wenn das erste Zeichen kein Minuszeichen oder + ist,
        // aber nur ein Zeichen enthalten ist, gibt 0 zurück
        if (m_str[0] == '+' || m_str[0] == '-' && m_length == 1 ) {
            return 0;
        }

        for (int i = tPos; i < m_length; i++) {
            if (m_str[i] < '0' || m_str[i] > '9') {
                return 0;
            }
            tInt = tInt * 10 + m_str[i] - '0';
        }
        return tInt * tSign;
    }

    // Gibt den String auf der Konsole aus.
    std::ostream & operator<<(std::ostream & os, String const & NewStr) {
        os << NewStr.m_str;
        return os;
    }

    // Liest von der Konsole ein
    std::istream & operator>>(std::istream & is, String & NewStr) {
        char c;
        int laufvariable {0};
        int temp_length {8};

        char * tStr {new char[temp_length]};

        // Liest den Eingabestrom, bis ungültige Zeichen laut isspace kommen
        while (is.get(c) && !std::isspace(c)) {
            tStr[laufvariable] = c;
            laufvariable++;

            // Wenn die festgelegte Länge des Temp-Strings gleich
            // der Laufvariable ist, wird ein neues Array doppelter
            // Größe erzeugt und die Daten werden umgeschrieben.
            if (laufvariable == temp_length) {
                temp_length *= 2;
                char * tTemp {new char[temp_length]};
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
        NewStr = String { tStr };

        // Freigeben des allokierten Speichers
        delete[] tStr;

        return is;
    }
} // FSI1