# Privilege (Misc #11)

## Description
```
We found a server with another flag file. However we cannot seem to access it due to privileges. There is only the flag file and some random executable. We're sure you'll figure something out. SSH: 10.4.234.7:2222 user:123
```

## Solution
Connect to the server given in the description (or the docker image IP on port 2222) using the credentials given.
You will see two files: `flag` and `privilege`.
Trying to open `flag` yields a `Permission denied`.
After running the `privilege` executable you are shown a prompt, trying different length inputs shows that after a certain number of characters you start to overflow into the output.
The output has to match `1337beef` which can be done by using a script similar to `solution.sh` that prints enough characters to start the overflow and than prints characters with hex value of `ef`, `be`, `37` and `13`.