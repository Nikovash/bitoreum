# Contributing to Crystal Bitoreum Core

Crystal Bitoreum Core welcomes contributions from everyone — whether you're reviewing code, fixing bugs, writing documentation, or submitting patches.

We operate under an open contributor model. This means **no one has special privileges**: trust is earned through consistent, quality contributions. However, some hierarchy exists for practical purposes — with designated maintainers responsible for merging PRs and managing releases.

---

## Contributor Workflow

1. **Fork the repository**  
2. **Create a new branch** for your feature or fix  
3. **Make atomic commits** — separate formatting/code moves from logic changes  
4. **Write clear commit messages** with a short subject (max 50 chars) and detailed body  
5. **Push to your fork**  
6. **Create a pull request (PR)**  

Follow our [developer notes](doc/developer-notes.md) and refer to the [Git manual](https://git-scm.com/doc) if needed.

### Commit Message Tips

- Use `fixes #123` to auto-close issues.
- Prefix PR titles with area tags like:

| Tag | Description |
|------|-------------|
| `Consensus:` | Changes to consensus rules |
| `Docs:` | Documentation |
| `Qt:` | GUI changes |
| `Net:` or `P2P:` | Networking |
| `RPC/REST/ZMQ:` | API-related |
| `Tests:` | Unit/functional/QA tests |
| `Wallet:` | Wallet logic |
| `Trivial:` | Whitespace, typo, etc. |

---

## Feature Contributions

Please evaluate long-term impact and maintenance costs. If you're adding a feature, be prepared to maintain it. Orphaned features risk eventual removal.

---

## Refactoring

Keep refactors clean and scoped:

- **No behavioral changes**
- Separate code moves, formatting, and logic
- Keep them easy to review

---

## Pull Request Process

- Submit **focused PRs** — one purpose per PR
- Add WIP or task lists if it's not ready
- Use rich descriptions, links to related issues or discussions
- Address reviewer feedback with additional commits

### Squashing Commits

Before merge, you may be asked to squash:

```bash
git rebase -i HEAD~n
# mark all but the first commit as squash
# refine commit message
git push -f
```

You may also allow "edits from maintainers" to let maintainers help squash.

---

## Review Expectations

Peer review is vital. PRs require multiple ACKs from experienced contributors before merging. Use:

- `ACK` – tested and approved
- `utACK` – code looks good, untested
- `NACK` – opposed, with reason
- `Concept ACK` – agrees with idea
- `Nit` – small, non-blocking suggestion

Reviews should mention the commit hash reviewed.

---

## Critical Code

Changes to **consensus code** or **protocol rules** require:

- Thorough discussions
- Council of the `N9ne` Agreement
- Often a BIP (Bitoreum Improvement Proposal)
- High review standard

---

## Testing

- Write unit tests where possible
- `make check` runs unit tests
- `test/functional/test_runner.py` for functional tests

All tests must pass before merging.

---

## Finding Reviewers

If your PR is overlooked:

- Check if it’s during a feature freeze
- Ask for feedback on Discord or the forum
- Use `git blame` to find previous authors and ping respectfully
- Be patient, and return the favor by reviewing others’ work

---

## Release Policy

Releases are managed by the project lead, Currently Ramen Wukong

---

## License

By contributing, you agree to license your code under the [MIT License](https://opensource.org/licenses/MIT), unless otherwise noted.

Non-original code must retain its original license and attribution.

---

Let’s build something resilient and transparent — together.