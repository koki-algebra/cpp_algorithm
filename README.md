# cpp_algorithm

Competitive programming and algorithm study in C++.

## Environment

- Compiler: GCC 16 (`g++-16`)
- Standard: C++23
- Formatter: `clang-format` (config: `.clang-format`)
- LSP: `clangd`

### Setup (macOS, from scratch)

1. Xcode Command Line Tools (provides `git`, `make`, base `clang`)
   ```bash
   xcode-select --install
   ```
2. [Homebrew](https://brew.sh/)
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
3. GCC 16 (provides `g++-16`, used by `Makefile`)
   ```bash
   brew install gcc
   ```
4. clang-format (formatting; picks up `.clang-format` automatically)
   ```bash
   brew install clang-format
   ```
5. clangd (editor completion/diagnostics)
   - Xcode Command Line Tools already ships one at `/usr/bin/clangd`, or install a newer one:
   ```bash
   brew install llvm
   ```
6. Editor: install the C/C++ extension (or clangd extension) and Clang-Format extension for your editor, pointing them at the binaries installed above. `.vscode/c_cpp_properties.json` already points IntelliSense at `g++-16` with C++23.

## Usage

```bash
# Create a contest directory (a.cpp - g.cpp)
make new CONTEST=abc400

# Compile
make build FILE=abc/abc400/a

# Compile & run
make run FILE=abc/abc400/a
```

## Structure

```
cpp_algorithm/
├── template.cpp
└── abc/
    └── abc400/
        ├── a.cpp
        └── ...
```
