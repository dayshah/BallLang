FROM ubuntu:latest

RUN apt-get update && apt-get install -y clang cmake llvm

WORKDIR /BallLang

COPY . .

RUN cmake . && make
