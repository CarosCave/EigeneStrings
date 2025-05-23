#include "Include/String.h"
#include <iostream>
#include "gtest/gtest.h"


TEST(Vergleichen, String_kleiner_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a < b, true);
    EXPECT_EQ(a < a, false);
    EXPECT_EQ(b < a, false);
}

TEST(Vergleichen, String_kleiner_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    EXPECT_EQ(a < b, true);
    EXPECT_EQ(b < a, false);
}

TEST(Vergleichen, String_Groesser_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a > b, false);
    EXPECT_EQ(a > a, false);
    EXPECT_EQ(b > a, true);
}

TEST(Vergleichen, String_Groesser_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    EXPECT_EQ(a > b, false);
    EXPECT_EQ(b > a, true);
}

TEST(Vergleichen, String_Gleich_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Maria");
    _24FSI1::String c("Marianne");
    EXPECT_EQ(a == b, true);
    EXPECT_EQ(a == c, false);
}

TEST(Vergleichen, String_Gleich_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Maria";
    EXPECT_EQ(a == b, true);
    EXPECT_EQ(b == a, true);
}

TEST(Vergleichen, String_Kleiner_Gleich_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a <= b, true);
    EXPECT_EQ(a <= a, true);
    EXPECT_EQ(b <= a, false);
}

TEST(Vergleichen, String_Kleiner_Gleich_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    EXPECT_EQ(a <= b, true);
    EXPECT_EQ(b <= a, false);
}

TEST(Vergleichen, String_Groesser_Gleich_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a >= b, false);
    EXPECT_EQ(a >= a, true);
    EXPECT_EQ(b >= a, true);
}

TEST(Vergleichen, String_Groesser_Gleich_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    EXPECT_EQ(a >= b, false);
    EXPECT_EQ(b >= a, true);
}

TEST(String_Manipulation, toLower) {
    _24FSI1::String a("MARIA");
    _24FSI1::String b = a.toLower();
    EXPECT_EQ(b, "maria");
}

TEST(String_Manipulation, toUpper) {
    _24FSI1::String a("maria");
    _24FSI1::String b = a.toUpper();
    EXPECT_EQ(b, "MARIA");
}

TEST(Misc, Give_Length) {
    _24FSI1::String a("Maria");
    EXPECT_EQ(a.Length(), 5);
}

TEST(Misc, Weise_Char_Array_Zu) {
    _24FSI1::String a;
    a = "Maria";
    EXPECT_EQ(a, "Maria");
}

TEST(Misc, Weise_Char_Zu) {
    _24FSI1::String a;
    a = 'M';
    EXPECT_EQ(a, 'M');
}

TEST(Misc, Weise_String_Zu) {
    _24FSI1::String a("Maria");
    _24FSI1::String b;
    b = a;
    EXPECT_EQ(b, "Maria");
}

TEST(Misc, Rückgabe_Char_Array) {
    _24FSI1::String a("Maria");
    const char *b = a.c_str();
    char *c = a.c_str();
    EXPECT_STREQ(b, "Maria");
    EXPECT_STREQ(c, "Maria");
}

TEST(Misc, Rückgabe_Integer_Positiv) {
    _24FSI1::String a("100");
    int b = a.toInt();
    EXPECT_EQ(b, 100);
}

TEST(Misc, Rückgabe_Integer_Negativ) {
    _24FSI1::String a("-100");
    int b = a.toInt();
    EXPECT_EQ(b, -100);
}

TEST(Misc, Rückgabe_Integer_Fehler_1) {
    _24FSI1::String a("A00");
    int b = a.toInt();
    EXPECT_EQ(b, 0);
}

TEST(Misc, Rückgabe_Integer_Fehler_2) {
    _24FSI1::String a("4A00");
    int b = a.toInt();
    EXPECT_EQ(b, 0);
}

TEST(Misc, Rechnen_mit_zwei_Integer) {
    _24FSI1::String a("100");
    _24FSI1::String b("200");
    int c = a.toInt() + b.toInt();
    EXPECT_EQ(c, 300);
}

TEST(Strings, Addiere_String_Char) {
    _24FSI1::String a("Maria");
    char b = 'M';
    _24FSI1::String c = a + b;
    EXPECT_EQ(c, "MariaM");
}

TEST(Strings, Addiere_String_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    _24FSI1::String c = a + b;
    EXPECT_EQ(c, "MariaMarianne");
}

TEST(Strings, Adddiere_String_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    _24FSI1::String c = a + b;
    EXPECT_EQ(c, "MariaMarianne");
}

TEST(Strings, ConCat_String_Char) {
    _24FSI1::String a("Maria");
    char b = 'M';
    a += b;
    EXPECT_EQ(a, "MariaM");
}

TEST(Strings, ConCat_String_CharArray) {
    _24FSI1::String a("Maria");
    char b[] = "Marianne";
    a += b;
    EXPECT_EQ(a, "MariaMarianne");
}

TEST(Strings, ConCat_String_String) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    a += b;
    EXPECT_EQ(a, "MariaMarianne");
}

TEST(Console, Output) {
    // Beginne mit dem Erfassen der Konsolenausgabe
    ::testing::internal::CaptureStdout();

    _24FSI1::String a("Maria");
    std::cout << a;

    // Beende die Erfassung und speichere die Ausgabe
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Maria");
}

TEST(Console, Input_Char) {
    // Beginne mit dem Erfassen der Konsoleneingabe
    std::istringstream iss("M");

    _24FSI1::String a;
    iss >> a;

    EXPECT_EQ(a, "M");
}

TEST(Console, Input_String_Kleiner_8) {
     // Beginne mit dem Erfassen der Konsoleneingabe
     std::istringstream iss("Maria");

    _24FSI1::String a;
     iss >> a;

    EXPECT_EQ(a, "Maria");
}

TEST(Console, Input_String_Groesser_8) {
    // Beginne mit dem Erfassen der Konsoleneingabe
    std::istringstream iss("MariannenGraben");
    std::streambuf *buf = iss.rdbuf();


    _24FSI1::String a;
    iss >> a;

    EXPECT_EQ(a, "MariannenGraben");

}

TEST(Console, Input_Int) {
    // Beginne mit dem Erfassen der Konsoleneingabe
    std::istringstream iss("100");

    _24FSI1::String a;
    iss >> a;

    EXPECT_EQ(a, "100");
}

TEST(Misc, Output_Int_100) {
    _24FSI1::String a("100");

    int b = a.toInt();

    EXPECT_EQ(b, 100);
}