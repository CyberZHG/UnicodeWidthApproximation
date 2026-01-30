/**
 * Calculate the total display width of a string.
 *
 * This function segments the string into grapheme clusters and calculates
 * the width based on the base character of each cluster.
 *
 * @param s - The input string.
 * @returns The total display width in columns.
 *
 * @example
 * ```typescript
 * import { getStringWidth } from "unicode-width-approximation";
 *
 * getStringWidth("hello");      // 5
 * getStringWidth("中文");        // 4
 * getStringWidth("👨‍👩‍👧‍👦");  // 2
 * ```
 */
export function getStringWidth(s: string): number;

/**
 * Get the display width of a single Unicode code point.
 *
 * @param code - The Unicode code point.
 * @returns The display width (0, 1, or 2).
 *
 * @example
 * ```typescript
 * import { getCodepointWidth } from "unicode-width-approximation";
 *
 * getCodepointWidth(0x41);    // 1 (ASCII 'A')
 * getCodepointWidth(0x4E00);  // 2 (CJK)
 * getCodepointWidth(0x0300);  // 0 (combining mark)
 * ```
 */
export function getCodepointWidth(code: number): number;

/**
 * Check if a code point is a wide character (East Asian Wide or Fullwidth).
 *
 * @param code - The Unicode code point.
 * @returns True if the character has width 2.
 */
export function isWideChar(code: number): boolean;

/**
 * Check if a code point is a zero-width character.
 *
 * @param code - The Unicode code point.
 * @returns True if the character has zero width.
 */
export function isZeroWidth(code: number): boolean;
