from pathlib import Path

DATA_DIR = Path(__file__).parent.parent / "ucd"

# East Asian Width properties determine character width
# F (Fullwidth) and W (Wide) -> width 2
# H (Halfwidth), Na (Narrow), N (Neutral), A (Ambiguous) -> width 1 (for now, A is ambiguous)
east_asian_width_properties = []

# General Category properties for zero-width characters
# Cc (Control), Cf (Format), Mn (Nonspacing Mark), Me (Enclosing Mark) -> width 0
# Zl (Line Separator), Zp (Paragraph Separator) -> width 0
zero_width_categories = []

# Emoji_Presentation properties for emoji characters (width 2)
emoji_presentation_properties = []


def parse_unicode_range(unicode_range: str):
    if ".." in unicode_range:
        start, end = unicode_range.split("..")
        return int(start, 16), int(end, 16)
    else:
        unicode = int(unicode_range, 16)
        return unicode, unicode


def add_to_eaw_properties(unicode_range: str, eaw_property: str):
    start, end = parse_unicode_range(unicode_range)
    east_asian_width_properties.append((start, end, eaw_property))


def add_to_zero_width_categories(unicode_range: str, category: str):
    start, end = parse_unicode_range(unicode_range)
    zero_width_categories.append((start, end, category))


def add_to_emoji_presentation(unicode_range: str, prop: str):
    start, end = parse_unicode_range(unicode_range)
    emoji_presentation_properties.append((start, end, prop))


def compress_properties(properties, name):
    properties.sort()
    for i in range(len(properties) - 1):
        if properties[i][1] >= properties[i + 1][0]:
            print(f"Overlap: {properties[i]} and {properties[i + 1]}")
    print(f"# {name}: {len(properties)}")
    n, m = len(properties), 1
    for i in range(1, n):
        if (
            properties[m - 1][1] + 1 == properties[i][0]
            and properties[m - 1][2] == properties[i][2]
        ):
            properties[m - 1] = (
                properties[m - 1][0],
                properties[i][1],
                properties[m - 1][2],
            )
        else:
            properties[m] = properties[i]
            m += 1
    del properties[m:]
    print(f"# {name} (compressed): {len(properties)}")


def generate_codes():
    codes = ""

    # East Asian Width Properties (for width 2 characters: F and W)
    wide_props = [(s, e, p) for s, e, p in east_asian_width_properties if p in ("F", "W")]
    codes += f"static constexpr int NUM_WIDE_CHAR_RANGES = {len(wide_props)};\n\n"
    codes += "static const std::int32_t WIDE_CHAR_RANGES[] = {\n"
    for i, (start, end, _) in enumerate(wide_props):
        if i != 0 and i % 5 == 0:
            codes += "\n"
        if i % 5 == 0:
            codes += "    "
        codes += f"0x{start:04X}, 0x{end:04X}, "
    codes += "\n};\n\n"

    # Zero Width Categories
    codes += f"static constexpr int NUM_ZERO_WIDTH_RANGES = {len(zero_width_categories)};\n\n"
    codes += "static const std::int32_t ZERO_WIDTH_RANGES[] = {\n"
    for i, (start, end, _) in enumerate(zero_width_categories):
        if i != 0 and i % 5 == 0:
            codes += "\n"
        if i % 5 == 0:
            codes += "    "
        codes += f"0x{start:04X}, 0x{end:04X}, "
    codes += "\n};\n\n"

    # Emoji Presentation Properties
    codes += f"static constexpr int NUM_EMOJI_PRESENTATION_RANGES = {len(emoji_presentation_properties)};\n\n"
    codes += "static const std::int32_t EMOJI_PRESENTATION_RANGES[] = {\n"
    for i, (start, end, _) in enumerate(emoji_presentation_properties):
        if i != 0 and i % 5 == 0:
            codes += "\n"
        if i % 5 == 0:
            codes += "    "
        codes += f"0x{start:04X}, 0x{end:04X}, "
    codes += "\n};\n"

    with open(DATA_DIR / "_width_properties.cpp", "w") as f:
        f.write(codes)


def main():
    # Parse EastAsianWidth.txt
    with open(DATA_DIR / "EastAsianWidth.txt") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            unicode_range, prop = line.split(";", 1)
            unicode_range = unicode_range.strip()
            prop = prop.split("#")[0].strip()
            add_to_eaw_properties(unicode_range, prop)

    # Parse DerivedGeneralCategory.txt for zero-width categories
    # Zero-width: Cc (Control), Cf (Format), Mn (Nonspacing Mark), Me (Enclosing Mark)
    # Also Zl (Line Separator), Zp (Paragraph Separator)
    zero_width_cats = {"Cc", "Cf", "Mn", "Me", "Zl", "Zp"}
    with open(DATA_DIR / "DerivedGeneralCategory.txt") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split(";", 1)
            if len(parts) < 2:
                continue
            unicode_range = parts[0].strip()
            prop = parts[1].split("#")[0].strip()
            if prop in zero_width_cats:
                add_to_zero_width_categories(unicode_range, prop)

    # Parse emoji-data.txt for Emoji_Presentation characters
    with open(DATA_DIR / "emoji-data.txt") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split(";", 1)
            if len(parts) < 2:
                continue
            unicode_range = parts[0].strip()
            prop = parts[1].split("#")[0].strip()
            if prop == "Emoji_Presentation":
                add_to_emoji_presentation(unicode_range, prop)

    compress_properties(east_asian_width_properties, "East Asian Width Properties")
    compress_properties(zero_width_categories, "Zero Width Categories")
    compress_properties(emoji_presentation_properties, "Emoji Presentation Properties")
    generate_codes()


if __name__ == "__main__":
    main()
