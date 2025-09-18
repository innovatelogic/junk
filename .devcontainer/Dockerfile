FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-24.04

# Install clang, llvm, git, and gtest
RUN apt-get update -y && \
    apt-get install -y --no-install-recommends \
        clang \
        libclang-dev \
        llvm \
        llvm-dev \
        build-essential \
        git \
        cmake \
        libgtest-dev \
        libbenchmark-dev \
        build-essential \
        libopencv-dev \
        python3 \
        python3-dev \
        python3-venv \
        python3-pip \
        python3-numpy \
        libgnutls28-dev \
        libboost-all-dev && \
    # Build and install gtest
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib && \
    # Clean up to reduce the image size
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN apt update && apt install -y python3 python3-pip
RUN pip3 install --break-system-packages pytest sympy matplotlib ninja

# Build script
COPY build-seastar.sh ./build-seastar.sh
RUN chmod +x ./build-seastar.sh
RUN sudo ./build-seastar.sh

ARG USERNAME=vscode
RUN id -u ${USERNAME} &>/dev/null || useradd -m ${USERNAME}

CMD ["bash"]