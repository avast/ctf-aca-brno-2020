DOT_SIGN = '&'
DASH_SIGN = '%'
FLAG = "avastCTF{d4rl1ng_c4nt_you_hear_m3_s0s}"

morse_code = {
    'a': ".-",
    'b': "-...",
    'c': "-.-.",
    'd': "-..",
    'e': ".",
    'f': "..-.",
    'g': "--.",
    'h': "....",
    'i': "..",
    'j': ".---",
    'k': "-.-",
    'l': ".-..",
    'm': "--",
    'n': "-.",
    'o': "---",
    'p': ".--.",
    'q': "--.-",
    'r': ".-.",
    's': "...",
    't': "-",
    'u': "..-",
    'v': "...-",
    'w': ".--",
    'x': "-..-",
    'y': "-.--",
    'z': "--..",
    '0': "-----",
    '1': ".----",
    '2': "..---",
    '3': "...--",
    '4': "....-",
    '5': ".....",
    '6': "-....",
    '7': "--...",
    '8': "---..",
    '9': "----."
}

result = ""
for c in FLAG:
    if c.lower() in morse_code:
        result += morse_code[c.lower()]
    else:
        result += c
    result += ' '

result = result.replace('.', DOT_SIGN)
result = result.replace('-', DASH_SIGN)

print(result)