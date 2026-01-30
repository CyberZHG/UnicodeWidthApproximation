import { describe, it } from "mocha";
import assert from "node:assert";
import { getStringWidth, getCodepointWidth, isWideChar, isZeroWidth } from "../index.js";

describe("getStringWidth", () => {
    it("should handle ASCII strings", () => {
        assert.strictEqual(getStringWidth(""), 0);
        assert.strictEqual(getStringWidth("Hello"), 5);
        assert.strictEqual(getStringWidth("Hello, World!"), 13);
    });

    it("should handle CJK strings", () => {
        assert.strictEqual(getStringWidth("中文"), 4);
        assert.strictEqual(getStringWidth("日本語"), 6);
        assert.strictEqual(getStringWidth("한국어"), 6);
    });

    it("should handle mixed strings", () => {
        assert.strictEqual(getStringWidth("Hello, 世界"), 11);
    });

    it("should handle emoji", () => {
        assert.strictEqual(getStringWidth("🐱"), 2);
        assert.strictEqual(getStringWidth("🙈🙉🙊"), 6);
        assert.strictEqual(getStringWidth("👋🏻"), 2);
        assert.strictEqual(getStringWidth("👨‍👩‍👧‍👦"), 2);
        assert.strictEqual(getStringWidth("🇨🇳"), 2);
    });

    it("should handle combining marks", () => {
        assert.strictEqual(getStringWidth("é"), 1);
        assert.strictEqual(getStringWidth("ä"), 1);
        assert.strictEqual(getStringWidth("é̂"), 1);
    });

    it("should handle control characters", () => {
        assert.strictEqual(getStringWidth("hello\n"), 5);
        assert.strictEqual(getStringWidth("hello\tworld"), 10);
    });

    it("should handle fullwidth characters", () => {
        assert.strictEqual(getStringWidth("ＡＢＣ"), 6);
    });
});

describe("getCodepointWidth", () => {
    it("should return 1 for ASCII", () => {
        assert.strictEqual(getCodepointWidth(0x41), 1);  // 'A'
        assert.strictEqual(getCodepointWidth(0x7A), 1);  // 'z'
        assert.strictEqual(getCodepointWidth(0x20), 1);  // space
    });

    it("should return 0 for control characters", () => {
        assert.strictEqual(getCodepointWidth(0x00), 0);  // NULL
        assert.strictEqual(getCodepointWidth(0x0A), 0);  // LF
        assert.strictEqual(getCodepointWidth(0x0D), 0);  // CR
    });

    it("should return 2 for CJK", () => {
        assert.strictEqual(getCodepointWidth(0x4E00), 2);
        assert.strictEqual(getCodepointWidth(0x3042), 2);  // Hiragana A
    });

    it("should return 2 for fullwidth", () => {
        assert.strictEqual(getCodepointWidth(0xFF01), 2);  // Fullwidth !
        assert.strictEqual(getCodepointWidth(0xFF21), 2);  // Fullwidth A
    });

    it("should return 2 for emoji", () => {
        assert.strictEqual(getCodepointWidth(0x1F600), 2);  // Grinning face
        assert.strictEqual(getCodepointWidth(0x1F1FA), 2);  // Regional Indicator U
    });

    it("should return 0 for combining marks", () => {
        assert.strictEqual(getCodepointWidth(0x0300), 0);  // Combining grave
        assert.strictEqual(getCodepointWidth(0x0301), 0);  // Combining acute
    });

    it("should return 0 for ZWJ", () => {
        assert.strictEqual(getCodepointWidth(0x200D), 0);
    });
});

describe("isWideChar", () => {
    it("should return true for CJK", () => {
        assert.strictEqual(isWideChar(0x4E00), true);
    });

    it("should return true for fullwidth", () => {
        assert.strictEqual(isWideChar(0xFF21), true);
    });

    it("should return false for ASCII", () => {
        assert.strictEqual(isWideChar(0x41), false);
    });
});

describe("isZeroWidth", () => {
    it("should return true for ZWJ", () => {
        assert.strictEqual(isZeroWidth(0x200D), true);
    });

    it("should return true for combining marks", () => {
        assert.strictEqual(isZeroWidth(0x0300), true);
    });

    it("should return true for control characters", () => {
        assert.strictEqual(isZeroWidth(0x0A), true);
    });

    it("should return false for ASCII", () => {
        assert.strictEqual(isZeroWidth(0x41), false);
    });
});
