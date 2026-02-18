# ICP_Semestral

## Clean, build, run

### Clean

```bash
rm -rf build
```

### Build

**MacOS**
```bash
cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts buildsystems/vcpkg.cmake"

cmake --build build -j
```
### Run

```bash
./build/app
```