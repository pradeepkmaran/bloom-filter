FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    pkg-config \
    python3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN rm -rf build && mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc)

# Run tests by default
CMD ["ctest", "--test-dir", "build", "--output-on-failure"]
