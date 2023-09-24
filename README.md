# amol-opt
Partial reimplementation of [opt-rs](https://github.com/t-young31/opt-rs)
using [EnzymeAD](https://github.com/EnzymeAD/Enzyme) for automatic differentation.

## Usage
Open this repository in a devcontainer

```bash
mkdir build
cmake -B build/ -S . && makc -C build
# Optimise a molecule and generate opt.xyz
./build/amopt h2o.xyz
```
