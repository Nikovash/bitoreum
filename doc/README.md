# Crystal Bitoreum Core

This is the official reference wallet for **Crystal Bitoreum** digital currency and comprises the backbone of the Crystal Bitoreum peer-to-peer network. You can [download Crystal Bitoreum Core](https://www.bitoreum.org/downloads/) <!-- TODO: Replace with official Crystal Bitoreum download link --> or [build it yourself](#building) using the guides below.

## Running

The following are some helpful notes on how to run Crystal Bitoreum on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/bitoreum-qt` (GUI) or
- `bin/bitoreumd` (headless)

### Windows

Unpack the files into a directory, and then run `bitoreum-qt.exe`.

### macOS

Drag `Bitoreum-Qt` to your Applications folder, and then run `Bitoreum-Qt`.

### Need Help?

* See the [Crystal Bitoreum documentation](https://docs.bitoreum.org) <!-- TODO: Replace with Crystal Bitoreum doc site -->
* See the [Crystal Bitoreum Developer Documentation](https://bitoreum-docs.github.io/) <!-- TODO: Replace with Crystal Bitoreum developer doc site -->
* Ask for help on [Crystal Bitoreum Nation Discord](http://bitoreumchat.org) <!-- TODO: Update if a new Discord exists -->
* Ask for help on the [Crystal Bitoreum Forum](https://bitoreum.org/forum) <!-- TODO: Replace with official Crystal Bitoreum forum -->

## Building

The following are developer notes on how to build Crystal Bitoreum Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [macOS Build Notes](build-macos.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

## Development

The Crystal Bitoreum Core repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- Source Code Documentation <!-- TODO: Add link -->
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources

* Discuss on the [Crystal Bitoreum Forum](https://bitoreum.org/forum) <!-- TODO: Replace with official Crystal Bitoreum forum -->
* Discuss on [Crystal Bitoreum Nation Discord](http://bitoreumchat.org) <!-- TODO: Update if a new Discord exists -->

### Miscellaneous

- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

## License

Distributed under the [MIT software license](/COPYING).  
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
