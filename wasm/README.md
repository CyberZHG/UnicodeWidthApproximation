# Unicode Width Approximation (WASM)

A library for calculating the display width of Unicode strings in terminal/monospace environments.

## Installation

```bash
npm install unicode-width-approximation
```

## Usage

```javascript
import {
    getStringWidth,
    getCodepointWidth,
    isWideChar,
    isZeroWidth
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

## TypeScript

TypeScript type definitions are included.

```typescript
import { getStringWidth, getCodepointWidth } from "unicode-width-approximation";

const width: number = getStringWidth("hello世界");
console.log(width);  // 9
```

## API

### `getStringWidth(s: string): number`

Calculate the total display width of a string.

### `getCodepointWidth(code: number): number`

Get the display width of a single Unicode code point (0, 1, or 2).

### `isWideChar(code: number): boolean`

Check if a code point is a wide character (East Asian Wide or Fullwidth).

### `isZeroWidth(code: number): boolean`

Check if a code point is a zero-width character.

## Building

Requires [Emscripten](https://emscripten.org/) to be installed.

```bash
npm run build
```

## Testing

```bash
npm test
```

## License

MIT License
