# Folder Structure

## Folder Structure
**\src:** 
- **busSideChannel_lib** -> The spy BUSted code.
- **NS** -> NS world code
- **TA**  -> The victim code which will run on the S world as TF-M unpriv secure services (aka, TAs) 

## Quick Start

### 1. Enter the Development Environment

```bash
nix develop
```

This provides a reproducible shell with all required dependencies (ARM toolchain, CMake, Python packages,etc.).

> **Note**: Run `nix develop` in every new terminal session.

### 2. Build and Deploy

```bash
# Configure the build system
./0-setup_code.sh

# Compile the Secure and Non-Secure images
./1-compile.sh

# Deploy to the target board
./2-deploy.sh
```

