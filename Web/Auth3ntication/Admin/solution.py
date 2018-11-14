import re

message = raw_input("==> Message given (in hex):  ")
key_len = int(raw_input("==> Key length:  "))
knowing_mes = raw_input("==> The expected message in the output (should be equal to key length) \nGive in characters:  ")
print "\n"
keys = []
list = []

message = message.replace("\\x","")
message = message.decode("hex")

for i in range(0,len(message)-key_len):
    list.append(message[i:i+key_len])

for hell in list:
    str = ""
    for i in range(0,key_len):
        str += chr(ord(hell[i])^ord(knowing_mes[i]))
    keys.append(str)

for key in keys:
    output = ""
    for i in range(0,len(message)):
        output += chr(ord(key[i%key_len])^ord(message[i]))
    if(re.search(knowing_mes,output)):
        print key + ": \t" + output
        print "\n"