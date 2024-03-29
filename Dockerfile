FROM ubuntu:latest

RUN apt-get update && apt-get install -y clang cmake llvm

WORKDIR /BallLang

COPY . .

RUN rm -r build && mkdir build && cd build && cmake .. && make

CMD ["./build/BallLang"]
