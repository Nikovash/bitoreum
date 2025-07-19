# Crystal Bitoreum Core Wallet Release v4.1.0.0
---

Release is now available from:

<https://github.com/Nikovash/bitoreum/releases/tag/v4.1.0.0>

This is a new major version release, bringing new features, various bugfixes and other improvements.

This release is mandatory for all wallets, nodes and smartnodes

Please report bugs using the issue tracker at github:

<https://github.com/Nikovash/bitoreum/issues>


## Version Over Version Changes
---
Core Wallet
- Enables realtime Smartnode scaling
- Seperate logging
- Updates Core Documents To Be Relective Of Modern OS's
- Added new collateral milestone 2000000 BTRM @ blockheight 842000
 
## GitHub
---
- Trimmed branches to be reflective of development & release paths

## Workflows
---
- Added v4.x to Github Actions
- Corrected Windows Workflows
- Corrected Versioning logic to preven mismatch version numbers on builds

## Seeds
---
- Chainparam seeds have been updated 

## Version Naming
---
New Version system determined for future releases
Current Scheme:

**[A].[B].[C].[D]**

**A** = Super Major Update
**B** = Major Update
**C** = Feature Update
**D** = Patch

Starting with next release we are changing to a new scheme that more reflects our progress to move away from Raptoreums codebase
Future Scheme:

**[A].[B].[C].[D]**

**A** = BTRM Major Update
**B** = DASH Upstream Major Version Number
**C** = Critical Update 
**D** = Feature/Patch

EXAMPLE: **4.17.1.0**

4th major iteration of BTRM
Dash v17 would be the upstream
1 = Critical update 1st of this series
0 = not a patch or a fix to the critical update

For Developer Previews (**DP**), or Release Candidates (**RC**) these could be strung to the feature/patch number OR just a release tag this determination has yet to be resovled. This is just a way for someone to determine at what level of the software are you using.

### Footnotes
---
The Crystal, in Crystal Bitoreum is an inhouse distinction used to differentiate the original Core Wallet 
and developers, from the new Core Wallet and developers. The coins naming conventions Bitoreum and coin call
symbol, $BTRM, have remained the same.
