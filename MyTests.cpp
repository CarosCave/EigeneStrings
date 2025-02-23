#include "Include/String.h"
#include <iostream>
#include "gtest/gtest.h"


TEST(Vergleichen, kleiner) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a < b, true);
    EXPECT_EQ(a < a, false);
    EXPECT_EQ(b < a, false);
}

TEST(Vergleichen, groesser) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Marianne");
    EXPECT_EQ(a > b, false);
    EXPECT_EQ(a > a, false);
    EXPECT_EQ(b > a, true);
}

TEST(Vergleichen, gleich) {
    _24FSI1::String a("Maria");
    _24FSI1::String b("Maria");
    _24FSI1::String c("Marianne");
    EXPECT_EQ(a == b, true);
    EXPECT_EQ(a == c, false);
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

// TEST(Console, Input_String) {
//     // Beginne mit dem Erfassen der Konsoleneingabe
//     //::testing::internal::
// }