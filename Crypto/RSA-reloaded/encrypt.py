from Crypto.Util.number import *
from Crypto.PublicKey import RSA
import gmpy2

p=getPrime(1024)
q=getPrime(1024)

N1=p*q
e=65537L

flag=open('flag.txt').read()
f1=bytes_to_long(flag[:len(flag)/2])
f2=bytes_to_long(flag[len(flag)/2:])

if p>q:
	x=p%q
else:
	x=q%p

r=gmpy2.next_prime(x+f1)
s=gmpy2.next_prime(r)

for i in range(50):
	s=gmpy2.next_prime(s)

N2=r*s

enc_f1=pow(f2,e,N1)
enc_f2=pow(f1,e,N2)

pub_key = RSA.construct((int(N1), e))
pub_key2 = RSA.construct((int(N2), e))
open("publickey1.pem","w").write(pub_key.exportKey("PEM"))
open("publickey2.pem","w").write(pub_key2.exportKey("PEM"))

file1 = open("ciphertext1.txt", 'w')
file2 = open("ciphertext2.txt", 'w')
file1.write(str(enc_f1))
file2.write(str(enc_f2))
