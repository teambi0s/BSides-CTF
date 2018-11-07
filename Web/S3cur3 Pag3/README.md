### Chall Name
S3cur3 Pag3

### Chall Description
One of the most secure websites....or is it???

### Chall Link
http://35.200.146.153/chall/

### Flag
flag{NginX_4li45_p4th_tr4v3r54l5_r_b4d!!!}

### Points
250

### Solution
1. First we have to do a path traversal as we cant directly access the swp file and download the .swp file for index.php
    http://35.200.146.153/chall../chall/.index.php.swp
2. Then on analysing the swp file, we can understand what the required parameters are in order to get the flag.
3. Send a GET request with those parameters to get the flag.  
    http://35.200.146.153/chall/?fflllllaaaagg=nginxisbadifpoorlyconfigured
