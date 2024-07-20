#!/bin/bash

# Define compiler and flags
CXX=g++
CXXFLAGS="-std=c++11 -Wall"
INCLUDES="-I/opt/homebrew/opt/openssl@1.1/include"
LIBS="-L/opt/homebrew/opt/openssl@1.1/lib -lssl -lcrypto -lsqlite3"
SRC_DIR="src"
BIN_DIR="bin"
TARGET="${BIN_DIR}/my_program"

# Create bin directory if it doesn't exist
mkdir -p ${BIN_DIR}

# Compile the source files
${CXX} ${CXXFLAGS} ${INCLUDES} ${SRC_DIR}/*.cpp -o ${TARGET} ${LIBS}

# Run the program
./${TARGET}
