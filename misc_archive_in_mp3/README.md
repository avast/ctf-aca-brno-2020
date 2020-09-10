# Archive in mp3 (Misc #2)

## Description
```
We got this mp3 file in an email and we have reasons to believe there might be something hidden in it, but we cannot seem to find it.
```

## Solution

The only things you get is the carrier.mp3 file.
Use `binwalk` on it mp3 file, which tells you there is a zip file in it.
Extract the zip file, using `binwalk -e`.
Extract the contents of flag.bz2 file, which contains the flag in a text file