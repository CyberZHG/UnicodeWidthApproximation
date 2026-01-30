#include <gtest/gtest.h>
#include "unicode_width.h"
using namespace unicode_width;

TEST(TestWidthProperties, uniform_sampling) {
    for (int32_t code = 0; code < 0xEFFFF; code += 377) {
        ASSERT_EQ(isZeroWidthBruteForce(code), isZeroWidth(code));
        ASSERT_EQ(isWideCharBruteForce(code), isWideChar(code));
    }
}

TEST(TestWidthProperties, basic_codepoints) {
    // ASCII
    EXPECT_EQ(getCodepointWidth('a'), 1);
    EXPECT_EQ(getCodepointWidth('Z'), 1);
    EXPECT_EQ(getCodepointWidth('0'), 1);
    EXPECT_EQ(getCodepointWidth(' '), 1);

    // Control characters (zero width)
    EXPECT_EQ(getCodepointWidth(0x00), 0);  // NULL
    EXPECT_EQ(getCodepointWidth(0x0A), 0);  // LF
    EXPECT_EQ(getCodepointWidth(0x0D), 0);  // CR
    EXPECT_EQ(getCodepointWidth(0x1B), 0);  // ESC

    // CJK characters (wide)
    EXPECT_EQ(getCodepointWidth(0x4E00), 2);  // CJK Unified Ideograph
    EXPECT_EQ(getCodepointWidth(0x3042), 2);  // Hiragana A
    EXPECT_EQ(getCodepointWidth(0x30A2), 2);  // Katakana A
    EXPECT_EQ(getCodepointWidth(0xAC00), 2);  // Hangul syllable

    // Full-width characters
    EXPECT_EQ(getCodepointWidth(0xFF01), 2);  // Fullwidth exclamation mark
    EXPECT_EQ(getCodepointWidth(0xFF21), 2);  // Fullwidth Latin capital A

    // Emoji (wide)
    EXPECT_EQ(getCodepointWidth(0x1F600), 2);  // Grinning face
    EXPECT_EQ(getCodepointWidth(0x1F4A9), 2);  // Pile of poo

    // Zero-width joiner
    EXPECT_EQ(getCodepointWidth(0x200D), 0);  // ZWJ
    EXPECT_EQ(getCodepointWidth(0x200B), 0);  // ZWSP

    // Combining marks (zero width)
    EXPECT_EQ(getCodepointWidth(0x0300), 0);  // Combining grave accent
    EXPECT_EQ(getCodepointWidth(0x0301), 0);  // Combining acute accent

    // Emoji_Presentation characters - width 2
    EXPECT_EQ(getCodepointWidth(0x1F1FA), 2);  // Regional Indicator U
    EXPECT_EQ(getCodepointWidth(0x1F1F8), 2);  // Regional Indicator S
    EXPECT_EQ(getCodepointWidth(0x1F600), 2);  // Grinning face
    EXPECT_EQ(getCodepointWidth(0x1F4A9), 2);  // Pile of poo

    // Text-default emoji (not Emoji_Presentation) - width 1 without VS16
    EXPECT_EQ(getCodepointWidth(0x00A9), 1);  // Copyright sign (text-default)
    EXPECT_EQ(getCodepointWidth(0x2764), 1);  // Red heart (text-default)
}
