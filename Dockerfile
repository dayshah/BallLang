FROM ubuntu:latest

RUN apt update && apt install -y clang cmake llvm clangd git gdb zlib1g-dev

WORKDIR /BallLang

COPY . .
