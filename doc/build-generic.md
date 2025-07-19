# Crystal Bitoreum Core: Generic Build Notes

These instructions explain how to build **Crystal Bitoreum Core** using the modern `depends` system.

---

## Deprecation Notice

Old instructions that relied on system-wide dependencies (like Berkeley DB, Boost, Qt) are deprecated.  
The **only supported method** is to use the `depends` build system and compile with the appropriate `--prefix`.

---

## Required Tools

Ensure that your system has all build tools installed before continuing.  
Refer to platform-specific setup in:

- [Linux Build Notes](Linux-build.md)
- [macOS Build Notes](build-macos.md)
- [Windows Build Notes](build-windows.md)

---

## Building Dependencies

Crystal Bitoreum Core uses a standalone `depends/` system (inherited from Bitcoin) to manage its full build environment.

```bash
cd depends
make -j$(nproc)  # Use appropriate -j based on core count
cd ..
```

This will:
- Download all required source packages
- Build fully self-contained versions
- Cache built components to avoid rebuilding unchanged parts

Re-run this periodically if dependencies change or builds fail.

For advanced info, see [`depends/README.md`](../depends/README.md)

---

## Building Crystal Bitoreum Core

Once dependencies are built:

```bash
./autogen.sh
./configure --prefix=$(pwd)/depends/<host>
make
make install  # optional
```

Replace `<host>` with your platform’s triplet:

| Platform           | Triplet                     |
|--------------------|-----------------------------|
| Linux 64-bit       | `x86_64-pc-linux-gnu`       |
| Linux 32-bit       | `i686-pc-linux-gnu`         |
| Windows 64-bit     | `x86_64-w64-mingw32`        |
| Windows 32-bit     | `i686-w64-mingw32`          |
| macOS              | `x86_64-apple-darwin22`     |
| Linux ARM 32-bit   | `arm-linux-gnueabihf`       |
| Linux ARM 64-bit   | `aarch64-linux-gnu`         |

For cross-compilation:  
- Build dependencies with the **same** `<host>` triplet.
- Use `--host=<triplet>` when configuring.

For distro compatibility across libc versions:

```bash
./configure --enable-glibc-back-compat
```

---

## Using `ccache` for Faster Builds

If installed, `./configure` will detect and use [ccache](https://ccache.dev/) automatically.  
To disable:

```bash
./configure --disable-ccache
```

Recommended: Increase default cache size:

```bash
ccache -M 20G
```

---

## Additional Flags

View all configuration options with:

```bash
./configure --help
```

---

This guide ensures consistent and isolated builds using the `depends` system—essential for reproducibility and cross-platform deployment.
