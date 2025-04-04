# Build libdragon and tiny3d
FROM ghcr.io/dragonminded/libdragon:latest AS builder
ENV N64_INST=/n64_toolchain

COPY ./3rdparty/libdragon /tmp/libdragon
COPY ./3rdparty/tiny3d /tmp/tiny3d

RUN cd /tmp/libdragon && ./build.sh
RUN cd /tmp/tiny3d && ./build.sh

# Bake the built libraries into the docker image
FROM ghcr.io/dragonminded/libdragon:latest
ENV N64_INST=/n64_toolchain

ARG UID
ARG GID
ARG USERNAME

# Copy the built libraries from the builder stage
COPY --from=builder ${N64_INST} ${N64_INST}

# Install bear for compile_commands.json
# Install ffmpeg for asset conversion
# Ensure curl and unzip are installed for installing clangd
RUN apt-get update && apt-get install -y curl unzip bear ffmpeg && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Use curl to install clangd since newer version aren't in the package repo
RUN curl -L https://github.com/clangd/clangd/releases/download/20.1.0/clangd-linux-20.1.0.zip \
    -o /tmp/clangd.zip && \
    unzip /tmp/clangd.zip -d /tmp/clangd && \
    mv /tmp/clangd/clangd_20.1.0/bin/clangd /usr/bin/clangd && \
    chmod +x /usr/bin/clangd && \
    rm -rf /tmp/clangd*

# Create a non root user to run the container
# This allows for easier file sharing with the host
RUN groupadd -g $GID $USERNAME && \
    useradd -m -u $UID -g $GID -s /bin/bash $USERNAME

RUN apt-get update && apt-get install -y sudo && \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER $USERNAME
WORKDIR /home/$USERNAME

CMD ["sleep", "infinity"]
