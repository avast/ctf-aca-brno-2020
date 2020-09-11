flag: avastCTF{4re_y0u_4_z3r0_0r_4_1}

Challenge is dockerized, to run:
docker-compose build && docker-compose up
exposed port is defined in docker-compose.yml, currently 8000
players should be given a copy of source_code.py, a server code with credentials and the flag redacted

Possible solution:
* what players can see from the redacted source code:
  * flag will be printed only if they visit /flag with correct value of auth cookie
  * structure of this cookie and which value (admin:1) is checked
  * login with admin username is disabled, so you need to manipulate the cookie directly
  * AES in CBC mode is not secure - a bit flip attack can be used - flipping a correct bit of the auth cookie will result in exactly one change in the plaintext (changing admin:0 to admin:1)
  * which bit to flip can be calculated, as the players will know the structure of the cookie
  * or it can be bruteforced by flipping each bit and checking for difference in the rendered page
