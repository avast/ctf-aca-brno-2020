# Corrupted Header (Misc #6)

## Description
```
I found this weird .pmg file on my old PC in a folder named important. Maybe it's worth looking into.
```

## Solution
After unsuccessfully trying to open the .pmg file, check what data it contains.
Use `xxd` or a similar tool to get the files magic number and compare it to standard formats.
After noticing it is very similar to .png, change the file to have the correct magic number.
Open the newly created .png file and you got it.