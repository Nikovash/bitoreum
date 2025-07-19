# Crystal Bitoreum Core Wallet Release v4.1.0.0
---

Release is now available from:

<https://github.com/Nikovash/bitoreum/releases/tag/v4.1.0.0>

This is a new major version release, bringing new features, various bugfixes and other improvements.

This release is mandatory for all wallets, nodes and smartnodes

Please report bugs using the issue tracker at github:

<https://github.com/Nikovash/bitoreum/issues>

## Version Over Version Changes

Core Wallet
- Enables Realtime Smartnode Scaling
- Seperate logging
- Updates Core Documents To Be Relective Of Modern OS's
- Added new collateral milestone 2000000 BTRM @ blockheight 842000
 
## GitHub

- Trimmed branches to be reflective of development & release paths

## Workflows

- Added v4.x to Github Actions
- Corrected Windows Workflows
- Corrected Versioning logic to prevent mismatch version numbers on builds

## Seeds

- chainparamseeds have been updated 

## Version Naming

New Version system determined for future releases<br />
Current Scheme:

**[A].[B].[C].[D]**

**A** = Super Major Update<br />
**B** = Major Update<br />
**C** = Feature Update<br />
**D** = Patch<br />

Starting with next release we are changing to a new scheme that more reflects our progress to move away from Raptoreums codebase<br />
Future Scheme:

**[A].[B].[C].[D]**

**A** = BTRM Major Update<br />
**B** = DASH Upstream Major Version Number<br />
**C** = Critical Update<br />
**D** = Feature Update/Patch<br />

EXAMPLE: **4.17.1.0**

**4** = 4th Major Iteration of BTRM<br />
**17** = Dash v17 would be the upstream<br />
**1** = Critical update 1st of this series<br />
**0** = Not a patch or a fix to the **critical update**<br />

For Developer Previews (**DP**), or Release Candidates (**RC**) these could be strung to the feature/patch number OR just a release tag this determination has yet to be resovled. This is just a way for someone to determine at what level of the software are you using.

---
### Footnotes
---
The **Crystal**, in Crystal Bitoreum is an in-house distinction used to differentiate the original Core Wallet 
and developers, from the new Core Wallet and developers. The coins naming conventions **Bitoreum** and coin call
symbol, **$BTRM**, have remained the same.
