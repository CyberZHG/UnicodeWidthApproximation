#!/usr/bin/env bash

emcmake cmake .. -B wasm -DUNICODE_WIDTH_APPROXIMATION_BIND_ES=ON
(cd wasm && emmake make UnicodeWidthApproximationWASM)
