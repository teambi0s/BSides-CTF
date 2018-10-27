# avap

**Challenge File**: [avap](Handout/avap)  

**Author**: [a.m3th](https://twitter.com/a_m3th), [k4iz3n](https://twitter.com/akulpillai)

**Description**: Here's an easy one for you all.

**Flag**: flag{4s_e45y_4s_1t_g3ts}

**Walk through**: A basic binary where a check function first checks the commandline argument and checks if it is 7 using a quadratic equation and sets a global variable as 7.
Then it calls the main function which calls a stringcmp function which XORs the input with the key and then compares it with the hardcoded using strncmp.

