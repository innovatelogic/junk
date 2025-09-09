FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-22.04

# Install clang, llvm, git, and gtest
RUN apt-get update -y && \
    apt-get install -y software-properties-common && \
    add-apt-repository -y ppa:deadsnakes/ppa && \
    add-apt-repository -y ppa:ubuntugis/ppa -y && \
    apt-get update -y && \
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
        python3.10 \
        python3.10-dev \
        python3.10-venv \
        python3-pip \
        python3.9-distutils \
        python3-numpy \
        libboost-all-dev && \
    # Build and install gtest
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib && \
    # Clean up to reduce the image size
    apt-get clean && rm -rf /var/lib/apt/lists/*

RUN apt update && apt install -y python3 python3-pip
RUN pip3 install pytest sympy matplotlib

ARG USERNAME=vscode
RUN id -u ${USERNAME} &>/dev/null || useradd -m ${USERNAME}

CMD ["bash"]