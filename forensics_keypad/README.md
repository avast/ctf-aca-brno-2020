# Keypad

We recorded a hacker typing something on a keypad. Unfortunately the video got corrupted, but we managed to save the audio track. Is it enough to find out what he was typing? (Flag should be in the format avastCTF{wordword}.)

## Solution
Audio file contains a sequence of DTMF tones (typing on a keypad), which can be translated to a sequence of numbers.
Low amount of repeating numbers should indicate this is not a plain multitap keypad sequence - T9 is used.
Each number can therefore mean multiple letters (1 = a, b or c). By listing the possibilities, most words in ciphertext correspond with only one or few English words.
Flag: avastCTF{pulsedialing}
