# Spooky (Forensics #8)

## Description
```
A suspicious looking USB drive was found on the premises with nothing but the following note attached: "Whatever you may find inside this file, remember to put avastCTF{} around it. Know that numbering starts from 0 and if you're stuck Otto from Prison Break might help you out."
```

## Solution
You get a video in which random letters are appearing and disappearing every frame.
If you search for Otto from Prison Break you will find that his last name is Fibonacci.
Now you take the Fibonacci sequence and for each number in it you find the frame with a coresponding number and write down the letter that appears in it.
Then take the letters written down and put then inside `avastCTF{}` and you're done.