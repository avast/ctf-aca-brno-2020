flag: avastCTF{g00d_0ld_1nj3ct10n_t7f9de1}

Challenge is dockerized, to run:
docker-compose build && docker-compose up
server.py and start.sh must be in the same folder
exposed port is defined in docker-compose.yml, currently 8000

Possible solution:
- web is written using Python Tornado framework, which is hinted at by the web itself and also response headers
- input field is vulnerable to server-side template injection, allowing command execution on the server
- example payload: {%import os%}{{os.popen("env").read()}}
- there is a file flag.txt, which does not contain a flag - instead there is a message that the flag has been moved (hint to look at bash_history)
- in .bash_history players can see the exact command that was used to encrypt the flag and put it into environment variables
- reverse the process to get the flag
