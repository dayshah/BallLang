FROM ubuntu:latest

RUN apt-get update && apt-get install -y clang cmake llvm clangd git gdb

WORKDIR /BallLang

COPY . .
