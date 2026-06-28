# cicd-0112358

![CI](https://github.com/YOUR_USERNAME/cicd-0112358/actions/workflows/ci.yml/badge.svg?branch=main)

A C++17 project demonstrating a CI pipeline with CMake, Conan 2, and GitHub Actions.

## What this repo shows

- **Pull requests with CI pipeline invocation** - pushes to `main` are forbidden by branch rules; every PR requires the CI to pass before merging
- **Auto-formatting** - `clang-format` runs on every PR and commits style fixes back automatically
- **Static analysis** - `clang-tidy` with `WarningsAsErrors` and a curated check profile, run after formatting
- **Cross-platform build & test** - matrix across `ubuntu-latest` and `windows-latest`, using Conan 2 for dependency management (GTest 1.14), CMake + Ninja, and CTest
- **Dependency caching** - Conan package cache keyed on `conanfile.txt` to keep CI fast

## Project structure

```
include/   fibonacci.h                      - public API
src/       fibonacci.cpp                    - iterative implementation
tests/     test_fibonacci.cpp               - GTest unit tests
examples/  fibonacci_hello_world/main.cpp   - A basic example of usage
```

## Building locally

### Windows

```powershell
# First time only — skip the next 2 lines if you already have Conan installed and configured
pip install "conan>=2.0,<3"
conan profile detect --force

.\run_conan_install.ps1

cmake -B build -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=out/conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release
# Or use IDE configuration tools instead
```

Pass `-Force` to `run_conan_install.ps1` to rebuild all Conan packages from source.

### Linux

```bash
# First time only — skip the next 2 lines if you already have Conan installed and configured
pip install "conan>=2.0,<3"
conan profile detect --force
conan install . --build=missing -s build_type=Release -s compiler.cppstd=17 \
    -c tools.cmake.cmaketoolchain:generator=Ninja --output-folder out/conan
cmake --preset conan-release -DBUILD_TESTING=ON
cmake --build --preset conan-release
ctest --preset conan-release
```

---

Black

Then

White are

All I see

In my infancy

Red and yellow then came to be

Reaching out to me

Lets me see

As below so above and beyond I imagine

Drawn beyond the lines of reason

Push the envelope

Watch it bend
