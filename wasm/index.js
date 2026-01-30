import createModule from "./wasm/UnicodeWidthApproximationWASM.js";

const UnicodeWidthApproximationWASM = await createModule();

/**
 * Calculate the total display width of a string.
 *
 * This function segments the string into grapheme clusters and calculates
 * the width based on the base character of each cluster.
 *
 * @param {string} s - The input string.
 * @returns {number} The total display width in columns.
 */
export function getStringWidth(s) {
    return UnicodeWidthApproximationWASM._getStringWidth(s);
}

/**
 * Get the display width of a single Unicode code point.
 *
 * @param {number} code - The Unicode code point.
 * @returns {number} The display width (0, 1, or 2).
 */
export function getCodepointWidth(code) {
    return UnicodeWidthApproximationWASM._getCodepointWidth(code);
}

/**
 * Check if a code point is a wide character (East Asian Wide or Fullwidth).
 *
 * @param {number} code - The Unicode code point.
 * @returns {boolean} True if the character has width 2.
 */
export function isWideChar(code) {
    return UnicodeWidthApproximationWASM._isWideChar(code);
}

/**
 * Check if a code point is a zero-width character.
 *
 * @param {number} code - The Unicode code point.
 * @returns {boolean} True if the character has zero width.
 */
export function isZeroWidth(code) {
    return UnicodeWidthApproximationWASM._isZeroWidth(code);
}
