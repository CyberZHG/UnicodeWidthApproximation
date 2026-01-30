from unicode_width_approximation import (get_codepoint_width, get_string_width,
                                         is_wide_char, is_zero_width)


def test_ascii_strings():
    assert get_string_width("") == 0
    assert get_string_width("Hello") == 5
    assert get_string_width("Hello, World!") == 13
    assert get_string_width("abc123") == 6


def test_cjk_strings():
    assert get_string_width("中文") == 4
    assert get_string_width("日本語") == 6
    assert get_string_width("한국어") == 6


def test_mixed_strings():
    assert get_string_width("Hello, 世界") == 11


def test_emoji_strings():
    assert get_string_width("🐱") == 2
    assert get_string_width("🙈🙉🙊") == 6
    assert get_string_width("👋🏻") == 2
    assert get_string_width("👨‍👩‍👧‍👦") == 2
    assert get_string_width("🇨🇳") == 2


def test_combining_marks():
    assert get_string_width("é") == 1
    assert get_string_width("ä") == 1
    assert get_string_width("é̂") == 1


def test_control_characters():
    assert get_string_width("hello\n") == 5
    assert get_string_width("hello\tworld") == 10


def test_fullwidth_characters():
    assert get_string_width("ＡＢＣ") == 6


def test_codepoint_width():
    # ASCII
    assert get_codepoint_width(ord("A")) == 1
    assert get_codepoint_width(ord("z")) == 1
    assert get_codepoint_width(ord(" ")) == 1

    # Control characters
    assert get_codepoint_width(0x00) == 0  # NULL
    assert get_codepoint_width(0x0A) == 0  # LF
    assert get_codepoint_width(0x0D) == 0  # CR

    # CJK
    assert get_codepoint_width(0x4E00) == 2
    assert get_codepoint_width(0x3042) == 2  # Hiragana A

    # Fullwidth
    assert get_codepoint_width(0xFF01) == 2  # Fullwidth !
    assert get_codepoint_width(0xFF21) == 2  # Fullwidth A

    # Emoji
    assert get_codepoint_width(0x1F600) == 2  # Grinning face
    assert get_codepoint_width(0x1F1FA) == 2  # Regional Indicator U

    # Combining marks
    assert get_codepoint_width(0x0300) == 0  # Combining grave
    assert get_codepoint_width(0x0301) == 0  # Combining acute

    # ZWJ
    assert get_codepoint_width(0x200D) == 0


def test_is_wide_char():
    assert is_wide_char(0x4E00) is True  # CJK
    assert is_wide_char(0xFF21) is True  # Fullwidth A
    assert is_wide_char(ord("A")) is False


def test_is_zero_width():
    assert is_zero_width(0x200D) is True  # ZWJ
    assert is_zero_width(0x0300) is True  # Combining grave
    assert is_zero_width(0x0A) is True  # LF
    assert is_zero_width(ord("A")) is False
