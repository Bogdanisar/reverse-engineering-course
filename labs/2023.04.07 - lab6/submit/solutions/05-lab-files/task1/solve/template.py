from pwn import *
import sys

io = process("./task1")

io.recvuntil(bytes('Enter password:', 'utf-8'))

password = 'Oqu3raiN\n'
io.sendline(bytes(password, 'utf-8'))

io.interactive()

# io.wait()

sys.exit()
