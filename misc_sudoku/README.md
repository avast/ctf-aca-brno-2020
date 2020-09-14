# sudoku

Sudoku is simple CLI game running on server. Client can connect and then play the game according to pre-described notation.

## docker
Sudoku is dockerized.
- to build docker image:
  ```
  $ sudo docker build -t ubuntu_sudoku .
  ```
- to run docker image:
  ```
  $ sudo docker run <image_id>
  ```
- to get docker's IP:
  ```
  $ sudo docker inspect --format '{{ .NetworkSettings.IPAddress }}' <image_id>
  ```

## usage
- ### server
  Run sudoku with:
  ```
  $ python3 main.py
  ```
- ### client
  Client can connect to port 19988:
  ```
  $ telnet <host> 19988
  ```
  After connection is established, server will generate sudoku and send parts of it to client in pre-described notation. Client have 30 seconds and only 1 attempt to send solution back.

## notation
Sudoku will be printed using this notation: **[row1, column1]-number1; [row2, column2]-number2; [row3, column3]-number3**

Example:
  [1,1]-2; [1,2]-5; [3,7]-8; [4,5]-1; [9,9]-7

*While client is connected to server, it can send data ONLY once*

## flag
**avastAdvanture{sUD0Ku_is_3asy}**
