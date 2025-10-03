# macOS Build Instructions (macOS 13 x86)

These instructions will help you build the Crystal Bitoreum Core wallet manually on macOS 13+ (x86_64). Use the Terminal app: `/Applications/Utilities/Terminal.app`.

This x86_64 complie will run on Apple silicone with the Rosetta Layer

---

## Prerequisites

### 1. Install Xcode Command Line Tools

```bash
xcode-select --install
```

When prompted, confirm the installation.

### 2. Install Homebrew (if not already installed)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

---

## 📦 Install Dependencies

Install the required packages with Homebrew:

```bash
brew install automake libtool pkg-config miniupnpc librsvg libnatpmp zeromq python
```

---

## 🐍 Setup Python Virtual Environment

To avoid messing up the System's Python:

```bash
python3 -m venv venv
source venv/bin/activate
pip install --upgrade pip setuptools
pip install ds_store mac_alias
```

To exit the virtual python environment after use:

```bash
deactivate
```

---

## ⚙️ Build the Wallet

### 1. Fetch the source (if not done yet)

```bash
git clone https://github.com/Nikovash/bitoreum
cd bitoreum
```

### 2. Build Dependencies

### 🧭 macOS ↔ Darwin Version Matrix

| macOS Version | macOS Name   | Darwin Version | `--host` Triplet Example         |
|---------------|--------------|----------------|----------------------------------|
| 14.x          | Sonoma       | Darwin 23.x    | x86_64-apple-darwin23            |
| 13.x          | Ventura      | Darwin 22.x    | x86_64-apple-darwin22            |
| 12.x          | Monterey     | Darwin 21.x    | x86_64-apple-darwin21            |
| 11.x          | Big Sur      | Darwin 20.x    | x86_64-apple-darwin20            |
| 10.15         | Catalina     | Darwin 19.x    | x86_64-apple-darwin19            |
| 10.14         | Mojave       | Darwin 18.x    | x86_64-apple-darwin18            |
| 10.13         | High Sierra  | Darwin 17.x    | x86_64-apple-darwin17            |
| 10.12         | Sierra       | Darwin 16.x    | x86_64-apple-darwin16            |
| 10.11         | El Capitan   | Darwin 15.x    | x86_64-apple-darwin15            |
| 10.10         | Yosemite     | Darwin 14.x    | x86_64-apple-darwin14            |

For the purpose of these instructions we are going to target MacOS Ventura, thus darwin22; use the chart provided to target your specific OS.

```bash
make -C depends -j$(sysctl -n hw.ncpu) HOST=x86_64-apple-darwin22
```

### 3. Configure the build

```bash
./autogen.sh
./configure --prefix=$(pwd)/depends/x86_64-apple-darwin22
```

### 4. Build Binaries

```bash
make -j$(sysctl -n hw.ncpu)
```

### 5. Optional: Create `.dmg` Installer

```bash
make deploy
```

This will generate `Bitoreum-Qt.dmg` in the project root. You can rename it:

```bash
mv Bitoreum-Qt.dmg Crystal-Bitoreum-Qt.dmg
```

---

## 🧪 Running the Daemon

### 1. Create RPC Config File

```bash
mkdir -p "$HOME/Library/Application Support/BitoreumCore"
echo -e "rpcuser=bitoreumrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "$HOME/Library/Application Support/BitoreumCore/bitoreum.conf"
chmod 600 "$HOME/Library/Application Support/BitoreumCore/bitoreum.conf"
```

### 2. Start the Daemon

```bash
./src/bitoreumd -daemon
```

### 3. Monitor Sync Progress

```bash
tail -f "$HOME/Library/Application Support/BitoreumCore/debug.log"
```

---

## 🧰 Common Commands

```bash
./src/bitoreumd -daemon                # Start the daemon
./src/bitoreum-cli --help              # List all CLI options
./src/bitoreum-cli help                # List all RPC commands (requires daemon running)
```
