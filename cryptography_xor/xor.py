FLAG = "avastCTF{x0r_is_a_l1ttl3_b3tter_th4n_m0r}"
KEY = "hell"

result = ""
for c in range(len(FLAG)):
    val = ord(FLAG[c]) ^ ord(KEY[c % len(KEY)])
    print(f"{FLAG[c]}({ord(FLAG[c])}) xor {KEY[c % len(KEY)]}({ord(KEY[c % len(KEY)])}) = {val}")
    result += chr(val)

with open("flag", 'w', newline='') as out_file:
    out_file.write(result)