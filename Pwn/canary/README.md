# canary

**Challenge files** : [handout](Handout/)

**Author** : mahesh

**Short Solution** : Simple stack overflow; overwrite the `argv[0]` with pointer to flag that is already read into the binary, trigger `stack_chk_fail` to leak the flag.
