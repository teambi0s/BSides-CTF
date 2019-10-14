#!/usr/bin/env python2
import os
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from secret import FLAG


class AES_Key:
    def __init__(self):
        self.key=list(os.urandom(16))

    def enqueue(self):
        self.key+=get_random_bytes(1)

    def dequeue(self):
        self.key=self.key[1:]

    def size(self):
        return len(self.key)

    def shuffle(self):
        self.dequeue()
        self.enqueue()
        assert self.size()==AES.block_size
        return "".join(self.key)

def pad(msg):
    pad_byte = 16 - len(msg) % 16
    return msg + chr(pad_byte) * pad_byte

def slice(msg,step = AES.block_size):
    yield [pad(msg)[i:i+step] for i in range(0,len(msg),step)]


key = AES_Key()
ct=""
MAC = 0
for List in slice(FLAG):
    for block in List:
        cipher = AES.new(key.shuffle(), AES.MODE_ECB)
        ct+= cipher.encrypt(block)
        MAC ^= int(ct[-16:].encode('hex'),16)

MAC ^= int(key.shuffle().encode('hex'),16)

open("ci.pher.text",'wb').write(str(MAC) +":"+ ct.encode('hex'))



