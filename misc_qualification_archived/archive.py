import argparse
import os
import random
import threading
import time
import uuid


def arg_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--depth", type=int, required=True, help="Depth of created archives")
    parser.add_argument("-c", "--count", type=int, required=True, help="The number of achives to be created")
    parser.add_argument("-t", "--threads", type=int, required=True, help="Number of threads to use")
    args = parser.parse_args()

    return args


def remove_and_move(name, extension=None, remove=True):
    if remove is True:
        os.system("rm " + name)
    os.system("mv " + name + "." + extension + " " + name + " > /dev/null")


def make_7z(name):
    os.system("7z a " + name + ".7z " + name + " > /dev/null")
    remove_and_move(name, "7z")


def make_bz2(name):
    os.system("bzip2 " + name + " > /dev/null")
    remove_and_move(name, "bz2", False)


def make_gz(name):
    os.system("gzip " + name + " > /dev/null")
    remove_and_move(name, "gz", False)


def make_rar(name):
    os.system("rar a " + name + ".rar " + name + " > /dev/null")
    remove_and_move(name, "rar")


def make_tar(name):
    os.system("tar -cvf " + name + ".tar " + name + " > /dev/null")
    remove_and_move(name, "tar")


def make_xz(name):
    os.system("xz " + name + " > /dev/null")
    remove_and_move(name, "xz", False)


def make_zip(name):
    os.system("7z a " + name + ".zip " + name + " > /dev/null")
    remove_and_move(name, "zip")


def archive(name, depth):
    last = None
    functions = [make_7z, make_bz2, make_gz, make_rar, make_tar, make_xz, make_zip]
    
    for i in range(0, depth):
        while True:
            random_function = random.randint(0, len(functions) - 1)
            
            if random_function != last:
                last = random_function
                break
        functions[random_function](name)


def create_flag_file(name, uid):
    file = open(name, "w")
    file.write(f"avastCTF{{{uid}}}")
    file.close


def generate_archive(x, uid, depth):
    create_flag_file(str(x), uid)
    archive(str(x), depth)


def generate_archives(count, depth, threads):
    with open("solutions", "w") as solutions:
        for x in range(0, count):
            uid = uuid.uuid4()
            solutions.write(f"avastCTF{{{uid}}}\n")

            thread = threading.Thread(target=generate_archive, args=(x, uid, depth))
            thread.start()

            if(threading.active_count() >= args.threads + 1):
                thread.join()

    thread.join()


if __name__ == "__main__":
    start = time.time()
    args = arg_parse()
    generate_archives(args.count, args.depth, args.threads)
    print(f"--- {time.time() - start} seconds ---")
