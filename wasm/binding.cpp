#include <emscripten/bind.h>
#include "unicode_width.h"
using namespace emscripten;
using namespace unicode_width;

EMSCRIPTEN_BINDINGS(UnicodeWidth) {
    function("_getStringWidth", &getStringWidth);
    function("_getCodepointWidth", &getCodepointWidth);
    function("_isWideChar", &isWideChar);
    function("_isZeroWidth", &isZeroWidth);
}
