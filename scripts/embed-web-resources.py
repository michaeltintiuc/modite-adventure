"""Build a portable version of Creative Engine's embedded resource manager."""

import sys
from pathlib import Path
from zipfile import ZipFile


def main():
    archive_path, engine_source, output_dir = map(Path, sys.argv[1:])
    source = engine_source.read_text(encoding="utf-8")
    start = source.find("// TODO: should application incbin the resources binary?")
    end = source.find("struct BitmapSlot", start)
    if start < 0 or end < 0:
        raise SystemExit("Unsupported Creative Engine resource manager layout")

    with ZipFile(archive_path) as archive:
        (output_dir / "Resources.h").write_bytes(archive.read("Resources.h"))
        resources = archive.read("Resources.bin")

    # WebAssembly cannot assemble the native .incbin block.
    with (output_dir / engine_source.name).open("w", encoding="utf-8") as output:
        output.write(source[:start])
        output.write("alignas(16) static TUint8 resources[] = {\n")
        for offset in range(0, len(resources), 32):
            output.write(",".join(map(str, resources[offset:offset + 32])) + ",\n")
        output.write("};\nBResourceManager gResourceManager(resources);\n\n")
        output.write(source[end:])


if __name__ == "__main__":
    main()
