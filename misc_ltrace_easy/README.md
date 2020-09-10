# ltrace (Misc #9)

## Description
```
We've gotten hold of this executable.
The thing is. It is asking for a password and we don't have it.
Can you find out what it is? Or maybe bypass it?
It's up to you, we're sure if there is a (l)trace you will find it.
```

## Solution
An executable is the only thing you get.
So you run it and it asks for a password.
Giving it a password results in Wrong being printed (unless you got it right on first try - in which case congrats :)).
So you may think to try `gdb` or `strings`, but neither yields useful information, but using `ltrace` even with a wrong password shows what we need to put in to get further.
After putting in the correct password we recieve the flag