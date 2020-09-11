#!/bin/bash
mkdir /home/user
echo "Not so fast. The flag was here, but I moved it somewhere else for safety." > flag.txt
echo 'export ENCRYPTEDFLAG=$(cat /flag.txt | tr -d '\n' | base64 | rev)' >> /home/user/.bash_history
echo "Not so fast. The flag was here, but I moved it somewhere else for safety. > /flag.txt" >> /home/user/.bash_history
