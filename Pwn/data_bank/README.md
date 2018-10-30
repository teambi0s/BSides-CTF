# data_bank  

**Challenge files** : [handout](Handout/)

**Author** : mahesh

**Short Solution** : Obvious tcache UAF; perform a tcache corruption to get control of the tcache count[] array, overwrite the count of any small bin size chunk to 7, free small bin chunk to get libc leak, do another tcache corruption to overwrite free_hook with one_gadget.

**flag** : flag{k33p_c0unt_0f_The_entr1e5}

**Discription**

``` 
nc 35.200.202.92 1337

```

