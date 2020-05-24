# Genome (C++ 3D Experiments)

This is a project that was made for experiments with 3D in C++.

## Prebuild

```
mkdir build && cd build
```

## Build

```
cmake .. && make all
```

or to hard rebuild

```
rm -rf ./* && cmake .. && make all
```

### Start

```
./genome
```

## Development Mode

sudo npm i -g nodemon
nodemon --delay 500ms --ignore build/ -e h,cpp --exec "cd build && cmake .. && make all"
nodemon --watch ./build/genome --exec "./build/genome"
