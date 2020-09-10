import argparse
import random
import socket
import time


def arg_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--target", required=True)
    args = parser.parse_args()

    return args


def main():
    message = "Did you hear about the blind Vietnamese man who was able to tell what race people were by touch? It's true! Just by feeling their hand, old man Nguyen could tell you if somebody was European, African, Polynesian, or American. He was best at Asian countries, just by practice, and could even tell what country someone was from, something he wasn't quite capable of with other ethnicities. For instance, he could tell upon meeting her that his wife Nguyet was Vietnamese, his friend Wong was Chinese, and his dentist Edgar was Singaporean. Well anyway, the Guinness Book of World Records eventually heard about him and sent out a team, since they'd never heard of anyone with this level of precision from simple touch. They ran several tests, asking him to hold the hands of several people and state their ethnicity. He did so, as he always had, with barely a hesitation. Then they decided to trick him. They brought in his wife Nguyet, his friend Wong, and his dentist Edgar. All three entered the room silently. The head researcher beckoned Wong over, and had him position himself in the same way all other tested people had been - but the researcher himself took Nguyen's hand. \"This person is European,\" Nguyen said immediately. The researcher nodded to Wong, who said, \"No Nguyen, it's me.\" Nguyen heard Wong's voice from exactly where he would expect it. But he knew that he was holding a white man's hand, and Wong was Chinese. \"This is not your hand, Wong. This is a white man's hand.\" \"That is Wong's hand, Nguyen. Have we been going too long? Do you need a break?\" The head researcher was impressed, but knew that he had to be absolutely certain about Nguyen's abilities. Nguyen held firmly. He shook his head. \"If this is Wong, why does it feel so white?\""
    flag = "avastCTF{asc11_is_s0_much_better_th4n_utf}"
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = "192.168.1.2"

    for char in flag:
        data = message[:42]
        message = message[42:]
        port = ord(char)
        time.sleep(random.random() * 5 + 0.2)
        sock.sendto(data.encode(), (ip, port))
        


if __name__ == "__main__":
    main()