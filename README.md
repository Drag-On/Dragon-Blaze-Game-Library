Dragon-Blaze-Game-Library
=========================

# How to compile
## Linux
### Dependencies:
- g++
- libx11-dev
- cmake
- make
- wget
- perl
- xorg-dev
- libglu1-mesa-dev

### Commands
Execute the following commands in a shell:
- cd /some/folder/
- git clone https://github.com/Drag-On/Dragon-Blaze-Game-Library.git
- cd Dragon-Blaze-Game-Library/
- git submodule init
- git submodule update
- cd DBGL_Base/lib/glew/
- make extensions
- make
- cd ../glfw/
- cmake -G "Unix Makefiles" -D BUILD_SHARED_LIBS=true .
- make
- cd ../../
- mkdir Release
- cd Release
- cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ../
- make

## Windows
TBD
