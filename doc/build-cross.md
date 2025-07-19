# Cross-Compiling Crystal Bitoreum Core

**Crystal Bitoreum Core** can be cross-compiled on Linux to multiple target systems using the `depends` build system and appropriate `HOST` targets.

---

## Windows 64-bit Cross-Compilation

### Install Toolchain

```bash
sudo apt update
sudo apt upgrade
sudo apt install build-essential libtool autotools-dev automake pkg-config bsdmainutils curl git python3 cmake
sudo apt install g++-mingw-w64-x86-64 nsis
```

Ubuntu 18.04 only:

```bash
sudo update-alternatives --config x86_64-w64-mingw32-g++  # Choose posix
```

### Notes for WSL

WSL builds **must not** run from `/mnt/c/`, `/mnt/d/`, etc. Use `/home/` or `/usr/src/`.

### Build Steps

```bash
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')  # Strip imported Windows paths
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make
```

> Optional: Run `make deploy` to create the installer using NSIS.

---

## Linux ARM Cross-Compilation

### Install Toolchain

```bash
sudo apt-get install g++-arm-linux-gnueabihf
```

### Build for ARM32

```bash
cd depends
make HOST=arm-linux-gnueabihf -j$(nproc)
cd ..
./autogen.sh
./configure --prefix=$(pwd)/depends/arm-linux-gnueabihf
make
```

### Build for ARM64

```bash
sudo apt-get install g++-aarch64-linux-gnu

cd depends
make HOST=aarch64-linux-gnu -j$(nproc)
cd ..
./autogen.sh
./configure --prefix=$(pwd)/depends/aarch64-linux-gnu --host=aarch64-linux-gnu
make
```

---

## Depends System

See [depends/README.md](../depends/README.md) for full documentation on how the build system works and how to add or customize packages.

---

## Footnotes

<sup>1</sup> Starting with Ubuntu 16.04, the `mingw-w64` toolchain includes both **posix** and **win32** threading options.  
Crystal Bitoreum **requires the posix variant** due to incompatibility between `win32` threads and the C++11 `std::mutex` class.

---

Want builds for macOS ARM, Raspberry Pi, or other embedded targets? Add the correct `HOST` triplet and dependencies!
