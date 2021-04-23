# Maybe for prod we can use an alpine image
FROM ubuntu:bionic

RUN apt-get update && \
    apt-get -y install clang cmake && \
    rm -rf /var/lib/apt/lists/*

# We could build here the application, but is more practical for CI to use
# one docker for building and creating a new image just for production with only the
# runtime dependencies and the binaries.

WORKDIR /opt