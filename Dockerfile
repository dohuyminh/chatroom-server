# base image 
FROM ubuntu:latest

# working directory
WORKDIR /app

# C++ environment 
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake

# 

# lib code 
COPY lib lib/

# source code
COPY src src/

# configure build 
COPY CMakeLists.txt CMakeLists.txt
COPY build.sh build.sh

# API Port 
EXPOSE 8080

# build and run
RUN "bash ./build.sh"