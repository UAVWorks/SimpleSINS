#!/bin/bash

ROOT_DIR=$(cd $(dirname $0)/../ && pwd)

docker run --rm -ti -v $ROOT_DIR:/src --workdir=/src -e HOST_USER_ID=$(id -u) -e HOST_USER_GROUP_ID=$(id -g) -e HOST_USER_NAME=$USER approximator/clangformat:4.0 bash -c "find /src/firmware -maxdepth 1 \( -name '*.c' -o -name '*.h' \) -print -exec clang-format-4.0 -style=file -i {} \; && find /src/GroundControlStation/src \( -name '*.cpp' -o -name '*.h' \) -print -exec clang-format-4.0 -style=file -i {} \;"
