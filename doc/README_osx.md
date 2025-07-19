# Deterministic macOS DMG Notes

Working macOS DMGs are created in **Linux** by combining a recent `clang`, Apple’s binutils (`ld`, `ar`, etc.), and DMG authoring tools.

Apple uses `clang` extensively and has upstreamed the necessary functionality so that a standard `clang` installation supports key options like `-F`, `-target`, `-mmacosx-version-min`, and `--sysroot`—all required when building for macOS.

Apple's version of binutils (called **cctools**) includes functionality missing from the FSF’s version. In addition to extra linker support for frameworks and sysroots, other macOS-specific tools such as `install_name_tool`, `lipo`, and `nmedit` are also required. These do not natively build under Linux and must be patched. The following project provided a starting point for these patches:  
[mingwandroid/toolchain4](https://github.com/mingwandroid/toolchain4)

To build a working toolchain, the following Apple source packages are needed:

- `cctools`
- `dyld`
- `ld64`

By default, these tools inject timestamps, which breaks deterministic builds. You can prevent this by setting:

```bash
export ZERO_AR_DATE=1
```

This patched version of `cctools` uses `clang`'s headers and `libLTO.so` (not LLVM-GCC), improving compatibility with newer toolchains.

---

## Apple SDK Requirement

All builds must target a specific Apple SDK, which is not redistributable but can be freely downloaded with a free Apple Developer account.

Download [Xcode 7.3.1](https://developer.apple.com/devcenter/download.action?path=/Developer_Tools/Xcode_7.3.1/Xcode_7.3.1.dmg)

You only need:

```
Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk
```

---

## Extracting the SDK on macOS

```bash
hdiutil attach Xcode_7.3.1.dmg
tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.11.sdk.tar.gz MacOSX10.11.sdk
```

---

## Extracting the SDK on Linux

Linux tools like `7z`, `hpmount`, and loopback mount generally fail with modern DMG formats. Instead, use:

```bash
sudo apt-get install p7zip-full sleuthkit
contrib/macdeploy/extract-osx-sdk.sh
rm -rf 5.hfs MacOSX10.11.sdk
```

Ensure the `.dmg` file is in the current directory when running the script.

---

## Gitian Build Process Overview

Gitian builds two sets of files:

1. Linux-based macOS build tools
2. macOS binaries created using those tools

Intermediate `.tar.gz` files are deterministic and safe to redistribute. SDK files are excluded from Gitian outputs.

---

## DMG Creation Tools

- **`genisoimage`** is used to generate the initial DMG. It is not deterministic by default and must be patched to ensure consistent file ordering.
  - Patch: [theuni/osx-cross-depends](https://raw.githubusercontent.com/theuni/osx-cross-depends/master/patches/cdrtools/genisoimage.diff)
  - Note: Patch may cause memory leaks but is used in a single execution.

- **`dmg`** from the `libdmg-hfsplus` project is used for compressing the DMG.
  - Fork with fixes: [theuni/libdmg-hfsplus](https://github.com/theuni/libdmg-hfsplus)
  - Only compression is used; creation is broken and unused.

---

## DMG Appearance Customization

Backgrounds and other visual features can be added by embedding a `.DS_Store` file before final compression.

Generate one using:

```bash
contrib/macdeploy/custom_dsstore.py
```

---

## Code Signing and Gatekeeper Compliance

Since macOS Mavericks (10.9), Gatekeeper enforces Apple-blessed code signatures.

To preserve build determinism despite needing a private Apple key:

1. **Builders** run Gitian to create an unsigned DMG and `.tar.gz` containing the full app structure and prebuilt tools.
2. **Apple keyholders** generate detached signatures using a provided script.
   - Signatures repository: [bitcoin-core/bitcoin-detached-sigs](https://github.com/bitcoin-core/bitcoin-detached-sigs)
3. **Builders** feed the app + detached sigs into Gitian to finalize a deterministic DMG.
