FROM ubuntu:20.04

LABEL maintainer="jlesner@ucsc.edu"

# COPY ../smv_dep /src_dep/

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    libsaxonb-java \
    graphviz \
    cpp \
    curl \
    dos2unix \
    default-jre-headless \
    wget

RUN ln -s /usr/bin/python3 /usr/bin/python
# RUN ln -s /usr/bin/pip3 /usr/bin/pip

RUN pip3 install lxml==4.9.2 numpy==1.24.4 pycparser==2.21

# WORKDIR /smv

# fetch dependency includes
# RUN curl -sL http://aws_path | ( cd / && tar -xzf - ) 
# CMD ["node", "server.js"]
