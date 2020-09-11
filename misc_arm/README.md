### Description

"Find out what would be the output of the linked program, when it would be executed with argument 6499045. To make it easier for you, the file f.s contains simplified version of the critical function. Flag should be in the format avastCTF{#output_number}."

- players are given source.s assembly file, f.s with simplified assembly of just the function,  and an input (number)
- flag will be in format avastCTF{output_number}
- flag for input 6499045: avastCTF{3606}
- cfile is just a compiled version of the program to check the result, will not be given to players

### Solution

- assembly code is using arm instruction set, so one solution would be to just compile the code on arm machine and run it with given input
- second option might be to reason through the instructions? especially in the simplified version f.s

given input 6499045 -> output 3606
