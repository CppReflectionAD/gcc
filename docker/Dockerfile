# Runtime and development image for GCC reflection and cpp_reflection_ad.
# The build context is the DESTDIR staging tree (dist/), which contains opt/gcc.
# Base must match the runner OS (ubuntu-latest = 24.04) so glibc/shared libs line up.
FROM ghcr.io/astral-sh/uv:latest AS uv-bin

FROM ubuntu:24.04

# Install GCC dependencies, cpp_reflection_ad build/test tools, and developer utilities
RUN apt-get update && apt-get install -y --no-install-recommends \
      binutils \
      bison \
      build-essential \
      ca-certificates \
      cmake \
      curl \
      dejagnu \
      flex \
      gdb \
      git \
      less \
      libc6-dev \
      libgmp-dev \
      libgmp10 \
      libmpc-dev \
      libmpc3 \
      libmpfr-dev \
      libmpfr6 \
      neovim \
      ninja-build \
      openssh-client \
      procps \
      python3 \
      python3-pip \
      python3-venv \
      screen \
      tar \
      texinfo \
      xz-utils \
      zlib1g \
      zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy uv for Python tooling (pre-commit, linting, script dependencies)
COPY --from=uv-bin /uv /uvx /usr/local/bin/

COPY opt/gcc /opt/gcc

ENV PATH=/opt/gcc/bin:$PATH \
    LD_LIBRARY_PATH=/opt/gcc/lib64:/opt/gcc/lib

CMD ["bash"]
