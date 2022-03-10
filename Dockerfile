FROM alpine:latest

COPY . /usr/blockchain/

RUN apk update; \
    apk upgrade; \
    apk add g++ cmake make;

WORKDIR /usr/blockchain/

RUN mkdir build; \
    cd build; \
    cmake ..; \
    make; 

WORKDIR /usr/blockchain/build

CMD [ "./DirAnalyzer" ]

