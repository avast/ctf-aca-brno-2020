# download base image
FROM ubuntu

RUN apt-get update

# download sudoku script prerequisites
RUN apt-get install -y python3
RUN apt-get install -y python3-pip
RUN pip3 install numpy

RUN mkdir /sudoku_server

WORKDIR /sudoku_server

# copy sudoku script to docker
COPY . .

# open port 19988
EXPOSE 19988

# run sudoku server
CMD python3 main.py
