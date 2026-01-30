#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "unicode_width.h"
using namespace std;
using namespace unicode_width;

namespace py = pybind11;

PYBIND11_MODULE(_core, m, py::mod_gil_not_used()) {
    m.doc() = "A library for calculating the display width of Unicode strings.";

    m.def("get_string_width",
          &getStringWidth,
          py::arg("s"),
          R"pbdoc(
Calculate the total display width of a UTF-8 encoded string.

This function segments the string into grapheme clusters and calculates
the width based on the base character of each cluster.

Args:
    s: The UTF-8 encoded string.

Returns:
    The total display width in columns.

Example:
    >>> get_string_width("hello")
    5
    >>> get_string_width("中文")
    4
    >>> get_string_width("👨‍👩‍👧‍👦")
    2
)pbdoc");

    m.def("get_codepoint_width",
          &getCodepointWidth,
          py::arg("code"),
          R"pbdoc(
Get the display width of a single Unicode code point.

Width rules:
- Control characters, format characters, and combining marks have width 0
- East Asian Wide (W) and Fullwidth (F) characters have width 2
- Emoji_Presentation characters have width 2
- All other characters have width 1

Args:
    code: The Unicode code point.

Returns:
    The display width (0, 1, or 2).

Example:
    >>> get_codepoint_width(ord('A'))
    1
    >>> get_codepoint_width(0x4E00)  # CJK
    2
    >>> get_codepoint_width(0x0300)  # Combining mark
    0
)pbdoc");

    m.def("is_wide_char",
          &isWideChar,
          py::arg("code"),
          R"pbdoc(
Check if a code point is a wide character (East Asian Wide or Fullwidth).

Args:
    code: The Unicode code point.

Returns:
    True if the character has width 2.
)pbdoc");

    m.def("is_zero_width",
          &isZeroWidth,
          py::arg("code"),
          R"pbdoc(
Check if a code point is a zero-width character.

Zero-width characters include:
- Control characters (General Category Cc)
- Format characters (General Category Cf)
- Nonspacing marks (General Category Mn)
- Enclosing marks (General Category Me)
- Line/Paragraph separators (General Category Zl, Zp)

Args:
    code: The Unicode code point.

Returns:
    True if the character has zero width.
)pbdoc");
}
