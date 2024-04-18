#FROM ubuntu:22.04@sha256:arm64_version_sha256_here
#FROM --platform=linux/arm64 ubuntu:20.04
FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

EXPOSE 7777/udp

ENV USER root

ENV LIBGL_ALWAYS_SOFTWARE=1

#TODO: Include layer for Google's FlatBuffer
    # source: git clone https://github.com/google/flatbuffers.git
    # within "FlatBuffers" dir, "cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ." (for Mac) find Linux version
    # compile FlatBuffers, using "make"
    # OPTIONAL TEST RUN: "./flattests"
    # move flatc exec to usr/local/ (also contains cmake) "sudo mv flatc /usr/local/"


#Install the dependencies required for the build
    # build-essential (GNU Compiler)
    # libstdc++-11-dev (C++ std libraries)
    # wget to make a request for Cmake
    # git to retreive the ENet library
    # autoconf and libtool (dependency of autoconf)

# "apt-get clean" will delete the leftover .deb files from the install
# "rm -rf "var/lib/apt/lists/*" deletes the package list downloaded by "apt-get update"

RUN apt-get update && apt-get install -y build-essential libstdc++-11-dev wget git libtool autoconf && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*


# fetch the ENet source code from GitHub, then build, compile, and install
    # ldconfig creates links and cache to trusted directory (usr/lib || lib)

RUN git clone https://github.com/lsalzman/enet.git /tmp/enet

RUN cd /tmp/enet && \
    autoreconf -vfi && \
    ./configure && \
    make && \
    make install && \
    ldconfig

# Utilize wget to make a HTTP request to download CMake binary and specify the output path as "tmp" and name it "cmake.tar.gz"
# Uncompress the dictated "/tmp/cmake.tar.gz" w/-f, verbose -v. Put it in /usr/local (container filesytem). Throw away top level directories w/strip_components
# Delete the old compressed cmake.tar.gz
    # Cmake 3.27.9 via Kiteware compatible with AMD64 x86 architectures
RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-x86_64.tar.gz -O /tmp/cmake.tar.gz && \
    tar -xzvf /tmp/cmake.tar.gz -C /usr/local --strip-components=1 && \
    rm /tmp/cmake.tar.gz

# CMake 3.27.9 via Kitware compatible for ARM 64 Arhcitecture
#RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-aarch64.tar.gz -O /tmp/cmake.tar.gz && \
#    tar -xzvf /tmp/cmake.tar.gz -C /usr/local --strip-components=1 && \
#    rm /tmp/cmake.tar.gz


# The SFML library cannot be downloaded via it's most stable binary. Instead the specific v2.6 must be downloaded and built into
# an executable to satisfy the project's v2.6 requirement
RUN apt-get update && apt-get install -y \
    g++ \
    libflac-dev \
    libogg-dev \
    libvorbis-dev \
    libopenal-dev \
    libjpeg-dev \
    libfreetype6-dev  \
    libxrandr-dev \
    libglew-dev \
    libudev-dev \
    libsndfile1-dev \
    libgl1-mesa-dev \
    libxcursor-dev &&  \
    apt-get clean &&  \
    rm -rf /var/lib/apt/lists/*

RUN wget -O sfml.tar.gz https://github.com/SFML/SFML/archive/2.6.0.tar.gz && \
    tar -xf sfml.tar.gz && \
    cd SFML-2.6.0 && \
    cmake . && \
    make && \
    make install

RUN apt-get update && apt-get install -y \
    libgl1-mesa-glx \
    libgl1-mesa-dri \
    mesa-utils \
    && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# VNC server that is used to connect to VNC client on the client
RUN 	apt-get update && apt-get install -qqy x11-apps x11-utils x11vnc xvfb
RUN     mkdir ~/.vnc
RUN     x11vnc -storepasswd 1234 ~/.vnc/passwd

#Change working directory to project direcotry
WORKDIR /usr/src/Odyssey-Tennis-Pong

COPY . .

RUN mkdir build && cd build

RUN cmake .

RUN make

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

#CMD ["xeyes"]
#CMD ["/bin/bash"]
 CMD ["./Odyssey-Tennis-Pong"]