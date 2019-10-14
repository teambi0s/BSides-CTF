# secureauth

**Challenge files** : [handout](Handout/)

**Author** : sherl0ck, night_f0x

**Short Solution** : In the check function, at the start it calls `rtdsc` (a precise timestamp) and saves the timestamp in the bss. With the buffer overflow in main call `rtdsc` again and find the difference between the 2 timestamps. If you had entered the correct byte, then nanosleep would be called in the loop and it would take longer than an incorrect flag byte.
Ideally we meant to get shellcode execution, though some tried with ROP. For shellcode execution, use csu gadgets to controls `rdi`, `rsi` and `rdx` and call `mprotect` to make the `bss` segment `rwx`. Then shellcode to find the difference between the saved timestamp and the freshly calculated one. Print out the difference. The byte that takes the longest time is the correct one. Use this to bruteforce the flag.
