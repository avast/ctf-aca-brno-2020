import argparse
import itertools
from string import ascii_lowercase

parser = argparse.ArgumentParser()
parser.add_argument("file")
args = parser.parse_args()

key_list = itertools.product(ascii_lowercase, repeat=4)

with open(args.file, 'r', newline='') as in_file:
    flag = in_file.read()
    for key in key_list:
        result = ""
        for c in range(len(flag)):
            result += chr(ord(flag[c]) ^ ord(key[c % len(key)]))

        if(result[:8] == 'avastCTF'):
            print(f"{''.join(key)}: {result}")
