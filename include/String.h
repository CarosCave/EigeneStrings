#ifndef STRING_H
#define STRING_H
#include <iostream>


// Kein _24 im Namespace, da dies laut Standard nicht OK ist.
namespace FSI1 {
    class String {
    private:
        char * m_str; // Data
        std::size_t m_length; // Größe

        static int get_string_length(char const * NewStr);

        static String add(String const & NewStr1, String const & NewStr2);

        String & add_equal(String const & NewStr);
        //void copy_string(char const * const origin, String & destination, std::size_t const length);
        static void copy_string(char const * const origin, char * destination, std::size_t const start_pos, std::size_t const length);

        void mem_zero() const;

    public:
        // Konstruktoren und Destruktoren
        // Standardkonstruktor
        String();

        // Erlaubt implizierte Typkonvertierungen
        // für String s = "Test";
        // oder String t("Test");
        String(char const *const NewStr);

        // Konstruktor baut aus einzelnem Char ein String
        String(char const c);

        // Kopierkonstruktor stellt sicher, dass die Strings
        // korrekt kopiert werden und es keine Speicherprobleme gibt
        String(String const &NewStr);

        // Destruktor
        ~String();

        // Operatoren
        // Operator=
        // String & operator=(char const c);
        // String & operator=(char const * const NewStr);
        String &operator=(String const & NewStr);

        // Operator+
        // String operator+(char c) const;
        // String operator+(char const * NewStr) const;
        String operator+(String const & NewStr) const;

        // Operator+=
        // String & operator+=(char c);
        // String & operator+=(char const * NewStr);
        String &operator+=(String const & NewStr);

        char operator[](int position) const;

        // Vergleichende Friends, damit der symmetrische Vergleich möglich ist
        // ==
        friend bool operator==(String const & NewStr1, String const & NewStr2);

        // !=
        friend bool operator!=(String const & NewStr1, String const & NewStr2);

        // <
        friend bool operator<(String const & NewStr1, String const & NewStr2);

        // >
        friend bool operator>(String const & NewStr1, String const & NewStr2);

        // <=
        friend bool operator<=(String const & NewStr1, String const & NewStr2);

        // >=
        friend bool operator>=(String const & NewStr1, String const & NewStr2);


        // Methoden

        [[nodiscard]] String to_lower() const;

        [[nodiscard]] String to_upper() const;

        [[nodiscard]] int to_int() const;

        // Inline-Methoden
        // Rückgabe der Stringlänge
        [[nodiscard]] size_t length() const {
            return m_length;
        }

        // Rückgabe als Char-Array
        [[nodiscard]] char *c_str() const {
            return m_str;
        }

        friend std::ostream &operator<<(std::ostream &os, String const &NewStr);

        friend std::istream &operator>>(std::istream &is, String &NewStr);
    };
} // FSI1

#endif //STRING_H
