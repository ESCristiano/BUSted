# BUSted

This repository consolidates all artifacts related to the paper "BUSted!!! Microarchitectural Side-Channel Attacks on the MCU Bus Interconnect," accepted at IEEE S&P 2024. For more details about the attack, please visit our dedicated [website](https://bustedattack.com/), where all relevant documentation is centralized.

## Repo Structure 


**DMA-Covert-Channel**
- `Results`: Covert-channel measurements, including channel capacity.
- `src`: Source code for the covert-channel.
- `capacity.sh`: Script to automate the measurement of channel capacity.

**PoC-TF-M**
- `TF-M`: TF-M source code used as the Secure World firmware (v1.4).
- `TF_M_dma_side_channel` ([see](./PoC-TF-M/TF_M_dma_side_channel/README.md)): Source code for the smart lock attack on STM32L552 with TF-M.
- `Hardware`: Wiring instructions for the keypad used in the attack ([see](./PoC-TF-M/Hardware/README.md)).

**tools**
- `heatmap.py`: Tool for plotting the channel matrix ([example](./DMA-Covert-Channel/README.md#3---results)).
- `profile.py`: Tool for obtaining the pruned matrix from a victim trace.

## Prerequisites

### 1. Install Nix Package Manager

The development environment uses Nix for reproducible builds. Install Nix and add your user to the `nix-users` group:

```bash
sh <(curl --proto '=https' --tlsv1.2 -L https://nixos.org/nix/install) --no-daemon
```

Enable experimental features by adding to `~/.config/nix/nix.conf` or `/etc/nix/nix.conf`:

```
experimental-features = nix-command flakes
```

### 2. Install STM32 Programmer

Download and install [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) (requires ST account).

Verify installation:
```bash
STM32_Programmer_CLI --version
```

Ensure `STM32_Programmer_CLI` is in your `PATH`.

### 3. Configure USB Permissions (udev Rules)

Create `/etc/udev/rules.d/99-stlink.rules` with the following content:

```
# ST-LINK V3 (STM32L5 Discovery / Nucleo)
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374e", MODE="0666", GROUP="plugdev"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b", MODE="0666", GROUP="plugdev"
```

Reload udev rules:
```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

> **Note**: Without these rules, `sudo` is required for every deployment.

## Covert-Channels

The repository includes covert-channel [data](./DMA-Covert-Channel) for the 11 tested MCUs and a [trace](./tools/data.txt) from the Smart Lock application (our victim). We also provide the necessary [tools](./tools/README.md) to replicate the experiments and support further research.

The channel capacities were measured using the leakiEst tool ([Credits](#credits)). In the [DMA-Covert-Channel](./DMA-Covert-Channel/README.md) folder, you will find the `capacity.sh` script, which automates tool execution and extracts channel-capacity measurements.

## BUSted Attack

### 1. Enter the Development Environment

```bash
nix develop
```

This provides a reproducible shell with all required dependencies (ARM toolchain, CMake, Python packages, etc.).

> **Note**: Run `nix develop` in every new terminal session.

### 2. Build and Deploy

```bash
# Go to TF_M_dma_side_channel
cd ./PoC-TF-M/TF_M_dma_side_channel

# Configure the build system
./0_setup_code.sh

# Compile the Secure and Non-Secure images
./1_compile.sh

# Deploy to the target board
./2_deploy.sh
```

## Credits

Channel capacity was measured using the leakiEst tool, developed by researchers from the University of Birmingham. For more information, please visit the [leakiEst site](https://www.cs.bham.ac.uk/research/projects/infotools/leakiest/#:~:text=leakiEst%20%E2%80%94%20Tool%20for%20%22Leaking%20information%20Estimation%22.,insecure%20system%20with%20a%20very%20small%20information).

## Cite the paper 

If you find this information useful, please consider citing our work.

```latex
@INPROCEEDINGS{BUSted,
    author = {C. Rodrigues and D. Oliveira and S. Pinto},
    title = {BUSted!!! Microarchitectural Side-Channel Attacks on the MCU Bus Interconnect},
    booktitle = {2024 IEEE Symposium on Security and Privacy (SP)},
    year = {2024}
}
```
