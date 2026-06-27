# Crystal Bitoreum 4.1.1.99 Development Build Notes

## Overview

Version **4.1.1.99** is a **development build** of Crystal Bitoreum created during the ongoing modernization and C++17 migration effort.

This build serves as a development checkpoint and validation release intended to verify cross-platform build stability, GitHub Actions workflow compatibility, and ongoing source modernization before changes are merged into the primary development branch.

The `.99` suffix designates this as a development build and not a production release.

## Major Development Milestones

### Codex Branch Rebase and Synchronization

- Rebased the Codex development branch onto the current development codebase
- Resolved merge and integration issues introduced during branch synchronization
- Established a clean development baseline for future modernization work
- Preserved compatibility with existing network, wallet, smartnode, and consensus functionality
- Will push into a locked state branch called `dev-a`

### C++17 Migration Progress

- Modernized build configuration for contemporary compiler toolchains
- Resolved multiple compatibility issues exposed by newer Clang and GCC versions
- Updated project configuration to successfully build under modern C++17 environments
- Identified and corrected legacy compatibility assumptions inherited from upstream code
- Established a working baseline for future Boost replacement efforts

## macOS Build System Modernization

### Completed

- Successfully restored GitHub Actions macOS build functionality.
- Validated builds targeting:
  - macOS 12 compatibility target (x86_64-apple-darwin21)
  - macOS 13 compatibility target (x86_64-apple-darwin22)
  - macOS 15 compatibility target (x86_64-apple-darwin24)
- Updated workflow logic for modern Xcode and Clang toolchains
- Corrected Qt 5.9.6 compatibility issues exposed by current Apple SDKs
- Corrected zlib build issues affecting newer macOS environments
- Resolved Boost thread detection failures during configure validation
- Implemented compatibility workarounds required for std::unary_function removal and modern Clang diagnostics
- Verified successful generation of GUI binaries, DMG packages, and release archives

## GitHub Actions and CI Improvements

- Updated development workflows for modern GitHub Actions environments
- Improved compatibility with GitHub's upcoming JavaScript runtime migration
- Refined build validation and diagnostic reporting
- Standardized macOS build workflows across supported target versions
- Simplified workflow logic after successful troubleshooting and validation

### Validation Results

**Successfully validated:**
- Linux development builds
- WinTel CI builds
- macOS CI builds
- Artifact packaging
- DMG generation
- Release archive generation

## Dependency and Build System Work

### Qt

- Updated and validated Qt 5.9.6 build process on modern systems
- Corrected compatibility issues affecting newer compilers and SDKs
- Validated successful GUI application builds

### Boost

- Identified Boost 1.70 as a long-term modernization obstacle
- Implemented temporary compatibility fixes required for modern toolchains
- Established a future migration path toward native C++17 standard library replacements

### zlib

- Corrected build and preprocessing issues affecting modern macOS environments
- Updated patch handling and validation procedures

## Qt GUI, Splash Screen, and Visual Branding Updates

### Linux Qt Scaling Compatibility

* Added Linux-specific Qt scaling normalization for the legacy Qt wallet interface
* Disabled automatic Qt high-DPI scaling by default on Linux to prevent oversized or inconsistent GUI rendering
* Added an opt-in environment variable escape hatch for users who prefer native system scaling behavior:

```bash
BITOREUM_QT_RESPECT_SYSTEM_SCALE=1 ./bitoreum-qt
```

* Preserved existing high-DPI pixmap behavior for non-Linux platforms
* Improved consistency of wallet startup rendering across modern Linux desktop environments

### Splash Screen Modernization

* Reworked the Qt splash screen layout for the Crystal Bitoreum visual identity
* Updated splash screen rendering to use the active `splash.png` asset as the primary background artwork
* Added runtime-rendered readability gradients instead of baking all text and fades into the image asset
* Added centered version display using the full development version string
* Added Bitoreum Network branding directly in the splash rendering code
* Added dynamic Crystal Bitoreum copyright year handling
* Added hosted-by branding for Ramen Wukong
* Reduced and cleaned up startup progress/status text to prevent wrapping and layout issues
* Improved splash screen readability across different desktop scaling environments

### Image and Icon Asset Refresh

* Updated Bitoreum GUI icon assets across Qt and shared pixmap resources
* Added refreshed Bitoreum pixmap assets under `share/pixmaps`
* Updated favicon and application icon files for current Bitoreum branding
* Updated macOS `.icns`, Windows/Linux `.ico`, and PNG icon resources
* Replaced the active Qt splash image with a new `960x1080` PNG asset
* Optimized the active splash PNG by removing unnecessary metadata and legacy alpha data
* Removed unused legacy splash image variants from the Qt image resource folder
* Simplified the active splash image set so the Qt resource system uses only `src/qt/res/images/splash.png`

## Source Cleanup and Validation Clarifications

### Locktime Cutoff Readability

* Clarified the locktime cutoff condition in validation logic
* Made the previous-block null check explicit in the locktime cutoff expression
* Preserved existing consensus behavior while improving code readability and intent
* Confirmed this change is not intended to alter block, transaction, wallet, or network behavior

## Additional Validation Notes

**Additional work validated during this development checkpoint:**

* Qt GUI startup rendering
* Linux splash screen scaling behavior
* Updated splash image loading through the Qt resource system
* Refreshed icon and favicon assets
* Removal of unused splash image variants
* Continued non-consensus source modernization cleanup

## Future Development Direction

The 4.1.1.99 development cycle establishes a modernized build foundation for future Crystal Bitoreum development.

**Planned areas of focus include:**
- Complete review and validation of any remaining C++17 migration issues
- Comprehensive audit of Boost usage throughout the codebase
- Incremental replacement of Boost components with native C++17 standard library alternatives
- Long-term reduction or elimination of Boost dependency requirements
- Investigation and implementation of native Apple Silicon (ARM64) build support
- Continued modernization of legacy upstream code and build infrastructure
- Evaluation and integration of relevant upstream Dash improvements where practical
- Review and modernization of Long-Living Masternode Quorum (LLMQ) implementation
- Investigation of future Qt upgrade paths and compatibility requirements
- Global ARM architecture optimization for Apple Silicon and ARM-based Linux environments
- Continued cross-platform CI/CD improvements and build validation enhancements
- Ongoing technical debt reduction and dependency modernization effortse

## Network / Protocol Notes

**This development build does not intentionally introduce:**
- Consensus changes
- Protocol changes
- Smartnode changes
- Wallet behavior changes
- Blockchain compatibility changes

## Status

**Development Build**

Version 4.1.1.99 serves as a modernization and C++17 migration milestone demonstrating successful cross-platform builds across Linux, Windows, and macOS environments.

Not intended as a production release.
