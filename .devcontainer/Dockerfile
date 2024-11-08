FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-22.04

# Install clang, llvm, git, and gtest
RUN apt-get update && \
    apt-get install -y \
        clang \
        libclang-dev \
        llvm \
        git \
        cmake \
        libgtest-dev \
        libbenchmark-dev \
        build-essential \
        libboost-all-dev && \
    # Build and install gtest
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib && \
    # Clean up to reduce the image size
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN apt update && apt install -y python3 python3-pip
RUN pip3 install pytest
