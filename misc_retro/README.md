## Description

"Can you make this program reveal the flags to you? Hint: what is the output based on? gdb or a similar tool may be helpful. The challenge contains 2 flags."

Flag2: avastCTF{seg_faults_for_days_75509}
Flag1: avastCTF{44500128} 

- players are given file "retro", a compiled executable
- when the program runs, it creates an array of mostly zero values, but one array field contains the flag
- then it prints one value from the array
- the index of the value printed is determined by current time
- flag1: by setting the system time, they can move one by one through the array, until they find the flag
- flag2: time is represented as int32(time since epoch) - can be overflown by e.g. setting date far enough in the future, program will segfault and print the flag
