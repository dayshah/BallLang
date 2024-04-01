FROM ubuntu:latest

RUN apt update && apt install -y clang cmake llvm clangd git gdb

WORKDIR /BallLang

COPY . .
