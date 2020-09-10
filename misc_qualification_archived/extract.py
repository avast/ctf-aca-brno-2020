import os

while(True):
    filetype = os.popen('file 0 | grep -Po "(?<=0: ).*?(?= )"').read()
    filetype = filetype.strip()

    if(filetype == "gzip"):
        os.system("mv 0 0.gz && gzip -d 0.gz")
    elif(filetype == "XZ"):
        os.system("mv 0 0.xz && xz -d 0.xz")
    elif(filetype == "7-zip"):
        os.system("7z -y e 0")
    elif(filetype == "Zip"):
        os.system("7z -y e 0")
    elif(filetype == "POSIX"):
        os.system("tar -xvf 0")
    elif(filetype == "POSIX"):
        os.system("tar -xvf 0")
    elif(filetype == "RAR"):
        os.system("mv 0 0.rar && unrar e 0.rar && rm 0.rar")
    elif(filetype == "bzip2"):
        os.system("mv 0 0.bz2 && bzip2 -d 0.bz2")
    else:
        print(filetype)
        break
