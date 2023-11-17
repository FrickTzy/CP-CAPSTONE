FROM ubuntu:latest
LABEL authors="Karl"

ENTRYPOINT ["top", "-b"]