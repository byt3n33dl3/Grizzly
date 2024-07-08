#!/bin/bash

PROJECT_NAME=mydriver
PROJECT_DIR=$PWD
BUILD_DIR=${PROJECT_DIR}/build
BIN_DIR=${PROJECT_DIR}/bin
SRC_DIR=${PROJECT_DIR}/src

if [ -d "${BUILD_DIR}" ]; then
	rm -rfd ${BUILD_DIR}
fi

if [ -d "${BIN_DIR}" ]; then
	rm -rfd ${BIN_DIR}
fi

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

cmake -G "Unix Makefiles" "${SRC_DIR}"

make
mkdir -p ${BIN_DIR}

mv -f "${BUILD_DIR}/${PROJECT_NAME}.ko" "${BIN_DIR}"

make clean
rm -rf ${BUILD_DIR}
