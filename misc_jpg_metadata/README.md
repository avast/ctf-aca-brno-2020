# JPG metadata (Misc #8)

## Description
```
I think there may be something hiding in this picture of a random very handsome man. Please check it out.
```

## Solution
Simple viewing of vlcek.jpg doesn't give us any clue as to what the flag is.
But by accessing its metadata using for example `imagemagick's identify -verbose`, we find that where there should be copyright info, we find the flag.