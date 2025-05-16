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
# All the lib stuff is for Blender
RUN apt-get update && apt-get install -y \
        ca-certificates gnupg \
        curl \
        unzip \
        bear \
        ffmpeg \
        xz-utils \
        libglib2.0-0 \
        libx11-6 \
        libxi6 \
        libxxf86vm1 \
        libxcursor1 \
        libxrandr2 \
        libxinerama1 \
        libxcomposite1 \
        libasound2 \
        libpulse0 \
        libpython3.10 \
        libtbb2 \
        libosd-dev \
        libembree-dev \
        libopenimageio-dev \
        libopencolorio-dev \
        libboost-python1.74-dev \
        libopenafs-dev \
        libopenvdb-dev \
        libilmbase-dev \
        libopenexr-dev \
        libsm6 \
        libxext6 \
        libxrender-dev \
        nsight-systems \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Blender v 4.0 for obj -> Fast64 -> t3d conversion
RUN curl -L -o /tmp/blender.tar.xz https://download.blender.org/release/Blender4.0/blender-4.0.2-linux-x64.tar.xz && \
    mkdir -p /opt/blender && \
    tar -xf /tmp/blender.tar.xz -C /opt/blender --strip-components=1 && \
    chmod +x /opt/blender/blender && \
    ln -s /opt/blender/blender /usr/bin/blender && \
    rm /tmp/blender.tar.xz

# Use curl to install clangd since newer version aren't in the package repo
RUN curl -L -o /tmp/clangd.zip https://github.com/clangd/clangd/releases/download/20.1.0/clangd-linux-20.1.0.zip && \
    unzip /tmp/clangd.zip -d /tmp/clangd && \
    mv /tmp/clangd/clangd_20.1.0/bin/clangd /usr/bin/clangd && \
    chmod +x /usr/bin/clangd && \
    rm /tmp/clangd.zip && \
    rm -rf /tmp/clangd

# Create a non root user to run the container
# This allows for easier file sharing with the host
RUN groupadd -g $GID $USERNAME && \
    useradd -m -u $UID -g $GID -s /bin/bash $USERNAME

RUN apt-get update && apt-get install -y sudo && \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER $USERNAME
WORKDIR /home/$USERNAME

# Install Fast64 for Blender
RUN curl -L -o /tmp/fast64.zip https://github.com/Fast-64/fast64/releases/download/v2.3.0/fast64-v2.3.0.zip && \
    mkdir -p /home/$USERNAME/.config/blender/4.0/scripts/addons/ && \
    unzip /tmp/fast64.zip -d ~/.config/blender/4.0/scripts/addons/ && \
    rm /tmp/fast64.zip

CMD ["sleep", "infinity"]
