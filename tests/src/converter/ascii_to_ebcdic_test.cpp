#include <gtest/gtest.h>
#include <pentaledger/converter/ASCII_to_EBCDIC.hpp>
#include <string>

using namespace pentaledger::converter;

TEST(AsciiToEbcdicTest, BasicCharacterConversion) {
    // Test basic alphanumeric characters
    std::string asciiText = "Hello World 123";
    std::string ebcdicText = asciiToebcdic(asciiText);
    
    // Verify the conversion
    EXPECT_EQ(ebcdicText.size(), asciiText.size());
    
    // Check specific character conversions
    // 'H' (ASCII 72) should convert to EBCDIC 0xC8
    EXPECT_EQ((unsigned char)ebcdicText[0], 0xC8);
    // 'e' (ASCII 101) should convert to EBCDIC 0x85
    EXPECT_EQ((unsigned char)ebcdicText[1], 0x85);
    // '1' (ASCII 49) should convert to EBCDIC 0xF1
    EXPECT_EQ((unsigned char)ebcdicText[11], 0xF1);
}

TEST(AsciiToEbcdicTest, SpecialCharacters) {
    // Test special characters
    std::string specialChars = "!@#$%^&*()";
    std::string ebcdicSpecial = asciiToebcdic(specialChars);
    
    EXPECT_EQ(ebcdicSpecial.size(), specialChars.size());
    
    // Check some known conversions
    // '!' (ASCII 33) should convert to EBCDIC 0x5A
    EXPECT_EQ((unsigned char)ebcdicSpecial[0], 0x5A);
    // '@' (ASCII 64) should convert to EBCDIC 0x7C
    EXPECT_EQ((unsigned char)ebcdicSpecial[1], 0x7C);
}

TEST(AsciiToEbcdicTest, EmptyString) {
    // Test empty string
    std::string emptyStr = "";
    std::string ebcdicEmpty = asciiToebcdic(emptyStr);
    
    EXPECT_TRUE(ebcdicEmpty.empty());
}

TEST(AsciiToEbcdicTest, AllPrintableCharacters) {
    // Test all printable ASCII characters
    std::string allPrintable;
    for (int i = 32; i <= 126; ++i) {
        allPrintable += static_cast<char>(i);
    }
    
    std::string ebcdicAll = asciiToebcdic(allPrintable);
    
    EXPECT_EQ(ebcdicAll.size(), allPrintable.size());
    
    // Verify some key conversions
    // Space (ASCII 32) should convert to EBCDIC 0x40
    EXPECT_EQ((unsigned char)ebcdicAll[0], 0x40);
    // 'A' (ASCII 65) should convert to EBCDIC 0xC1
    EXPECT_EQ((unsigned char)ebcdicAll[33], 0xC1);
    // 'a' (ASCII 97) should convert to EBCDIC 0x81
    EXPECT_EQ((unsigned char)ebcdicAll[65], 0x81);
}

TEST(AsciiToEbcdicTest, NonPrintableCharacters) {
    // Test non-printable characters
    std::string nonPrintable;
    for (int i = 0; i < 32; ++i) {
        nonPrintable += static_cast<char>(i);
    }
    
    std::string ebcdicNonPrintable = asciiToebcdic(nonPrintable);
    
    EXPECT_EQ(ebcdicNonPrintable.size(), nonPrintable.size());
    
    // Verify some key conversions
    // NUL (ASCII 0) should convert to EBCDIC 0x00
    EXPECT_EQ((unsigned char)ebcdicNonPrintable[0], 0x00);
    // TAB (ASCII 9) should convert to EBCDIC 0x05
    EXPECT_EQ((unsigned char)ebcdicNonPrintable[9], 0x05);
    // CR (ASCII 13) should convert to EBCDIC 0x0D
    EXPECT_EQ((unsigned char)ebcdicNonPrintable[13], 0x0D);
}

TEST(AsciiToEbcdicTest, ExtendedCharacters) {
    // Test extended ASCII characters
    std::string extended;
    for (int i = 128; i <= 255; ++i) {
        extended += static_cast<char>(i);
    }
    
    std::string ebcdicExtended = asciiToebcdic(extended);
    
    EXPECT_EQ(ebcdicExtended.size(), extended.size());
    
    // Verify some key conversions
    // Extended characters should be mapped to 0x00
    EXPECT_EQ((unsigned char)ebcdicExtended[0], 0x00);
    EXPECT_EQ((unsigned char)ebcdicExtended[127], 0x00);
} 