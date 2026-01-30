# Unicode Width Approximation

A library for calculating the display width of Unicode strings in terminal/monospace environments.

## Installation

```bash
pip install unicode-width-approximation
```

## Usage

```python
from unicode_width_approximation import get_string_width, get_codepoint_width

# Get width of strings
print(get_string_width("hello"))      # 5
print(get_string_width("中文"))        # 4
print(get_string_width("👨‍👩‍👧‍👦"))  # 2

# Get width of single code points
print(get_codepoint_width(ord('A')))  # 1
print(get_codepoint_width(0x4E00))    # 2 (CJK)
print(get_codepoint_width(0x1F600))   # 2 (emoji)
```

## API

### `get_string_width(s: str) -> int`

Calculate the total display width of a UTF-8 encoded string.

### `get_codepoint_width(code: int) -> int`

Get the display width of a single Unicode code point (0, 1, or 2).

### `is_wide_char(code: int) -> bool`

Check if a code point is a wide character (East Asian Wide or Fullwidth).

### `is_zero_width(code: int) -> bool`

Check if a code point is a zero-width character.

## Width Rules

| Character Type | Width |
|---------------|-------|
| Control characters (Cc) | 0 |
| Format characters (Cf) | 0 |
| Combining marks (Mn, Me) | 0 |
| East Asian Wide (W) | 2 |
| East Asian Fullwidth (F) | 2 |
| Emoji_Presentation | 2 |
| Other characters | 1 |

## License

MIT License
