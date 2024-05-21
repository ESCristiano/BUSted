# BUSted

This repository consolidates all artifacts related to the paper "BUSted!!! Microarchitectural Side-Channel Attacks on the MCU Bus Interconnect," which was accepted at IEEE S&P 2024. For more details about the attack, please visit our dedicated [website](https://bustedattack.com/), where all relevant documentation is centralized.

## Repo Structure 

**DMA-Covert-Channel**
- `Results`: Covert-channel measurements, including channel capacity.
- `src`: Source code for the covert-channel.
- `capacity.sh`: Script to automate the measurement of channel capacity.

**tools**
- `heatmap.py`: Tool for plotting the channel matrix ([example](./DMA-Covert-Channel/README.md#3---results)).
- `profile.py`: Tool for obtaining the pruned matrix from a victim trace.

## Covert-Channels

The repository includes the covert-channel [data](./DMA-Covert-Channel) for the 11 MCUs tested and a [trace](./tools/data.txt) to the Smart Lock Application (our victim). We also supply the necessary [tools](./tools/README.md) to replicate the experiments and enable further research.

The channel capacities were measured using the leakiEst tool ([Credits](#credits)). In the [DMA-Covert-Channel](./DMA-Covert-Channel/README.md) folder, you will find a script (``capacity.sh``) that automates the execution of this tool and extracts the channel capacity measurements.

## BUSted Attack

### Profiling Phase

Coming soon...

### Exploitation Phase

Coming soon...

## Credits

The channel capacity was measured using the leakiEst tool, developed by researchers from the University of Birmingham. For more information please visit the [leakiEst site](https://www.cs.bham.ac.uk/research/projects/infotools/leakiest/#:~:text=leakiEst%20%E2%80%94%20Tool%20for%20%22Leaking%20information%20Estimation%22.,insecure%20system%20with%20a%20very%20small%20information).

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
