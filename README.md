# Genome (C++ 3D Experiments)

This is a project that was made for experiments with 3D in C++.

# Building

## Prebuild

```
rm -rf ./build && mkdir build && cd build
```

## Build

```
cmake .. && make all
```

or to hard rebuild

```
rm -rf ./* && cmake .. && make all
```

```
rm -rf ./build/*
```

## Start

```
./genome
```

# Development

```
sudo npm i -g nodemon
rm -rf ./build && mkdir build
export DEVELOPMENT_MODE=true
nodemon --delay 500ms --signal SIGHUP --ignore build/ -e h,cpp,txt --exec "cd build && cmake .. && make all || exit 1"
nodemon --signal SIGHUP --watch ./build/genome --exec "./build/genome || exit 1"
```

# MacOS Vulkan API Issue

Download SDK (https://vulkan.lunarg.com/sdk/home) and unzip to `/Users/USER/vulkansdk`.

Set there environment variables before building:

```
export VULKAN_SDK=/Users/$USER/vulkansdk/macOS
export PATH=$VULKAN_SDK/bin:$PATH
export VK_ICD_FILENAMES=$VULKAN_SDK/etc/vulkan/icd.d/MoltenVK_icd.json
export VK_LAYER_PATH=$VULKAN_SDK/etc/vulkan/explicit_layers.d
export DYLD_LIBRARY_PATH=$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH
export VULKAN_FRAMEWORK_PATH=$VULKAN_SDK/Frameworks
export DYLD_FRAMEWORK_PATH=$VULKAN_FRAMEWORK_PATH:$DYLD_FRAMEWORK_PATH
```
