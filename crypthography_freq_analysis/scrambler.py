import argparse
import random


def parseArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-i",
        "--input",
        type=str,
        required=True,
        help="Path to source file")
    parser.add_argument(
        "-o",
        "--output",
        type=str,
        required=True,
        help="Path to output file")

    return parser.parse_args()


def scrambleAlphabet():
    done = False

    while done is False:
        alphabet = "abcdefghijklmnopqrstuvwxyz"
        alphabetList = []
        cheatSheat = {}
        for char in alphabet:
            alphabetList.append(char)

        for char in alphabet:
            rand = random.randint(0, len(alphabetList) - 1)
            cheatSheat[char] = alphabetList[rand]
            alphabetList.remove(alphabetList[rand])

        done = True
        for char in cheatSheat:
            if cheatSheat[char] is char:
                done = False

    return cheatSheat


arguments = parseArgs()

cheatSheat = scrambleAlphabet()

with open(arguments.input, 'r') as in_file:
    with open(arguments.output, 'w') as out_file:
        for line in in_file:
            for char in line:
                if (char >= 'a' and char <= 'z'):
                    out_file.write(cheatSheat[char])
                elif (char >= 'A' and char <= 'Z'):
                    out_file.write(cheatSheat[char.lower()].upper())
                else:
                    out_file.write(char)

with open("flag", 'w') as flag:
    for char in "AvastCTF{vigen3ere_w4s_a_clever_c00kie}":
        if (char >= 'a' and char <= 'z'):
            flag.write(cheatSheat[char])
        elif (char >= 'A' and char <= 'Z'):
            flag.write(cheatSheat[char.lower()].upper())
        else:
            flag.write(char)
