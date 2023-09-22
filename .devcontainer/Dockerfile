FROM mcr.microsoft.com/devcontainers/base:bookworm

RUN apt-get update && \
    apt-get install --yes \
    cmake make llvm-dev lld clang libclang-dev python3-pip python3.11-venv clang-tidy && \
    python3 -m venv .venv && \
    . .venv/bin/activate && \
    pip install pre-commit

RUN git clone --depth 1 --branch v0.0.84 https://github.com/EnzymeAD/Enzyme.git && \
    cd Enzyme && \
    mkdir build && cd build && cmake ../enzyme -DCMAKE_BUILD_TYPE=Release && \
    make -j "$(nproc)" install
