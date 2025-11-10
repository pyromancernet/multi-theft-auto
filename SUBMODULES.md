# Git Submodules Configuration

This project uses git submodules for external dependencies:

- `sdk/` → [mtasa-sdk](https://github.com/multitheftauto-modern/mtasa-sdk) - MTA:SA SDK headers
- `vendor/` → [mtasa-vendors](https://github.com/multitheftauto-modern/mtasa-vendors) - Third-party vendor libraries

## Initial Setup

After cloning the repository, initialize and update submodules:

```bash
git submodule init
git submodule update
```

Or clone with submodules in one step:

```bash
git clone --recursive <repository-url>
```

## Updating Submodules

To update all submodules to their latest versions:

```bash
git submodule update --remote
```

To update a specific submodule:

```bash
git submodule update --remote sdk
# or
git submodule update --remote vendor
```

## Making Changes to Submodules

1. Navigate into the submodule directory:
   ```bash
   cd sdk
   # or
   cd vendor
   ```

2. Make your changes and commit:
   ```bash
   git add .
   git commit -m "Your changes"
   git push
   ```

3. Return to the main repository and commit the submodule reference update:
   ```bash
   cd ..
   git add sdk
   # or
   git add vendor
   git commit -m "Update submodule reference"
   git push
   ```

## Important Notes

- Each submodule is an independent git repository
- Submodules track specific commits, not branches
- Always commit submodule changes before pushing the main repository
- Use `git status` in the main repository to check if submodules have uncommitted changes

## For CI/CD

Add the `--recursive` flag when cloning:

```bash
git clone --recursive https://github.com/your-org/multi-theft-auto.git
```

Or for existing clones:

```bash
git pull
git submodule update --init --recursive
```
