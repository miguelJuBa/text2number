# text2number

## How to build using docker for development
```bash
# Create a new docker image with our desired dependencies
docker build -t text2number:dev .

# Enter docker image commandline 
docker run --rm -it -v <path/to/project/root>:/opt text2number:dev bash

# Build using cmake
mkdir build
cd build
cmake ..
make
```

## How to run

Just invocate the newly created binary:
```bash
docker run --rm -it -v <path/to/project/root>:/opt text2number:dev bash

./build/src/text2number
```

