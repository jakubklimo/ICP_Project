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

## Controls

| Key   | Description                                      |
|-------|--------------------------------------------------|
| F     | Toggles fullscreen mode                          |
| V     | Enables/disables vertical synchronization (VSync)|
| ESC   | Closes the application                           |
| P     | Takes a screenshot of the window                 |
| M     | Enables/disables MSAA (anti-aliasing)            |