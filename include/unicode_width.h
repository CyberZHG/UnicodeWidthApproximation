#ifndef UNICODE_WIDTH_APPROXIMATION_UNICODE_WIDTH_H
#define UNICODE_WIDTH_APPROXIMATION_UNICODE_WIDTH_H

#include <string>
#include <cstdint>

namespace unicode_width {

    /**
     * @brief Get the display width of a single Unicode code point.
     *
     * Width rules:
     * - Control characters, format characters, and combining marks have width 0
     * - East Asian Wide (W) and Fullwidth (F) characters have width 2
     * - Emoji_Presentation characters have width 2
     * - All other characters have width 1
     *
     * @param code The Unicode code point.
     * @return The display width (0, 1, or 2).
     */
    int getCodepointWidth(std::int32_t code);

    /**
     * @brief Calculate the total display width of a UTF-8 encoded string.
     *
     * This function segments the string into grapheme clusters and calculates
     * the width based on the base character of each cluster.
     *
     * @param s The UTF-8 encoded string.
     * @return The total display width in columns.
     */
    int getStringWidth(const std::string& s);

    /**
     * @brief Check if a code point is a zero-width character.
     *
     * Zero-width characters include:
     * - Control characters (General Category Cc)
     * - Format characters (General Category Cf)
     * - Nonspacing marks (General Category Mn)
     * - Enclosing marks (General Category Me)
     * - Line/Paragraph separators (General Category Zl, Zp)
     *
     * @param code The Unicode code point.
     * @return true if the character has zero width.
     */
    bool isZeroWidth(std::int32_t code);

    /**
     * @brief Check if a code point is a wide character (width 2).
     *
     * Wide characters include:
     * - East Asian Wide (W) characters
     * - East Asian Fullwidth (F) characters
     *
     * @param code The Unicode code point.
     * @return true if the character has width 2.
     */
    bool isWideChar(std::int32_t code);

    /** For unit tests only. */
    bool isZeroWidthBruteForce(std::int32_t code);
    /** For unit tests only. */
    bool isWideCharBruteForce(std::int32_t code);

}

#endif //UNICODE_WIDTH_APPROXIMATION_UNICODE_WIDTH_H
