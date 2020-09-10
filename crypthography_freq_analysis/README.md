# Frequency Analysis (Cryptography #2)

## Description
```
Yesterday our spies captured a non-sensical text file. It seems to be some kind of super advanced Ceasar's cipher. Try and see if you can crack it. It may contain some very important information.
```

## Solution
Participant gets a scrambledFlag and scrambledText, which has obviously been scrambled using alphabet substitustion.
Some letters can be gained from the scrambledFlag because all (most) flags are formated as `AvastCTF{*flag*}`.
Use or create a tool that solves substitution cyphers (usually based on the letter frequency of english texts and some kind of word dictionary), for example `https://www.dcode.fr/monoalphabetic-substitution` and use it on scrambledText.
Now that the template for decoding each letter is found, just apply it to the scrambledFlag.