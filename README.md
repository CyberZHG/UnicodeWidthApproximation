# Unicode Width Approximation

[![Unicode 17.0.0](https://img.shields.io/badge/Unicode-17.0.0-blue.svg)](https://www.unicode.org/versions/Unicode17.0.0/)
[![C++ Unit Tests](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/cpp-unit-tests.yml/badge.svg)](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/cpp-unit-tests.yml)
[![Python Build & Test](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/python-build-test.yml/badge.svg)](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/python-build-test.yml)
[![WASM Build & Test](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/wasm-build-test.yml/badge.svg)](https://github.com/CyberZHG/UnicodeWidthApproximation/actions/workflows/wasm-build-test.yml)
[![](https://img.shields.io/pypi/v/unicode-width-approximation)](https://pypi.org/project/unicode-width-approximation/)
[![](https://img.shields.io/pypi/v/unicode-width-approximation)](https://www.npmjs.com/package/unicode-width-approximation)
[![Coverage Status](https://coveralls.io/repos/github/CyberZHG/UnicodeWidthApproximation/badge.svg?branch=main)](https://coveralls.io/github/CyberZHG/UnicodeWidthApproximation?branch=main)
![](https://visitor-badge.laobi.icu/badge?page_id=cyberzhg.UnicodeWidthApproximation)

A library for calculating the display width of Unicode strings in terminal/monospace environments.

Available for **C++**, **Python**, and **JavaScript/WebAssembly**.

## Features

- Full compliance with Unicode 17.0 character properties
- Width calculation based on East Asian Width, General Category, and Emoji properties
- Grapheme cluster aware: emoji sequences, combining marks, etc. are handled correctly

## Width Rules

| Character Type           | Width  | Examples                    |
|--------------------------|--------|-----------------------------|
| Control characters (Cc)  | 0      | `\x00`, `\n`, `\t`          |
| Format characters (Cf)   | 0      | ZWJ (U+200D), ZWNJ (U+200C) |
| Combining marks (Mn, Me) | 0      | Combining accents           |
| East Asian Wide (W)      | 2      | CJK ideographs              |
| East Asian Fullwidth (F) | 2      | Fullwidth ASCII             |
| Emoji_Presentation       | 2      | 🐱, 🇨🇳, 👨‍👩‍👧‍👦       |
| Other characters         | 1      | ASCII, Latin, etc.          |

## Examples

| Input             | Width  | Explanation                                              |
|-------------------|--------|----------------------------------------------------------|
| `"hello"`         | 5      | 5 ASCII characters                                       |
| `"中文"`            | 4      | 2 CJK characters × 2                                     |
| `"café"`          | 4      | 4 characters (é is precomposed)                          |
| `"cafe\u0301"`    | 4      | "cafe" + combining acute = 4 (combining mark is 0 width) |
| `"👨‍👩‍👧‍👦"`   | 2      | Family emoji (1 grapheme cluster)                        |
| `"🇨🇳"`          | 2      | Flag emoji (1 grapheme cluster)                          |
| `"Ａ"` (fullwidth) | 2      | Fullwidth Latin A                                        |

## Installation

### Python

```bash
pip install unicode-width-approximation
```

### JavaScript (NPM)

```bash
npm install unicode-width-approximation
```

### C++ (CMake)

Add as a subdirectory or use FetchContent:

```cmake
include(FetchContent)
FetchContent_Declare(
    UnicodeWidthApproximation
    GIT_REPOSITORY https://github.com/CyberZHG/UnicodeWidthApproximation.git
    GIT_TAG main
)
FetchContent_MakeAvailable(UnicodeWidthApproximation)

target_link_libraries(your_target PRIVATE UnicodeWidthApproximation)
```

## Usage

### Python

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

### JavaScript / TypeScript

```javascript
import {
    getStringWidth,
    getCodepointWidth
} from "unicode-width-approximation";

// Get width of strings
console.log(getStringWidth("hello"));      // 5
console.log(getStringWidth("中文"));        // 4
console.log(getStringWidth("👨‍👩‍👧‍👦"));  // 2

// Get width of single code points
console.log(getCodepointWidth(0x41));    // 1 (ASCII 'A')
console.log(getCodepointWidth(0x4E00));  // 2 (CJK)
console.log(getCodepointWidth(0x1F600)); // 2 (emoji)
```

### C++

```cpp
#include "unicode_width.h"
#include <iostream>

int main() {
    // Get width of a string
    std::cout << unicode_width::getStringWidth("hello") << std::endl;      // 5
    std::cout << unicode_width::getStringWidth("中文") << std::endl;        // 4
    std::cout << unicode_width::getStringWidth("👨‍👩‍👧‍👦") << std::endl;  // 2
    std::cout << unicode_width::getStringWidth("🇨🇳") << std::endl;        // 2

    // Get width of a single code point
    std::cout << unicode_width::getCodepointWidth('A') << std::endl;       // 1
    std::cout << unicode_width::getCodepointWidth(0x4E00) << std::endl;    // 2 (CJK)
    std::cout << unicode_width::getCodepointWidth(0x1F600) << std::endl;   // 2 (emoji)
    std::cout << unicode_width::getCodepointWidth(0x0300) << std::endl;    // 0 (combining)

    // Check character properties
    std::cout << unicode_width::isWideChar(0x4E00) << std::endl;           // true
    std::cout << unicode_width::isZeroWidth(0x200D) << std::endl;          // true

    return 0;
}
```

## API Reference

### `getStringWidth(s)` / `get_string_width(s)`

Calculates the total display width of a UTF-8 encoded string.

**Parameters:**
- `s` - The input UTF-8 encoded string

**Returns:**
- The total display width in columns

**Note:** This function uses grapheme cluster segmentation to correctly handle combining marks and emoji sequences. The width is determined by the first code point of each grapheme cluster.

### `getCodepointWidth(code)` / `get_codepoint_width(code)`

Gets the display width of a single Unicode code point.

**Parameters:**
- `code` - The Unicode code point

**Returns:**
- `0` for zero-width characters (control, format, combining marks)
- `2` for wide characters (CJK, fullwidth, emoji)
- `1` for all other characters

### `isWideChar(code)` / `is_wide_char(code)`

Checks if a code point is a wide character (East Asian Wide or Fullwidth).

**Parameters:**
- `code` - The Unicode code point

**Returns:**
- `true` if the character has width 2

### `isZeroWidth(code)` / `is_zero_width(code)`

Checks if a code point is a zero-width character.

**Parameters:**
- `code` - The Unicode code point

**Returns:**
- `true` if the character has width 0

## Building from Source

### Prerequisites

- CMake 4.0+
- C++20 compatible compiler
- Python 3.x (for generating Unicode data tables)
- (Optional) Python 3.8+ with pybind11 for Python bindings
- (Optional) Emscripten for WebAssembly bindings

### Build Commands

```bash
# C++ library only
cmake -B build
cmake --build build

# With tests
cmake -B build -DUNICODE_WIDTH_APPROXIMATION_ENABLE_TESTS=ON
cmake --build build
ctest --test-dir build

# Python bindings (via pip)
pip install .

# WebAssembly bindings
cd wasm
npm run build
```

### CMake Options

| Option                                        | Default  | Description                     |
|-----------------------------------------------|----------|---------------------------------|
| `UNICODE_WIDTH_APPROXIMATION_ENABLE_TESTS`    | `OFF`    | Build unit tests                |
| `UNICODE_WIDTH_APPROXIMATION_ENABLE_COVERAGE` | `OFF`    | Enable code coverage            |
| `UNICODE_WIDTH_APPROXIMATION_ENABLE_STRICT`   | `OFF`    | Enable strict compiler warnings |
| `UNICODE_WIDTH_APPROXIMATION_BIND_PYTHON`     | `OFF`    | Build Python bindings           |
| `UNICODE_WIDTH_APPROXIMATION_BIND_ES`         | `OFF`    | Build WebAssembly bindings      |

## Data Sources

This library uses the following Unicode Character Database files:

- `EastAsianWidth.txt` - East Asian Width property
- `DerivedGeneralCategory.txt` - General Category property
- `emoji-data.txt` - Emoji properties

## Notes on Text-Default Emoji

Some emoji characters (like © U+00A9 and ❤ U+2764) are "text-default", meaning they display as text by default and only appear as emoji when followed by VS16 (U+FE0F). This library returns width 1 for these characters when they appear alone. When combined with VS16 in a grapheme cluster, the cluster is treated as a single emoji with width 2.

## License

MIT License

## Links

- [Unicode UAX #11: East Asian Width](https://www.unicode.org/reports/tr11/)
- [Unicode UAX #29: Unicode Text Segmentation](https://www.unicode.org/reports/tr29/)
- [Unicode 17.0 Character Database](https://www.unicode.org/Public/17.0.0/ucd/)
- [GraphemeClusterBreak](https://github.com/CyberZHG/GraphemeClusterBreak) - Dependency for grapheme cluster segmentation
