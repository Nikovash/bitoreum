# Crystal Bitoreum Core v4.1.0.1 "Greeley" Release Notes

## Overview

Version **v4.1.0.1**, codenamed **"Greeley"**, is a Crystal Bitoreum Core patch release for the **v4.1.0.x "Portland"** release series.

The **"Greeley"** release builds on **v4.1.0.0 "Portland"** and focuses on build modernization, C++17 compatibility, GitHub Actions workflow stability, and refreshed graphical branding assets.

This release promotes the modernization work previously validated during the `4.1.1.99` development cycle into a tagged production patch release.

The primary goals of this release are:

* Improve cross-platform build reliability
* Continue the C++17 migration path
* Refresh Qt GUI, splash screen, icon, and packaging assets
* Improve compatibility with modern compiler toolchains
* Preserve existing network, wallet, smartnode, and consensus behavior

This release is not intended to introduce consensus, protocol, smartnode, wallet, or blockchain compatibility changes.


## Major Release Highlights

### Codex Branch Synchronization

* Synchronized the Codex development branch with the current Crystal Bitoreum codebase
* Resolved merge and integration issues introduced during modernization work
* Established a clean release baseline for the v4.1.0.1 tag
* Preserved compatibility with existing network, wallet, smartnode, and consensus functionality
* Prepared the current Codex workstream for continued post-release development

### C++17 Migration Progress

* Modernized build configuration for contemporary compiler toolchains
* Resolved multiple compatibility issues exposed by newer Clang and GCC versions
* Updated project configuration to successfully build under modern C++17 environments
* Identified and corrected legacy compatibility assumptions inherited from upstream code
* Established a working baseline for future Boost reduction and replacement work

## macOS Build System Modernization

### Completed

* Restored GitHub Actions macOS build functionality
* Updated workflow logic for modern Xcode and Clang toolchains
* Corrected Qt 5.9.6 compatibility issues exposed by current Apple SDKs
* Corrected zlib build issues affecting newer macOS environments
* Resolved Boost thread detection failures during configure validation
* Implemented compatibility workarounds required for `std::unary_function` removal and modern Clang diagnostics
* Verified successful generation of GUI binaries, DMG packages, and release archives
* Continued validation of Darwin compatibility targets used for older macOS release support where applicable

## GitHub Actions and CI Improvements

* Updated release and development workflows for modern GitHub Actions environments
* Improved compatibility with GitHub's JavaScript runtime migration
* Refined build validation and diagnostic reporting
* Standardized macOS build workflow behavior across supported targets
* Simplified workflow logic after successful troubleshooting and validation
* Improved artifact packaging consistency for release builds

### Validation Results

Successfully validated during this release cycle:

* Linux development and release builds
* Windows / MinGW CI builds
* macOS CI builds
* Qt GUI artifact generation
* DMG generation
* Release archive generation
* Packaged application icon handling
* Cross-platform build artifact output

## Dependency and Build System Work

### Qt

* Updated and validated the Qt 5.9.6 build process on modern systems
* Corrected compatibility issues affecting newer compilers and SDKs
* Validated successful GUI application builds
* Improved Qt resource handling for splash screen and icon assets

### Boost

* Identified Boost 1.70 as a long-term modernization obstacle
* Implemented temporary compatibility fixes required for modern toolchains
* Established a future migration path toward native C++17 standard library replacements

### zlib

* Corrected build and preprocessing issues affecting modern macOS environments
* Updated patch handling and validation procedures
* Improved compatibility with newer Apple SDK and Clang environments

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
* Added centered version display using the active release version string
* Added Bitoreum Network branding directly in the splash rendering code
* Added dynamic Crystal Bitoreum copyright year handling
* Added hosted-by branding for Ramen Wukong
* Reduced and cleaned up startup progress and status text to prevent wrapping and layout issues
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

Additional work validated during this release cycle:

* Qt GUI startup rendering
* Linux splash screen scaling behavior
* Updated splash image loading through the Qt resource system
* Refreshed icon and favicon assets
* Removal of unused splash image variants
* Continued non-consensus source modernization cleanup
* Release artifact generation from the updated visual asset set

## Network / Protocol Notes

This release does **not** intentionally introduce:

* Consensus changes
* Protocol changes
* Smartnode changes
* Wallet behavior changes
* Blockchain compatibility changes

Existing compatible nodes, wallets, smartnodes, and services should not require any blockchain migration or reindex solely because of this release.

## Future Development Direction

The v4.1.0.1 release establishes a stronger modernized build foundation for future Crystal Bitoreum development.

Planned areas of focus include:

* Continued review and validation of remaining C++17 migration issues
* Comprehensive audit of Boost usage throughout the codebase
* Incremental replacement of Boost components with native C++17 standard library alternatives
* Long-term reduction or elimination of Boost dependency requirements
* Investigation and implementation of native Apple Silicon ARM64 build support
* Continued modernization of legacy upstream code and build infrastructure
* Evaluation and integration of relevant upstream Dash improvements where practical
* Review and modernization of Long-Living Masternode Quorum implementation
* Investigation of future Qt upgrade paths and compatibility requirements
* Global ARM architecture optimization for Apple Silicon and ARM-based Linux environments
* Continued cross-platform CI/CD improvements and build validation enhancements
* Ongoing technical debt reduction and dependency modernization efforts

## Status

**Release Build**

Version **v4.1.0.1 "Greeley"** is a tagged Crystal Bitoreum Core production patch release in the **v4.1.0.x "Portland"** release series.

This release is built from the modernization, C++17 compatibility, CI, and graphical asset work completed during the previous development cycle.

This release does not intentionally alter consensus, protocol, wallet, smartnode, or blockchain compatibility behavior.
